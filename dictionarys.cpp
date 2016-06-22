#include "dictionarys.h"
#include <QDebug>

Dictionarys::Dictionarys(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
}

void Dictionarys::translate()
{
	qDebug() << "translate()";
	ui.textEdit ->setText(ui.lineEdit ->text());
}

Dictionarys::~Dictionarys()
{

}
