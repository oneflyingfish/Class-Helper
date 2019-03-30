#include"ThirdForm.h"

ThirdForm::ThirdForm(QWidget *parent) : QWidget(parent)
{
	QVBoxLayout *vbox = new QVBoxLayout();
	//QHBoxLayout *hboxTop = new QHBoxLayout();
	//QHBoxLayout *hboxBelow = new QHBoxLayout();

	/*QPushButton *editButton = new QPushButton();
	editButton->setText("编辑");
	hboxTop->addWidget(editButton);

	QPushButton *deleteButton = new QPushButton();
	deleteButton->setText("删除");
	hboxTop->addWidget(deleteButton);

	QPushButton *insertButton = new QPushButton();
	insertButton->setText("插入");
	hboxTop->addWidget(insertButton);
	hboxTop->setAlignment(Qt::AlignRight);

	connect(editButton, SIGNAL(clicked()), this, SLOT(editInformation()));
	connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteInformation()));
	connect(insertButton, SIGNAL(clicked()), this, SLOT(insertInformation()));*/

	QTableWidget * tableWidget= new QTableWidget();
	QSqlDatabase *database = DataBase::readDatabase();
	QSqlQuery query;
	int i = 0, j = 0, nColumn, nRow;
	query.prepare("select * from "+currentClassName);
	query.exec();
	query.last();
	nRow = query.at() + 1;
	tableWidget->setRowCount(nRow);
	tableWidget->setColumnCount(4);
	tableWidget->setHorizontalHeaderLabels(QStringList() << "学号" << "姓名" << "性别" << "学院");
	tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(190, 255, 196);}");
	tableWidget->setAlternatingRowColors(true);
	nColumn = tableWidget->columnCount();
	query.first();
	while (j < nRow)
	{
		for (i = 0; i < nColumn; i++)
		{
			QTableWidgetItem *item = new QTableWidgetItem(query.value(i).toString());
			item->setTextAlignment(Qt::AlignCenter);
			tableWidget->setItem(j, i, item);
		}		
		j++;
		query.next();
	}
	database->close();

	//vbox->addLayout(hboxTop);
	vbox->addWidget(tableWidget);
	this->setLayout(vbox);
}