#ifndef DATABASE_H
#define DATABASE_H

#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include<QSqlError>
#include<QString>
#include<QDir>
#include<QMessageBox>
#include<QList>
#include"StudentInfo.h"
#include"honeyClass.h"
#include"qsqlrecord.h"

class DataBase:public QObject
{
	Q_OBJECT
public:
	static QSqlDatabase* readDatabase();//����ָ�����ݿ��ָ��
	static QList<StudentInfo> getStudentInfo();
	static QSqlDatabase database;//ָ�����ݿ��ָ��
};

#endif