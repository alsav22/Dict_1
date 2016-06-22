#include "dictionarys.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	Dictionarys w;
	w.show();
	return a.exec();
}
