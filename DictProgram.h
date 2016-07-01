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
		dicts << "stardict-ER-LingvoUniversal-2.4.2" << "stardict-lingvo-ER-Informal-2.4.2"
			  << "stardict-lingvo-ER-Computer-2.4.2" << "stardict-lingvo-ER-Polytechnical-2.4.2"
			  << "stardict-lingvo-ER-Biology-2.4.2"  << "stardict-lingvo-ER-Medical-2.4.2";
		
		
		ui.setupUi(this);
		//ui.checkBox_0 ->setChecked(true); // общ.
		//ui.checkBox_1 ->setChecked(true); // разг.
		//ui.checkBox_2 ->setChecked(true); // комп.
		//ui.checkBox_3 ->setChecked(true); // политех.
		//ui.checkBox_4 ->setChecked(true); // биол.
		//ui.checkBox_5 ->setChecked(true); // медиц.
		
		for (int i = 0; i < dicts.size(); ++i)
		{
			Dictionary* pdict = new Dictionary(dicts[i]);
			mvectorPointsToDicts.push_back(pdict);
		}
	}

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

	public slots:
		void translate()
		{
			QString word((ui.lineEdit ->text()).trimmed());
			QString translation;
			for (int i = 0; i < mvectorPointsToDicts.size(); ++i)
			{
				 QString temp = mvectorPointsToDicts[i] ->getTr(word);
				 if (!temp.isEmpty())
				 {
					temp += "///////////////////////<br />";
					translation.append(temp);
				 }
			}
			outputTr(translation);
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
	QStringList dicts; // имена словарей (папок)
	QVector <Dictionary*> mvectorPointsToDicts; // контейнер с указателями на словари

	Ui::DictionarysClass ui;
};



#endif