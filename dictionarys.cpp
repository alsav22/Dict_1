#include "dictionarys.h"
#include <QDebug>
#include <qregexp.h>
#include <QtGui>
#include <string>
#include <sstream>
#include <fstream>

Dictionarys::Dictionarys(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags), fileIfo("file.ifo"), fileIdx("file.idx"), fileDict("file.dict")
{
	ui.setupUi(this);
	
}

bool Dictionarys::parsingIdx()
{
	
	return true;
}

bool Dictionarys::createHash()
{
	
	return true;
}

bool Dictionarys::loadHash()
{
	
	return true;
}

void Dictionarys::translate()
{
	QFile fileIn("file.idx");
	QFile fileOut("out.txt");
	if (fileIn.open(QIODevice::ReadOnly) && fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QDataStream in(&fileIn);
		QTextStream out(&fileOut); 
		QString str;
		//int i = 1;
		while (!in.atEnd())
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
					quint32 n = 0;
					quint32 m = 0;
					in >> n >> m;
					out << str << '\n' << n << " " << m << '\n'; 
					str.clear();
					//qDebug() << dec << i << " " << hex << n << "  " << m;
					//++i;
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
