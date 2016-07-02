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
		ui.checkBox_0 ->setChecked(true); // общ.
		
		initialization();
	}

	void initialization()
	{
		mvectorNamesDicts.push_back(qMakePair(QString("stardict-ER-LingvoUniversal-2.4.2"), QString(QWidget::tr("Общей лексики"))));
		mvectorNamesDicts.push_back(qMakePair(QString("stardict-lingvo-ER-Informal-2.4.2"), QString(QWidget::tr("Разговорной лексики"))));
		mvectorNamesDicts.push_back(qMakePair(QString("stardict-lingvo-ER-Computer-2.4.2"), QString(QWidget::tr("Компьютерный"))));
		mvectorNamesDicts.push_back(qMakePair(QString("stardict-lingvo-ER-Polytechnical-2.4.2"), QString(QWidget::tr("Политехнический"))));
		mvectorNamesDicts.push_back(qMakePair(QString("stardict-lingvo-ER-Biology-2.4.2"), QString(QWidget::tr("Биологический"))));
		mvectorNamesDicts.push_back(qMakePair(QString("stardict-lingvo-ER-Medical-2.4.2"), QString(QWidget::tr("Медицинский"))));
		
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

	public slots:
		void translate()
		{
			QString word((ui.lineEdit ->text()).trimmed());
			QString translation;
			for (int i = 0; i < mvectorPointsToDicts.size(); ++i)
			{
				if (mvectorPointsToCheckBox[i] ->checkState() == Qt::Checked) // если словарь выбран
				{
					 QString temp = mvectorPointsToDicts[i] ->getTr(word); // получение перевода от этого словаря
					 if (!temp.isEmpty())
					 {
						translation.append(temp); // суммирование переводов от разных словарей
					 }
				}
			}
			outputTr(translation);
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
	}
	
	~DictProgram()
	{
		for (int i = 0; i < mvectorPointsToDicts.size(); ++i)
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
	Ui::DictionarysClass ui;
};



#endif