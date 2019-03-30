#include <QtWidgets/QApplication>
#include "honeyClass.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	honeyClass w;
	w.show();
	return a.exec();
}
