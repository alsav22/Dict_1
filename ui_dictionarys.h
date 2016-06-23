/********************************************************************************
** Form generated from reading UI file 'dictionarys.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DICTIONARYS_H
#define UI_DICTIONARYS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DictionarysClass
{
public:
    QLineEdit *lineEdit;
    QTextEdit *textEdit;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *DictionarysClass)
    {
        if (DictionarysClass->objectName().isEmpty())
            DictionarysClass->setObjectName(QString::fromUtf8("DictionarysClass"));
        DictionarysClass->resize(676, 456);
        lineEdit = new QLineEdit(DictionarysClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(35, 79, 231, 36));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(11);
        lineEdit->setFont(font);
        textEdit = new QTextEdit(DictionarysClass);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(310, 80, 326, 341));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Lucida Sans Unicode"));
        font1.setPointSize(10);
        textEdit->setFont(font1);
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textEdit->setReadOnly(true);
        label = new QLabel(DictionarysClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(35, 38, 246, 21));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(9);
        label->setFont(font2);
        label_2 = new QLabel(DictionarysClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(320, 40, 96, 19));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Arial"));
        font3.setPointSize(10);
        label_2->setFont(font3);

        retranslateUi(DictionarysClass);
        QObject::connect(lineEdit, SIGNAL(returnPressed()), DictionarysClass, SLOT(translate()));

        QMetaObject::connectSlotsByName(DictionarysClass);
    } // setupUi

    void retranslateUi(QWidget *DictionarysClass)
    {
        DictionarysClass->setWindowTitle(QApplication::translate("DictionarysClass", "Dictionarys", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DictionarysClass", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\260\320\275\320\263\320\273\320\270\320\271\321\201\320\272\320\276\320\265 \321\201\320\273\320\276\320\262\320\276:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DictionarysClass", "\320\237\320\265\321\200\320\265\320\262\320\276\320\264:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DictionarysClass: public Ui_DictionarysClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DICTIONARYS_H
