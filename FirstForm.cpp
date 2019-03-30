#include "FirstForm.h"

FirstForm::FirstForm(QWidget *parent): QWidget(parent)
{
	rowNumber = (currentStudentList.count()-1) /8+1;
	seats = new QLabel*[rowNumber];
	QHBoxLayout **hbox = new QHBoxLayout*[rowNumber];
	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Maximum));
	for (int i = 0; i < rowNumber; i++)
	{
		seats[i] = new QLabel[8];
		hbox[i]=new QHBoxLayout();
	}
	for (int i = 0; i < rowNumber; i++)
	{
		hbox[i]->addSpacerItem(new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Maximum));
		for (int j = 0; j <8; j++)
		{
			if ((i*8+j)<currentStudentList.count())
			{
				seats[i][j].setText(QString("\n")+ currentStudentList[i * 8 + j].getId() + "\n\n" + currentStudentList[i * 8 + j].getName() + "\n\n" + currentStudentList[i * 8 + j].getSex()+"\n");
				seats[i][j].setVisible(true);
			}
			else
			{
				seats[i][j].setText(QString(QString("\n") +"        "+ "\n\n" +"   " "\n\n" + "       "+"\n"));
				seats[i][j].setVisible(false);
			}
			seats[i][j].setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			seats[i][j].setMinimumSize(130, 130);
			seats[i][j].setStyleSheet("font: 14pt \"宋体\";border-width:2px;border-style:solid;background-color: rgb(215, 254, 254);border-color: rgb(168, 255, 153);color: rgb(0, 0, 0);");
			//seats[i][j].setStyleSheet("font: 14pt \"宋体\";border-width:2px;border-style:solid;background-color: rgb(170, 255, 255);border-color: rgb(255, 85, 0);color: rgb(0, 0, 0);");//边框改为红色
			hbox[i]->addWidget(&seats[i][j]);
			if (j == 1 || j == 5)
			{
				hbox[i]->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Maximum, QSizePolicy::Minimum));
				hbox[i]->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Maximum, QSizePolicy::Minimum));
			}
			else
			{
				hbox[i]->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Maximum, QSizePolicy::Minimum));
			}
			
		}
		hbox[i]->addSpacerItem(new QSpacerItem(40, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
		
		vbox->addLayout(hbox[i]);
		vbox->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Maximum));
	}
	//vbox->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Expanding, QSizePolicy::Minimum));
	vbox->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	this->setLayout(vbox);
	this->setVisible(true);
}

FirstForm::~FirstForm()
{
	for (int i = 0; i < rowNumber; i++)
	{
		delete[] seats[i];
	}
}


void FirstForm::setSeatsText(QList<StudentInfo> studentsList)
{
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if ((i * 8 + j)<studentsList.count())
			{
				seats[i][j].setText(QString("\n") + studentsList[i * 8 + j].getId() + "\n\n" + studentsList[i * 8 + j].getName() + "\n\n" + studentsList[i * 8 + j].getSex() + "\n");
				seats[i][j].setVisible(true);
			}
			else
			{
				seats[i][j].setVisible(false);
			}
		}
	}
}

void FirstForm::setDifferentColor(int index)
{
	seats[index/8][index%8].setStyleSheet("font: 14pt \"宋体\";border-width:2px;border-style:solid;background-color: rgb(170, 255, 255);border-color: rgb(255, 85, 0);color: rgb(0, 0, 0);");//边框改为红色
}

void FirstForm::recoverColor()
{
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			seats[i][j].setStyleSheet("font: 14pt \"宋体\";border-width:2px;border-style:solid;background-color: rgb(215, 254, 254);border-color: rgb(168, 255, 153);color: rgb(0, 0, 0);");
		}
	}
}