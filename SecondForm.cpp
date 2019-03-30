#include "SecondForm.h"

SecondForm::SecondForm(QWidget *parent,int a): QWidget(parent)
{
	if (a == 1)
	{
		int row = 10;
		QList<StudentInfo> studentList = currentStudentList;
		studentList=Random::sufferList(studentList);
		int listNum = studentList.count()/ row + 1;
		QVBoxLayout **vbox = new QVBoxLayout*[listNum];
		QHBoxLayout *hbox = new QHBoxLayout();
		int k = 0;
		for (int i = 0; i < listNum; i++)
		{
			vbox[i] = new QVBoxLayout();
			for (int j = 0; j < row; j++)
			{
				QCheckBox* checkbox = new QCheckBox(this);
				if (k < studentList.count())
				{
					checkbox->setText(studentList[k++].getName());
					checkbox->setStyleSheet("font: 14pt \"ËÎÌו\"");
					checkbox->setCheckState(Qt::Unchecked);
				}
				else
				{
					delete checkbox;
					hbox->addLayout(vbox[i]);
					goto loop1;
				}
				vbox[i]->addWidget(checkbox);
			}
			hbox->addLayout(vbox[i]);
		}
	loop1:
		this->setLayout(hbox);
	}
	else if (a == 2)
	{
		int row = 10;
		QList<StudentInfo> studentList = currentStudentList;
		studentList=Random::sufferList(studentList);
		int listNum = (studentList.count()+1)/2 / row + 1;
		QVBoxLayout **vbox = new QVBoxLayout*[listNum];
		QHBoxLayout *hbox = new QHBoxLayout();
		int k = 0;
		for (int i = 0; i < listNum; i++)
		{
			vbox[i] = new QVBoxLayout();
			for (int j = 0; j < row; j++)
			{
				QCheckBox* checkbox = new QCheckBox(this);
				if (k < studentList.count() - 1)
				{
					checkbox->setText(studentList[k++].getName() + " , " + studentList[k++].getName());
					checkbox->setStyleSheet("font: 14pt \"ËÎÌו\"");
					checkbox->setCheckState(Qt::Unchecked);
				}
				else if (k == studentList.count() - 1)
				{
					checkbox->setText(studentList[k++].getName() + " ,     ");
					checkbox->setStyleSheet("font: 14pt \"ËÎÌו\"");
					checkbox->setCheckState(Qt::Unchecked);
				}
				else
				{
					delete checkbox;
					hbox->addLayout(vbox[i]);
					goto loop2;
				}
				vbox[i]->addWidget(checkbox);
			}
			hbox->addLayout(vbox[i]);
		}
	loop2:
		this->setLayout(hbox);
	}
}

