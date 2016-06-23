// https://habrahabr.ru/post/161073/
//���������� ����������� ����, ������������ ������� StarDict
//
// ��� StarDict  ����� ������ �����, �� �������� ������������ ����� ������� ��, 
// ��� ��� ���� ���� ����� ����� ��������� ���, ����������� �� ���� ������. 
// ����, ����������� ������ StarDict, ������ ���������� ����� � ������ �����������.
// ���� ��������� ��� ����������, �� ����� ����������� ����� ������ �� ����� ������� ����� ���������:
// ������ ������� ������ ��������� � ���� 3 ������������ �����:
//
// 1. ���� � ����������� ifo  � �������� ���������������� �������� ������ �������;
// 2. ���� � ����������� idx . ������ ������ ������ idx ����� ������� �� 3-� �����, ������ ���� �� ������:
//     word_str � ������ � ������� utf-8, ��������������� '\0';
//     word_data_offset - �������� �� ������ � ����� .dict (������ ����� 32 ��� 64 ����);
//     word_data_size � ������ ���� ������ � ����� .dict.
//
// 3. ���� � ����������� dict � �������� ���� ��������, 
//    ��������� �� ������� ����� ���� �������� �� �������� (�������� �������� � ����� idx).
//...........................................................................................
// � ����� ������� ����� ������� ������������� (������� ����������) � file.ifo, file.idx, file.dict.
// ��� ������ ��� �������� � ������ ������ quint32 (32 ����). ���� ������, �� ��������,
// ��� ������������ QHash <QString, QPair <quint32, quint32> > mHash (� ���� ������ ���
// ��������, ������ - ������ ��������) � quint32 offset, quint32 size.
// ����� quint32: wordcount (���������� ���� � �������), � idxfilesize (������ ����� .idx)
	 
#include <QtGui>
#include "dictionarys.h"
#include <QtGui/QApplication>

#ifdef QT_DEBUG
#include <vld.h>
#include <Windows.h>
#endif

int main(int argc, char *argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	QApplication a(argc, argv);

	QTextCodec::setCodecForTr(QTextCodec::codecForName("CP1251"));

	Dictionarys w;
	w.show();
	return a.exec();
}
