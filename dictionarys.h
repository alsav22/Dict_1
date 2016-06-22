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

private:
	Ui::DictionarysClass ui;

	public slots:
		void translate();
};

#endif // DICTIONARYS_H
