#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <QtGui>
#include "ui_dictionarys.h"

class Dictionary 
{
	friend class DictProgram;

public:
	Dictionary(const QString& dirName);
	~Dictionary();
	
	void setNameFiles();
	bool parsingIdx();
	bool parsingIfo();
	bool createHash();
	bool loadHash();
	bool loadData();
	void HTMLfromString(QString& str);
	void formattingTr(QString& str);
	QString getTr(const QString& word);
	
protected:
	friend void getTagForDict(Dictionary* p);

private:
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
};
	
#endif // DICTIONARY_H


