#include <QtGui>
#include "dictionarys.h"
#include <QtGui/QApplication>


#ifdef QT_DEBUG
#include <vld.h>
#include <Windows.h>
#endif

int main(int argc, char *argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	QApplication a(argc, argv);

	QTextCodec::setCodecForTr(QTextCodec::codecForName("CP1251"));

	Dictionarys w;
	w.show();
	return a.exec();
}
