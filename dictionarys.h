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
	bool createHash();
	bool loadHash();

private:
	Ui::DictionarysClass ui;
	
	QPair <quint32, quint32> mPair;
	QHash <QString, QPair <quint32, quint32> > mHash;
	QString fileIfo;
	QString fileIdx;
	QString fileDict;

	public slots:
		void translate();
};

#endif // DICTIONARYS_H
