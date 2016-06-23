#ifndef DICTIONARYS_H
#define DICTIONARYS_H

#include <QtGui/QWidget>
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
	
	QPair <quint32, quint32> mPair;
	QHash <QString, QPair <quint32, quint32> > mHash;
	QString fileIfo;
	QString fileIdx;
	QString fileDict;
	QString fileHash;
	QString fileParseIdx;
	QString fileParseIfo;
	QString ifoExtractOne;
	QString ifoExtractTwo;

	quint32 wordcount; // ���������� ���� � �������
	quint32 idxfilesize; // ������ ����� .idx
	
public slots:
		void translate();
};

#endif // DICTIONARYS_H
