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

	friend void getTagForDict(Dictionarys* p);

private:
	Ui::DictionarysClass ui;
	
	QHash <QString, QPair <quint32, quint32> > mHash;
	QString dirDict; // ����� �������
	QString fileIfo; // ��� ����� ������� .ifo
	QString fileIdx; // ��� ����� ������� .idx
	QString fileDict; // ��� ����� ������� .dict
	QString fileHash;
	QString fileParseIdx;
	QString fileParseIfo;
	QString ifoWordcount;   // ������ ���� �� .ifo
	QString ifoIdxfilesize; // ������ ���� �� .ifo
    quint32 offset; // ��� ������ ��������
	quint32 size;   // ��� ������ ������
	quint32 wordcount; // ���������� ���� � �������
	quint32 idxfilesize; // ������ ����� .idx

	QFile* mpFileDict; // ������ ��� ������ � ������ ������� .dict
	
public slots:
		void translate();
};

#endif // DICTIONARYS_H


