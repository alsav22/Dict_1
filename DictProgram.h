#ifndef DICTPROGRAM_H
#define DICTPROGRAM_H

#include <QtGui>
#include "dictionary.h"
#include "ui_dictionarys.h"


#ifdef Q_OS_LINUX
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/XKBlib.h>
#endif

#ifdef Q_OS_WIN32
#include <Windows.h>
#include <string>
#endif

class DictProgram : public QWidget
{
	Q_OBJECT

public:
	DictProgram(QWidget *parent = 0, Qt::WFlags flags = 0) : QWidget(parent, flags), mNumberDicts(0)
	{
		ui.setupUi(this);
		ui.checkBox_0 ->setChecked(true); // ���. (�� ���������)
		
		if (!initialization())
		{
			qDebug() << "Error initialization()!";
		}
	}

	bool initialization()
	{
		QFile fileIn("DirsDicts.txt");
		if (!fileIn.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			qDebug() << "Error opening file DirsDicts.txt!";
			return false;
		}
		QTextStream rd(&fileIn);
		QString DirDict;
		QString NameForOut;
		while (true)
		{
			DirDict = rd.readLine();
			if (rd.atEnd())
				break;
			NameForOut = rd.readLine();
			
			mvectorNamesDicts.push_back(qMakePair(DirDict, NameForOut));
		}
		
		mNumberDicts = mvectorNamesDicts.size();
		if (mNumberDicts == 0)
		{
			qDebug() << "The dictionaries are not found!";
			return false;
		}
////////////////////////// ���� ������������ � ���-������� GUI, ������������ � groupBox		
		if (mNumberDicts != ui.groupBox ->children().size())
		{
			qDebug() << "The number of dictionaries does not match the number of check-boxes!";
			return false;
		}
		
		//foreach(QObject* p, ui.groupBox ->children())
		//{
		//	//qDebug() << p ->objectName();
		//	//qDebug() << ((QCheckBox*)p) ->text();
		//	// ��������� �� ���-����� ���������� � ���������
		//	mvectorPointsToCheckBox.push_back(static_cast <QCheckBox*>(p));
		//}
///////////////////////////
		
		for (int i = 0; i < mNumberDicts; ++i)
		{
			Dictionary* pdict = new Dictionary(mvectorNamesDicts[i].first, mvectorNamesDicts[i].second);
			mvectorPointsToDicts.push_back(pdict);
		}
		return true;
	}
	
	// ��������� ��� ������� ��� ������ (��������� � ������� ���������������� ���-�����)
	// ���������� ��������� �� ��������������� ���-����
	QCheckBox* getPointerToCheckBox(const QString text) 
	{
		QObjectList list = ui.groupBox ->children();
		foreach(QObject* p, list)
		{
			if (static_cast<QCheckBox*>(p) ->text() == text)
				return static_cast<QCheckBox*>(p);
		}
		return nullptr;
	}
	
	// ������� ������ CSS)
	void HTMLfromString(QString& str)
	{
		//QString begin("<html><head>");
		QString style("<style type=text/css>"
					  "k {font-weight: bold}"
					  "kref {color: #008080; font-size: 5; font-weight: bold}"
					  "t {font-size: 5; font-family: \"Lucida Sans Unicode\"}"
					  "c {color: blue}"
					  "</style>");
		//QString end("</style></head><body>" + str + "</body></html>");
		//QString end("</style></head>" + str);
		//str = begin + style + end;
		str = style + str;
		
	}
	// �������������� ��������
	void formattingTr(QString& str, QString name)
	{
		str.replace(QRegExp("\n<tr>"), "<tr>"); // ������������ ��� �������� �� ��������� ������
		str.replace("<tr>", " <t>[");  // ��� <tr> �������� �� <t>, �����, ��� �������� � html,
		str.replace("</tr>", "]</t>"); // ���� ����� ����������; ������������ � [], 
		str.replace("\n", "<br />"); // 0x0A �������� �� ��� ����� ������
		//str.remove(QRegExp("<rref>([a-zA-Z0-9. -])+</rref>")); // ������ �� ������� ���������
		str.remove(QRegExp("<rref>[^<]+</rref>")); // ������ �� ������� ���������
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
		// ���������� ������������ ����� �������
		QString ins = "&nbsp;&nbsp;&nbsp;&nbsp;<font color=\"#ff00ff\"><b><i>" + name + "</i></b></font><br />";
		str.insert(0, ins);
		str.push_back("<br />");
		//qDebug() << str;
	
		HTMLfromString(str); // � html-����� (� CSS)
	}
	// ��������� ������� (�� ���������� ��������) ����� word � ������ translation
	void translate(const QString& word, QString& translation)
	{
		translation.clear();
		for (int i = 0; i < mNumberDicts; ++i)
		{
			QCheckBox* pCheckBox = getPointerToCheckBox(mvectorPointsToDicts[i] ->getName());
			if (pCheckBox)
			{
				if (pCheckBox ->checkState() == Qt::Checked)
				//if (mvectorPointsToCheckBox[i] ->checkState() == Qt::Checked) // ���� ������� ������
				{
					QString temp = mvectorPointsToDicts[i] ->getTr(word); // ��������� �������� �� ����� �������
					if (!temp.isEmpty())
					{
						formattingTr(temp, mvectorPointsToDicts[i] ->getName());
						translation.append(temp); // ������������ ��������� �� ������ ��������
					}
				}
			}
			else
			{
				qDebug() << "The dictionaries are not found to the check boxs!";
				return;
			}

		}
	}
	quint8 getNumberDicts()
	{ return mNumberDicts; }
	void setNumberDicts(quint8 number)
	{ mNumberDicts = number; }

	public slots:
		void translate()
		{
			QString word = ui.lineEdit ->text().trimmed();
			QString tr;
			translate(word, tr); 
			outputTr(tr);
		}
public:	
	// ����� ��������
	void outputTr(QString& translation)
	{
		ui.textEdit ->clear();
		if (!translation.isEmpty())
			ui.textEdit ->setText(translation);
		else
			ui.textEdit ->setText(QWidget::tr("����� �� �������!"));
		qDebug() << ui.textEdit ->toHtml();
	}
	
	~DictProgram()
	{
		for (int i = 0; i < mNumberDicts; ++i)
		{
			delete mvectorPointsToDicts[i];
		}
	}

protected:
	// ������������ �� ���������� ���� ��� �������� ����
bool event(QEvent* pe) 
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

private:
	QVector <QPair <QString, QString> > mvectorNamesDicts; // ��������� � ������� �������� (�����)
	QVector <Dictionary*> mvectorPointsToDicts; // ��������� � ����������� �� �������
	//QVector <QCheckBox*> mvectorPointsToCheckBox; // ��������� � ����������� �� ���-�����
	quint8 mNumberDicts;
	Ui::DictionarysClass ui;
};



#endif