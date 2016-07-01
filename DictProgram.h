#ifndef DICTPROGRAM_H
#define DICTPROGRAM_H

#include <QtGui>
#include "dictionary.h"
#include "GVariables.h"
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
	DictProgram(QWidget *parent = 0, Qt::WFlags flags = 0) : QWidget(parent, flags), dict(GlobalVariables::getGlobalVariables().dicts[0])
	{
		ui.setupUi(this);
		ui.checkBox_0 ->setChecked(true); // общ.
		//ui.checkBox_1 ->setChecked(true); // разг.
		//ui.checkBox_2 ->setChecked(true); // комп.
		//ui.checkBox_3 ->setChecked(true); // политех.
		//ui.checkBox_4 ->setChecked(true); // биол.
		//ui.checkBox_5 ->setChecked(true); // медиц.
		//dict.setNameFiles(GlobalVariables::getGlobalVariables().dicts[0]);
		// выбор папки со словарём
		if (ui.checkBox_0 ->isChecked())
			dict.dirDict = GlobalVariables::getGlobalVariables().dicts[0];
		if (ui.checkBox_1 ->isChecked())
			dict.dirDict = GlobalVariables::getGlobalVariables().dicts[1];
		if (ui.checkBox_2 ->isChecked())
			dict.dirDict = GlobalVariables::getGlobalVariables().dicts[2];
		if (ui.checkBox_3 ->isChecked())
			dict.dirDict = GlobalVariables::getGlobalVariables().dicts[3];
		if (ui.checkBox_4 ->isChecked())
			dict.dirDict = GlobalVariables::getGlobalVariables().dicts[4];
		if (ui.checkBox_5 ->isChecked())
			dict.dirDict = GlobalVariables::getGlobalVariables().dicts[5];
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
	{}

	public slots:
		void translate()
		{
			QString word((ui.lineEdit ->text()).trimmed());
			QString translation = dict.getTr(word);
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
	Dictionary dict;

	Ui::DictionarysClass ui;
};



#endif