#ifndef STUDENTINFO_H
#define STUDENTINFO_H
#include<QString>
class StudentInfo
{
public:
	StudentInfo(int index, QString id, QString name, QString sex, QString Place);
	QString getId();
	int getIndex();
	QString getName();
	QString getSex();
	QString getPlace();
private:
	int index;
	QString id;
	QString name;
	QString sex;
	QString Place;
};

#endif