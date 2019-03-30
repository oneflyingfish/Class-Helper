#ifndef RANDOM_H
#define RANDOM_H

#include<QList>
#include <QtGlobal>
#include<QTime>
#include<random>
#include"StudentInfo.h"

class Random
{
public:
	static int random(int max);
	static int random(int min, int max);
	static QList<StudentInfo> sufferList(QList<StudentInfo>& infoList);
};

#endif