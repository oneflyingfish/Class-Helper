#include"Random.h"

int Random::random(int max)
{
	std::random_device rd;//Ӳ���豸��ʼ������,��ϧwindows��Ϊrand_s
	std::default_random_engine e(rd());//��������
	std::uniform_int_distribution<int> u(0,max-1);//��ʾ���ȷֲ�
	return u(e);
	/*qsrand(QTime(0, 0, 0).msecsTo(QTime::currentTime()));
	return qrand() % max;*/
}

int Random::random(int min, int max)
{
	std::random_device rd;//Ӳ���豸��ʼ������,��ϧwindows��Ϊrand_s
	std::default_random_engine e(rd());//��������
	std::uniform_int_distribution<int> u(min, max-1);//��ʾ���ȷֲ�
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