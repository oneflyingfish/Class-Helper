#ifndef SECONDFORN_H
#define SECONDFORN_H

#include <QtWidgets/QWidget>
#include<QCheckBox>
#include<QRadioButton>
#include<QBoxLayout>
#include<QPushButton>
#include<QCheckBox.h>
#include<QPushButton>
#include<QBoxLayout>
#include"honeyClass.h"
#include"Random.h"

class SecondForm : public QWidget
{
	Q_OBJECT
public:
	SecondForm(QWidget *parent = Q_NULLPTR,int a=1);
};

#endif