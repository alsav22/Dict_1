/********************************************************************************
** Form generated from reading UI file 'dictionary.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DICTIONARY_H
#define UI_DICTIONARY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
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
    QGroupBox *groupBox;
    QCheckBox *checkBox_0;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_5;

    void setupUi(QWidget *DictionarysClass)
    {
        if (DictionarysClass->objectName().isEmpty())
            DictionarysClass->setObjectName(QString::fromUtf8("DictionarysClass"));
        DictionarysClass->resize(775, 456);
        DictionarysClass->setFocusPolicy(Qt::NoFocus);
        lineEdit = new QLineEdit(DictionarysClass);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(35, 79, 231, 36));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(11);
        lineEdit->setFont(font);
        textEdit = new QTextEdit(DictionarysClass);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(310, 80, 421, 341));
        textEdit->setFont(font);
        textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textEdit->setReadOnly(true);
        label = new QLabel(DictionarysClass);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(35, 38, 246, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(9);
        label->setFont(font1);
        label_2 = new QLabel(DictionarysClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(320, 40, 96, 19));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(10);
        label_2->setFont(font2);
        groupBox = new QGroupBox(DictionarysClass);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(35, 135, 231, 266));
        checkBox_0 = new QCheckBox(groupBox);
        checkBox_0->setObjectName(QString::fromUtf8("checkBox_0"));
        checkBox_0->setGeometry(QRect(15, 40, 186, 23));
        checkBox_0->setCursor(QCursor(Qt::PointingHandCursor));
        checkBox_0->setChecked(false);
        checkBox_0->setTristate(false);
        checkBox_2 = new QCheckBox(groupBox);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setGeometry(QRect(15, 110, 191, 23));
        checkBox_2->setChecked(false);
        checkBox_3 = new QCheckBox(groupBox);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setGeometry(QRect(15, 145, 191, 23));
        checkBox_3->setChecked(false);
        checkBox_4 = new QCheckBox(groupBox);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setGeometry(QRect(15, 180, 186, 23));
        checkBox_4->setChecked(false);
        checkBox_1 = new QCheckBox(groupBox);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setGeometry(QRect(15, 75, 191, 23));
        checkBox_1->setChecked(false);
        checkBox_5 = new QCheckBox(groupBox);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setGeometry(QRect(15, 215, 171, 23));
        checkBox_5->setChecked(false);

        retranslateUi(DictionarysClass);
        QObject::connect(lineEdit, SIGNAL(returnPressed()), DictionarysClass, SLOT(translate()));

        QMetaObject::connectSlotsByName(DictionarysClass);
    } // setupUi

    void retranslateUi(QWidget *DictionarysClass)
    {
        DictionarysClass->setWindowTitle(QApplication::translate("DictionarysClass", "Dictionarys", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("DictionarysClass", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\260\320\275\320\263\320\273\320\270\320\271\321\201\320\272\320\276\320\265 \321\201\320\273\320\276\320\262\320\276:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("DictionarysClass", "\320\237\320\265\321\200\320\265\320\262\320\276\320\264:", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DictionarysClass", "\320\241\320\273\320\276\320\262\320\260\321\200\320\270", 0, QApplication::UnicodeUTF8));
        checkBox_0->setText(QApplication::translate("DictionarysClass", "\320\236\320\261\321\211\320\265\320\271 \320\273\320\265\320\272\321\201\320\270\320\272\320\270", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("DictionarysClass", "\320\232\320\276\320\274\320\277\321\214\321\216\321\202\320\265\321\200\320\275\321\213\320\271", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("DictionarysClass", "\320\237\320\276\320\273\320\270\321\202\320\265\321\205\320\275\320\270\321\207\320\265\321\201\320\272\320\270\320\271", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("DictionarysClass", "\320\221\320\270\320\276\320\273\320\276\320\263\320\270\321\207\320\265\321\201\320\272\320\270\320\271", 0, QApplication::UnicodeUTF8));
        checkBox_1->setText(QApplication::translate("DictionarysClass", "\320\240\320\260\320\267\320\263\320\276\320\262\320\276\321\200\320\275\320\276\320\271 \320\273\320\265\320\272\321\201\320\270\320\272\320\270", 0, QApplication::UnicodeUTF8));
        checkBox_5->setText(QApplication::translate("DictionarysClass", "\320\234\320\265\320\264\320\270\321\206\320\270\320\275\321\201\320\272\320\270\320\271", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DictionarysClass: public Ui_DictionarysClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DICTIONARY_H
