#include"Database.h"

extern QString currentClassName;
extern QList<StudentInfo> currentStudentList;
QSqlDatabase DataBase::database;

QSqlDatabase* DataBase::readDatabase()
{
	database = QSqlDatabase::addDatabase("QSQLITE");
	database.setDatabaseName("ClassInformation.db");
	//database = QSqlDatabase::addDatabase("QODBC");
	//database.setDatabaseName("DRIVER={Microsoft Access Driver (*.mdb, *.accdb)};FIL={MS Access};DBQ="+QDir().currentPath()+"/ClassInformation.mdb");//E:/freework/C++ program language/QT/honeyClass/honeyClass/
	if (!database.open())
	{
		QSqlError error;
		error = database.lastError();
		if (error.isValid())//��������ʱisValid()����true  
		{
			switch (error.type()) {
			case QSqlError::NoError:
				QMessageBox::information(NULL, "����", "���ݿ�����ʧ�ܣ����ܴ����ļ���ʧ����", QMessageBox::YesRole);
				break;
			case QSqlError::ConnectionError://���Ӵ���  
				QMessageBox::information(NULL, "����", error.text(), QMessageBox::YesRole);
				break;
			case QSqlError::StatementError://������  
				QMessageBox::information(NULL, "����", error.text(), QMessageBox::YesRole);
				break;
			case QSqlError::TransactionError://������� 
				QMessageBox::information(NULL, "����", error.text(), QMessageBox::YesRole);
				break;
			default://δ֪����  
				QMessageBox::information(NULL, "����", "δ֪����"+error.text(), QMessageBox::YesRole);
				break;
			}
		}
		QMessageBox::information(NULL, "����", "���ݿ�����ʧ�ܣ����ܴ����ļ���ʧ����", QMessageBox::YesRole);
		exit(1);
		return NULL;
	}
	return &database;
}

QList<StudentInfo> DataBase::getStudentInfo()
{
	
	QSqlDatabase* database = readDatabase();
	QSqlQuery* query = new QSqlQuery(*database);
	query->exec("select * from " + currentClassName);
	QList<StudentInfo> studentInfoList;
	int i = 0;
	while(query->next() != false)
	{
		StudentInfo studentinfo(i++, query->value(0).toString(), query->value(1).toString(), query->value(2).toString(), query->value(3).toString());
		studentInfoList.append(studentinfo);
	}
	database->close();
	return studentInfoList;
}