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
	bool parsingIdx();
	bool parsingIfo();
	bool createHash();
	bool loadHash();
	bool loadData();

private:
	Ui::DictionarysClass ui;
	
	QHash <QString, QPair <quint32, quint32> > mHash;
	QString fileIfo;
	QString fileIdx;
	QString fileDict;
	QString fileHash;
	QString fileParseIdx;
	QString fileParseIfo;
	QString ifoWordcount;   // первое поле из .ifo
	QString ifoIdxfilesize; // второе поле из .ifo
    quint32 offset; // под размер смещения
	quint32 size;   // под размер записи
	quint32 wordcount; // количество слов в словаре
	quint32 idxfilesize; // размер файла .idx

	QFile* dict;
	QDataStream* streamDict;
	
public slots:
		void translate();
};

#endif // DICTIONARYS_H
