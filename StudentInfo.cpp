#include"StudentInfo.h"

StudentInfo::StudentInfo(int index, QString id, QString name, QString sex, QString Place)
{
	this->id = id;
	this->name = name;
	this->index = index;
	this->sex = sex;
	this->Place = Place;
}
QString StudentInfo::getId()
{
	return this->id;
}
int StudentInfo::getIndex()
{
	return this->index;
}

QString StudentInfo::getName()
{
	return this->name;
}

QString StudentInfo::getSex()
{
	return this->sex;
}

QString StudentInfo::getPlace()
{
	return this->Place;
}