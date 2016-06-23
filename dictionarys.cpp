#include "dictionarys.h"
#include <QDebug>
#include <qregexp.h>
#include <QtGui>
#include <string>
#include <sstream>
#include <fstream>

Dictionarys::Dictionarys(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags), fileIfo("file.ifo"), 
	  fileIdx("file.idx"), fileDict("file.dict"), 
	  fileParseIfo("parseIfo.txt"), fileParseIdx("parseIdx.txt"), fileHash("Hash.txt")
{
	ui.setupUi(this);
	
	if (!loadData())
	{
		qDebug() << "Error loadData()!";
		//return;
	}
}

bool Dictionarys::loadData()
{
	if (!QDir::current().exists(fileParseIfo))
    if (!parsingIfo())
	{
		qDebug() << "Error parsingIfo()!";
		return false;
	}
	if (!QDir::current().exists(fileParseIdx))
    if (!parsingIdx())
	{
		qDebug() << "Error parsingIdx()!";
		return false;
	}
	if (!QDir::current().exists(fileHash))
    if (!createHash())
	{
		qDebug() << "Error createHash()!";
		return false;
	}
	
	if (!loadHash())
	{
		qDebug() << "Error loadHash()!";
		return false;
	}
	return true;
}

bool Dictionarys::parsingIfo()
{
	
	return true;
}

bool Dictionarys::parsingIdx()
{
	QFile fileIn(fileIdx);
	QFile fileOut(fileParseIdx);
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
			{
				qDebug() << QWidget::tr("Ошибка чтения!");
				return false;
			}
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
	}
	else
	{
		qDebug() << "Error!";
		return false;
	}
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

Dictionarys::~Dictionarys()
{

}
