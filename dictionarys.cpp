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
	  fileParseIfo("parseIfo.txt"), fileParseIdx("parseIdx.txt"), 
	  fileHash("Hash.txt"), ifoWordcount("wordcount"), ifoIdxfilesize("idxfilesize"),
	  wordcount(0), idxfilesize(0), offset(0), size(0), dict(nullptr), streamDict(nullptr)
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
	dict = new QFile(fileDict, this);
	if (!dict ->open(QIODevice::ReadOnly))
	{
		qDebug() << "Error opening " << fileDict << " !";
		return false;
	}
	streamDict = new QDataStream(dict);
	streamDict ->setVersion(QDataStream::Qt_4_8);
	return true;
}

bool Dictionarys::parsingIfo()
{
	QFile fileIn(fileIfo);
	QFile fileOut(fileParseIfo);
	if (fileIn.open(QIODevice::ReadOnly) && fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream in(&fileIn);
		QTextStream out(&fileOut); 
		QString str;
		QString number;
		while (true)
		{
			str = in.readLine();
			if (in.atEnd())
				break;
			if (str.startsWith(ifoWordcount))
			{
				number = str.mid(ifoWordcount.size() + 1);
				wordcount = number.toUInt();
				out << wordcount << endl;
			}
			if (str.startsWith(ifoIdxfilesize))
			{
				number = str.mid(ifoIdxfilesize.size() + 1);
				idxfilesize = number.toUInt();
				out << idxfilesize << endl;
			}
		}
		if (wordcount != 0 && idxfilesize != 0)
			return true;
	}
	
	qDebug() << "Error parsingIfo()!";
	return false;
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
					in >> offset >> size;
					out << str << '\n' << offset << " " << size << '\n'; 
					str.clear();
					//qDebug() << dec << i << " " << hex << offset << "  " << size;
					//++i;
				}
			}
		}
	}
	else
	{
		qDebug() << "Error parsingIdx()!";
		return false;
	}
	return true;
}

bool Dictionarys::createHash()
{
	QFile fileIn(fileParseIdx);
	QFile fileOut(fileHash);
	if (fileIn.open(QIODevice::ReadOnly | QIODevice::Text) && fileOut.open(QIODevice::WriteOnly))
	{
		QTextStream in(&fileIn); 
		QString str;
		offset = 0;
		size   = 0;
		while (true)
		{
			str = in.readLine();
			if (in.atEnd())
				break;
			in >> offset;
			in >> size;

			mHash.insert(str, qMakePair(offset, size));
		}
		
		QDataStream out(&fileOut);
		out << mHash;
	    return true;
	}
	qDebug() << "Error createHash()!";
	return false;
}

bool Dictionarys::loadHash()
{
	QFile fileIn(fileHash);
	if (fileIn.open(QIODevice::ReadOnly))
	{
		QDataStream in(&fileIn);
		in >> mHash;
		return true;
	}
	qDebug() << "Error loadHash()!";
	return false;
}

void Dictionarys::translate()
{
	QString word((ui.lineEdit ->text()).trimmed().toLower());
	
	offset = 0;
	size = 0;
	if (!word.isEmpty())
	{
		if (mHash.contains(word))
		{
			QPair <quint32, quint32> pair(mHash.value(word));
			offset = pair.first;
			size   = pair.second;

			ui.textEdit ->clear();
			//ui.textEdit ->setText(word + '\n' + QString::number(offset) + '\n' + QString::number(size));
			char* buffer = new char[size + 1];
			dict ->seek(0);
			dict ->seek(offset);
			//streamDict ->skipRawData(offset);
			dict ->read(buffer, size);
			buffer[size] = '\0';
			ui.textEdit ->setText(QString::fromUtf8(buffer));
			delete buffer;
		}
		else
		{
			ui.textEdit ->clear();
			ui.textEdit ->setText(QWidget::tr("Слово не найдено!"));
		}
	}
	else
	{
		ui.textEdit ->clear();
		ui.textEdit ->setText(QWidget::tr("Введите слово!"));
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

Dictionarys::~Dictionarys()
{
	delete streamDict;
}
