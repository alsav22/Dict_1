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
	DictProgram(QWidget *parent = 0, Qt::WFlags flags = 0) : QWidget(parent, flags)
	{
		ui.setupUi(this);
		ui.checkBox_0 ->setChecked(true); // общ. (по умолчанию)
		
		initialization();
	}

	void initialization()
	{
		mvectorNamesDicts.push_back(qMakePair(QString("stardict-ER-LingvoUniversal-2.4.2"), QString(QWidget::tr("ќбщей лексики"))));
		mvectorNamesDicts.push_back(qMakePair(QString("stardict-lingvo-ER-Informal-2.4.2"), QString(QWidget::tr("–азговорной лексики"))));
		mvectorNamesDicts.push_back(qMakePair(QString("stardict-lingvo-ER-Computer-2.4.2"), QString(QWidget::tr(" омпьютерный"))));
		mvectorNamesDicts.push_back(qMakePair(QString("stardict-lingvo-ER-Polytechnical-2.4.2"), QString(QWidget::tr("ѕолитехнический"))));
		mvectorNamesDicts.push_back(qMakePair(QString("stardict-lingvo-ER-Biology-2.4.2"), QString(QWidget::tr("Ѕиологический"))));
		mvectorNamesDicts.push_back(qMakePair(QString("stardict-lingvo-ER-Medical-2.4.2"), QString(QWidget::tr("ћедицинский"))));
		
		mvectorPointsToCheckBox.push_back(ui.checkBox_0); // общ.
		mvectorPointsToCheckBox.push_back(ui.checkBox_1); // разг.
		mvectorPointsToCheckBox.push_back(ui.checkBox_2); // комп.
		mvectorPointsToCheckBox.push_back(ui.checkBox_3); // политех.
		mvectorPointsToCheckBox.push_back(ui.checkBox_4); // биол.
		mvectorPointsToCheckBox.push_back(ui.checkBox_5); // медиц.
		
		for (int i = 0; i < mvectorNamesDicts.size(); ++i)
		{
			Dictionary* pdict = new Dictionary(mvectorNamesDicts[i].first, mvectorNamesDicts[i].second);
			mvectorPointsToDicts.push_back(pdict);
		}
	}
	// из QString в HTML-текст (задание стилей CSS)
	void HTMLfromString(QString& str)
	{
		QString begin("<html><head>");
		QString style("<style type=text/css>"
					  "k {font-weight: bold}"
					  "kref {color: #008080; font-size: 5; font-weight: bold}"
					  "t {font-size: 5; font-family: \"Lucida Sans Unicode\"}"
					  "c {color: blue}");
		QString end("</style></head><body>" + str + "</body></html>");
		str = begin + style + end;
	}
	// форматирование перевода
	void formattingTr(QString& str, QString name)
	{
		str.replace(QRegExp("\n<tr>"), "<tr>"); // транскрипци€ без переноса на следующую строку
		str.replace("<tr>", " <t>[");  // тег <tr> мен€етс€ на <t>, иначе, при переводе в html,
		str.replace("</tr>", "]</t>"); // этот текст вырезаетс€; транскрипцию в [], 
		str.replace("\n", "<br />"); // 0x0A мен€етс€ на тег новой строки
		str.remove(QRegExp("<rref>.+</rref>")); // ссылки на ресурсы удал€ютс€
		//str.replace("<c>", "<font color=\"red\">"); так можно задать цвет 
		// тег интернет-ссылки мен€етс€ на тег html-гиперссылки
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
		// добавление сокращЄнного имени словар€
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
		for (int i = 0; i < mvectorPointsToDicts.size(); ++i)
		{
			if (mvectorPointsToCheckBox[i] ->checkState() == Qt::Checked) // если словарь выбран
			{
				QString temp = mvectorPointsToDicts[i] ->getTr(word); // получение перевода от этого словар€
				if (!temp.isEmpty())
				{
					formattingTr(temp, mvectorPointsToDicts[i] ->getName());
					translation.append(temp); // суммирование переводов от разных словарей
				}
			}
		}
	}

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
			ui.textEdit ->setText(QWidget::tr("—лово не найдено!"));
	}
	
	~DictProgram()
	{
		for (int i = 0; i < mvectorPointsToDicts.size(); ++i)
		{
			delete mvectorPointsToDicts[i];
		}
	}

protected:
	// ѕереключение на английский ввод при активном окне
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
	QVector <Dictionary*> mvectorPointsToDicts; // контейнер с указател€ми на словари
	QVector <QCheckBox*> mvectorPointsToCheckBox; // контейнер с указател€ми на чек-боксы
	Ui::DictionarysClass ui;
};



#endif