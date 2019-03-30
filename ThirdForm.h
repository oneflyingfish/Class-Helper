#ifndef THIRDFORM_H
#define THIRDFORM_H

#include<QtWidgets/QWidget>
#include<QTableWidget>
#include<QPushButton>
#include "ThirdForm.h"
#include<QBoxlayout>
#include<QPushButton>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QHeaderView>
#include"Database.h"

class ThirdForm : public QWidget
{
	Q_OBJECT
public:

	ThirdForm(QWidget *parent = Q_NULLPTR);
};

#endif