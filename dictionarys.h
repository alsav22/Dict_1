#ifndef DICTIONARYS_H
#define DICTIONARYS_H

#include <QtGui>
#include "ui_dictionarys.h"

class Dictionarys : public QWidget
{
	Q_OBJECT

public:
	Dictionarys(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Dictionarys();
	
	void setNameFiles();
	bool parsingIdx();
	bool parsingIfo();
	bool createHash();
	bool loadHash();
	bool loadData();
	void HTMLfromString(QString& str);
	void formattingTr(QString& str);
	QString getTr(const QString& word);
	void outputTr(QString& translation);

protected:
	bool Dictionarys::event(QEvent* pe); // переключение на английский ввод при активном окне

	friend void getTagForDict(Dictionarys* p);

private:
	Ui::DictionarysClass ui;
	
	QHash <QString, QPair <quint32, quint32> > mHash;
	QString dirDict; // папка словаря
	QString fileIfo; // имя файла словаря .ifo
	QString fileIdx; // имя файла словаря .idx
	QString fileDict; // имя файла словаря .dict
	QString fileHash;
	QString fileParseIdx;
	QString fileParseIfo;
	QString ifoWordcount;   // первое поле из .ifo
	QString ifoIdxfilesize; // второе поле из .ifo
    quint32 offset; // под размер смещения
	quint32 size;   // под размер записи
	quint32 wordcount; // количество слов в словаре
	quint32 idxfilesize; // размер файла .idx

	QFile* mpFileDict; // объект для работы с файлом словаря .dict
	
public slots:
		void translate();
};

#endif // DICTIONARYS_H


