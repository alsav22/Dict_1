#include "dictionarys.h"
#include <QDebug>
#include <qregexp.h>
#include <QtGui>
#include <string>
#include <sstream>
#include <fstream>

Dictionarys::Dictionarys(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
}

void Dictionarys::translate()
{
	QFile file("file.idx");
	
	if (file.open(QIODevice::ReadOnly))
	{
		QDataStream in(&file);
		
		QString str;
		
		for (int i = 0; i < 300; ++i)
		{
			char ch ;
			if (in.readRawData(&ch, 1) == -1)
				qDebug() << QWidget::tr("Ошибка чтения!");
			else
			{
				if (ch)
					str += ch;
				else
				{
					ui.textEdit ->append(str);
					str.clear();
				
					quint32 n = 0;
					quint32 m = 0;
					in >> n >> m;
					qDebug() << hex << n << "  " << m;
					i += 7;
				}
			}
		}
			

	//	
	//	char ch = 'a';
	////
	////QString word(ui.lineEdit ->text());

	////QRegExp reg5("<ar>.*<k>(.+)</k>.*(?:<tr>.+</tr>)(.+)</ar>");
	////int pos;
	////QString en;
	////QString ru;
	////if ((pos = reg5.indexIn(str)) > -1)
	////{
	////	en = reg5.cap(1);
	////	qDebug() << en.trimmed();
	////	ru = reg5.cap(2);
	////	qDebug() << ru.trimmed();
	////	//qDebug() << reg6.cap(0);
	////	//qDebug() << reg6.cap(1);
	////	/*qDebug() << reg6.cap(2);
	////	qDebug() << reg6.cap(3);
	////	qDebug() << reg6.cap(2) + reg6.cap(3);*/
	////}
	}
	else
		qDebug() << "Error!";

}

Dictionarys::~Dictionarys()
{

}
