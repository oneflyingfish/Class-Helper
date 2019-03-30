#ifndef FIRSTFORM_H
#define FIRSTFORM_H

#include <QtWidgets/QWidget>
#include<QLayout>
#include<QBoxLayout>
#include<QLabel>
#include<QPushButton>
#include<QSpacerItem>
#include<QList>
#include"StudentInfo.h"
#include"Database.h"

extern 	QList<StudentInfo> currentStudentList;

class FirstForm : public QWidget
{
	Q_OBJECT
public:
	FirstForm(QWidget *parent = Q_NULLPTR);
	~FirstForm();
	void setSeatsText(QList<StudentInfo> studentsList);
	void setDifferentColor(int index);
	void recoverColor();
private:
	int rowNumber;
	QLabel** seats;
};

#endif
