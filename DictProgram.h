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
		ui.checkBox_0 ->setChecked(true); // общ. (по умолчанию)
		
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
////////////////////////// Блок используется с чек-боксами GUI, объединёнными в groupBox		
		if (mNumberDicts != ui.groupBox ->children().size())
		{
			qDebug() << "The number of dictionaries does not match the number of check-boxes!";
			return false;
		}
		
		foreach(QObject* p, ui.groupBox ->children())
		{
			//qDebug() << p ->objectName();
			mvectorPointsToCheckBox.push_back(static_cast <QCheckBox*>(p));
		}
///////////////////////////
		
		for (int i = 0; i < mNumberDicts; ++i)
		{
			Dictionary* pdict = new Dictionary(mvectorNamesDicts[i].first, mvectorNamesDicts[i].second);
			mvectorPointsToDicts.push_back(pdict);
		}
		return true;
	}
	
	// задание стилей CSS)
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
	// форматирование перевода
	void formattingTr(QString& str, QString name)
	{
		str.replace(QRegExp("\n<tr>"), "<tr>"); // транскрипция без переноса на следующую строку
		str.replace("<tr>", " <t>[");  // тег <tr> меняется на <t>, иначе, при переводе в html,
		str.replace("</tr>", "]</t>"); // этот текст вырезается; транскрипцию в [], 
		str.replace("\n", "<br />"); // 0x0A меняется на тег новой строки
		//str.remove(QRegExp("<rref>([a-zA-Z0-9. -])+</rref>")); // ссылки на ресурсы удаляются
		str.remove(QRegExp("<rref>[^<]+</rref>")); // ссылки на ресурсы удаляются
		//str.replace("<c>", "<font color=\"red\">"); так можно задать цвет 
		// тег интернет-ссылки меняется на тег html-гиперссылки
		str.replace("<iref>", "<a>");
		str.replace("</iref>", "</a>");
		str.replace("web-site:", "<br />web-site:"); // "web-site:" с новой строки
	
		// создание из интернет-ссылки html-гиперссылки
		QRegExp reg("<a>(.+)</a>");
		QString href;
		int pos = 0;
		while ((pos = reg.indexIn(str, pos)) != -1)
		{
			href = reg.cap(1);
			str.replace(pos + 2, href.size() + 1, " href=\"" + href + "\">" + href);
			pos += reg.matchedLength();
		}
		// добавление сокращённого имени словаря
		QString ins = "&nbsp;&nbsp;&nbsp;&nbsp;<font color=\"#ff00ff\"><b><i>" + name + "</i></b></font><br />";
		str.insert(0, ins);
		str.push_back("<br />");
		//qDebug() << str;
	
		HTMLfromString(str); // в html-текст (с CSS)
	}
	// получение первода (из нескольких словарей) слова word в строку translation
	void translate(const QString& word, QString& translation)
	{
		translation.clear();
		for (int i = 0; i < mNumberDicts; ++i)
		{
			if (mvectorPointsToCheckBox[i] ->checkState() == Qt::Checked) // если словарь выбран
			{
				QString temp = mvectorPointsToDicts[i] ->getTr(word); // получение перевода от этого словаря
				if (!temp.isEmpty())
				{
					formattingTr(temp, mvectorPointsToDicts[i] ->getName());
					translation.append(temp); // суммирование переводов от разных словарей
				}
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
	// вывод перевода
	void outputTr(QString& translation)
	{
		ui.textEdit ->clear();
		if (!translation.isEmpty())
			ui.textEdit ->setText(translation);
		else
			ui.textEdit ->setText(QWidget::tr("Слово не найдено!"));
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
	// Переключение на английский ввод при активном окне
bool event(QEvent* pe) 
{
	if (pe ->type() == QEvent::WindowActivate)
	{
#ifdef Q_OS_WIN32
		
			qDebug() << "define Q_OS_WIN32";
			PostMessage(GetForegroundWindow(), WM_INPUTLANGCHANGEREQUEST, 1, 0x04090409);
			// LoadKeyboardLayout(L"00000409", KLF_ACTIVATE); // или так
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
	QVector <QPair <QString, QString> > mvectorNamesDicts; // контейнер с именами словарей (папок)
	QVector <Dictionary*> mvectorPointsToDicts; // контейнер с указателями на словари
	QVector <QCheckBox*> mvectorPointsToCheckBox; // контейнер с указателями на чек-боксы
	quint8 mNumberDicts;
	Ui::DictionarysClass ui;
};



#endif