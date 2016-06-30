#include "Dictionary.h"
#include <QDebug>
#include <qregexp.h>
#include <QtGui>
#include <string>
#include <sstream>
#include <fstream>
#include "GVariables.h"

#ifdef Q_OS_LINUX
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#endif

#ifdef Q_OS_WIN32
#include <Windows.h>
#include <string>
#endif

Dictionary::Dictionary(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags), ifoWordcount("wordcount"), ifoIdxfilesize("idxfilesize"),
	  wordcount(0), idxfilesize(0), offset(0), size(0), mpFileDict(nullptr)
{
	//ui.setupUi(this);
	//ui.checkBox_0 ->setChecked(true); // ���.
	//ui.checkBox_1 ->setChecked(true); // ����.
	//ui.checkBox_2 ->setChecked(true); // ����.
	//ui.checkBox_3 ->setChecked(true); // �������.
	//ui.checkBox_4 ->setChecked(true); // ����.
	//ui.checkBox_5 ->setChecked(true); // �����.
	
	if (!loadData())
	{
		qDebug() << "Error loadData()!";
		//return;
	}
	//getTagForDict(this);
}

void Dictionary::setNameFiles()
{
	// ����� ����� �� �������
	if (ui.checkBox_0 ->isChecked())
		dirDict = GlobalVariables::getGlobalVariables().dicts[0];
	if (ui.checkBox_1 ->isChecked())
		dirDict = GlobalVariables::getGlobalVariables().dicts[1];
	if (ui.checkBox_2 ->isChecked())
		dirDict = GlobalVariables::getGlobalVariables().dicts[2];
	if (ui.checkBox_3 ->isChecked())
		dirDict = GlobalVariables::getGlobalVariables().dicts[3];
	if (ui.checkBox_4 ->isChecked())
		dirDict = GlobalVariables::getGlobalVariables().dicts[4];
	if (ui.checkBox_5 ->isChecked())
		dirDict = GlobalVariables::getGlobalVariables().dicts[5];

	QDir dir(dirDict);
	QStringList list = dir.entryList(QDir::Files | QDir::NoDotAndDotDot); // ������ ������ �� ����� �� �������
    
	// ����������, � ������� ������ �������, ��������������� ����� ������, � ������ �����������, �� ����� ������� 
	if (!list.empty())
	{
		foreach(QString s, list)
		{
			if (s.endsWith(".dict"))
				fileDict = dirDict + "/" + s;
	        else if (s.endsWith(".idx"))
				fileIdx  = dirDict + "/" + s;
			else if (s.endsWith(".ifo"))
				fileIfo  = dirDict + "/" + s;
		}
	}
	
	fileHash     = dirDict + "/" + "Hash.txt";
	fileParseIfo = dirDict + "/" + "parseIfo.txt";
	fileParseIdx = dirDict + "/" + "parseIdx.txt";
}

bool Dictionary::loadData()
{
	setNameFiles();
	
	if (!QFile::exists(fileParseIfo))
    if (!parsingIfo())
	{
		qDebug() << "Error parsingIfo()!";
		return false;
	}
	if (!QFile::exists(fileParseIdx))
    if (!parsingIdx())
	{
		qDebug() << "Error parsingIdx()!";
		return false;
	}
	if (!QFile::exists(fileHash))
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
	mpFileDict = new QFile(fileDict, this);
	if (!mpFileDict ->open(QIODevice::ReadOnly))
	{
		qDebug() << "Error opening " << fileDict << " !";
		return false;
	}
	return true;
}

void getTagForDict(Dictionary* p)
{
	QString str;
	QStringList strList;
	//QRegExp reg("(</?[a-z]+\\s?/?>)");
	QRegExp reg("(<k>.+</k>\\n ?<(?!tr))");
	QString tag;
	int pos;

	QFile fileIn(p ->fileParseIdx);
	
	if (fileIn.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		QTextStream in(&fileIn);
		int i;
		QString temp;
		while (true)
		{
			temp = in.readLine();
			in >> i >> i;
			in.read(1);
			str = p ->mpFileDict ->read(i);
			//str = p ->mpFileDict ->readLine();
			if (p ->mpFileDict ->atEnd())
				break;
			pos = 0;
			while ((pos = reg.indexIn(str, pos)) != -1)
			{
				
				tag = reg.cap(0);
				//p ->ui.textEdit ->setText(tag);
				if (!strList.contains(tag))
				{
					strList << tag;
					//qDebug() << tag;
				}
				pos += reg.matchedLength();
			}
		}
	}
	foreach(QString s, strList)
		p ->ui.textEdit ->append(s);//setText(s);
	
}

bool Dictionary::parsingIfo()
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

// �� .idx ����� ����������� ���� �������: ������ � ������ ����� ��� ��������, 
// ��������� ������ - ��� ����� ����� ������: �������� ��� ������� � ����� .dict �
// ������ �������� � ����� .dict
bool Dictionary::parsingIdx()
{
	QFile fileIn(fileIdx);
	QFile fileOut(fileParseIdx);
	if (fileIn.open(QIODevice::ReadOnly) && fileOut.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QDataStream in(&fileIn);
		QTextStream out(&fileOut); 
		QString str;
		
		while (!in.atEnd())
		{
			char ch ;
			if (in.readRawData(&ch, 1) == -1)
			{
				qDebug() << QWidget::tr("������ ������ �� .idx!");
				return false;
			}
			else
			{
				if (ch)
					str += ch;
				else
				{
					//ui.textEdit ->append(str);
					in >> offset >> size;
					out << str << '\n' << offset << " " << size << '\n'; 
					str.clear();
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

// �������� � ������ � ���� ���� �� ������ � .idx: ���� - ����� ��� ��������, �������� - ���� �� �������� � ������� ������� � .dict
bool Dictionary::createHash()
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
			//qDebug() << str;
			in >> offset;
			in >> size;
			in.read(1); // ������� �������(��) ����� ������ ����� readLine()

			mHash.insert(str, qMakePair(offset, size));
		}
		
		QDataStream out(&fileOut);
		out << mHash;
	    return true;
	}
	qDebug() << "Error createHash()!";
	return false;
}
// �������� ���� � ������� �� .idx
bool Dictionary::loadHash()
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

// �������������� ��������
void Dictionary::formattingTr(QString& str)
{
	str.replace(QRegExp("\n<tr>"), "<tr>"); // ������������ ��� �������� �� ��������� ������
	str.replace("<tr>", " <t>[");  // ��� <tr> �������� �� <t>, �����, ��� �������� � html,
	str.replace("</tr>", "]</t>"); // ���� ����� ����������; ������������ � [], 
	str.replace("\n", "<br />"); // 0x0A �������� �� ��� ����� ������
	str.remove(QRegExp("<rref>.+</rref>")); // ������ �� ������� ���������
	//str.replace("<c>", "<font color=\"red\">"); ��� ����� ������ ���� 
	// ��� ��������-������ �������� �� ��� html-�����������
	str.replace("<iref>", "<a>");
	str.replace("</iref>", "</a>");
	str.replace("web-site:", "<br />web-site:"); // "web-site:" � ����� ������
	
	// �������� �� ��������-������ html-�����������
	QRegExp reg("<a>(.+)</a>");
	QString href;
	int pos = 0;
	while ((pos = reg.indexIn(str, pos)) != -1)
	{
		href = reg.cap(1);
		str.replace(pos + 2, href.size() + 1, " href=\"" + href + "\">" + href);
		pos += reg.matchedLength();
	}
	qDebug() << str;
	
	HTMLfromString(str); // � html-����� (� CSS)
}

// �� QString � HTML-����� (������� ������ CSS)
void Dictionary::HTMLfromString(QString& str)
{
	QString begin("<html><head>");
	QString style("<style type=text/css>"
		          "k {font-weight: bold}"
				  "kref {font-weight: bold; font-style: oblique}"
				  "t {font-size: 5; font-family: \"Lucida Sans Unicode\"}"
				  "c {color: blue}");
	QString end("</style></head><body>" + str + "</body></html>");
	str = begin + style + end;
}

// ��������� ������� �� .dict
QString Dictionary::getTr(const QString& word)
{
	offset = 0;
	size = 0;
	QString translation = "";
	if (!word.isEmpty())
	{
		if (mHash.contains(word))
		{
			QPair <quint32, quint32> pair(mHash.value(word)); // ��������� �������� � ������� �� ����
			offset = pair.first;
			size   = pair.second;
			
			char* buffer = new char[size + 1]; // ����� ��� ������
			mpFileDict ->seek(0);
			mpFileDict ->seek(offset); // ������� � ��������
			mpFileDict ->read(buffer, size); // ������ ��������
			buffer[size] = '\0';
			
			translation = QString::fromUtf8(buffer); // ������ � QString �� UTF-8
			delete buffer;
			
			formattingTr(translation); // �������������� ��������
		}
	}
	return translation;
}

// ���� ��� ��������� ��������
void Dictionary::translate()
{
	QString word((ui.lineEdit ->text()).trimmed());
	QString translation = getTr(word);
	outputTr(translation);
}

// ����� ��������
void Dictionary::outputTr(QString& translation)
{
	ui.textEdit ->clear();
	if (!translation.isEmpty())
		ui.textEdit ->setText(translation);
	else
		ui.textEdit ->setText(QWidget::tr("����� �� �������!"));
}

// ������������ �� ���������� ���� ��� �������� ����
bool Dictionary::event(QEvent* pe) 
{
	if (pe ->type() == QEvent::WindowActivate)
	{
#ifdef Q_OS_WIN32
		
			qDebug() << "define Q_OS_WIN32";
			PostMessage(GetForegroundWindow(), WM_INPUTLANGCHANGEREQUEST, 1, 0x04090409);
			// LoadKeyboardLayout(L"00000409", KLF_ACTIVATE); // ��� ���
#endif

#ifdef Q_OS_LINUX
#ifdef DEBUG
qDebug() << "define Q_OS_LINUX";
#endif
			
			int xkbGroup = 0;
            int event_rtrn, error_rtrn, reason_rtrn;
            Display* display = XkbOpenDisplay(NULL, &event_rtrn, &error_rtrn,
                                              NULL, NULL, &reason_rtrn       );
            if(display == NULL)
            {
                #ifdef DEBUG
				qDebug() << "Cannot open display!";
                #endif
                return QWidget::event(pe);
            }
            XkbLockGroup(display, XkbUseCoreKbd, xkbGroup);
            XCloseDisplay(display);
#endif
	
	}
	return QWidget::event(pe);
	
}


Dictionary::~Dictionary()
{
	//delete mpFont;
}