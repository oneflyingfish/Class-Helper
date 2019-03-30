#include"Random.h"

int Random::random(int max)
{
	std::random_device rd;//硬件设备初始化种子,可惜windows上为rand_s
	std::default_random_engine e(rd());//设置引擎
	std::uniform_int_distribution<int> u(0,max-1);//表示均匀分布
	return u(e);
	/*qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
	return qrand() % max;*/
}

int Random::random(int min, int max)
{
	std::random_device rd;//硬件设备初始化种子,可惜windows上为rand_s
	std::default_random_engine e(rd());//设置引擎
	std::uniform_int_distribution<int> u(min, max-1);//表示均匀分布
	return u(e);
	/*qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
	return qrand() % (max - min) + min;*/
}

QList<StudentInfo> Random::sufferList(QList<StudentInfo>& infoList)
{
	QList<StudentInfo> shufferList;
	int times= infoList.count();
	for (int i = 0; i < times; i++)
	{
		int index = random(infoList.count());
		shufferList.append(infoList[index]);
		infoList.removeAt(index);
	}
	return shufferList;
}