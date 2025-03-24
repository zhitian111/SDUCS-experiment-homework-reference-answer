/********************************************************************************
** Form generated from reading UI file 'SubmitWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUBMITWINDOW_H
#define UI_SUBMITWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SubmintWindow
{
public:
    QWidget *centralwidget;
    QPushButton *submit_push_button;
    QPushButton *cancel_push_button;
    QLineEdit *dish_name;
    QTextEdit *main_text;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QMainWindow *SubmintWindow)
    {
        if (SubmintWindow->objectName().isEmpty())
            SubmintWindow->setObjectName("SubmintWindow");
        SubmintWindow->resize(494, 442);
        SubmintWindow->setMinimumSize(QSize(494, 442));
        SubmintWindow->setMaximumSize(QSize(494, 442));
        centralwidget = new QWidget(SubmintWindow);
        centralwidget->setObjectName("centralwidget");
        submit_push_button = new QPushButton(centralwidget);
        submit_push_button->setObjectName("submit_push_button");
        submit_push_button->setGeometry(QRect(50, 370, 80, 23));
        cancel_push_button = new QPushButton(centralwidget);
        cancel_push_button->setObjectName("cancel_push_button");
        cancel_push_button->setGeometry(QRect(360, 370, 80, 23));
        dish_name = new QLineEdit(centralwidget);
        dish_name->setObjectName("dish_name");
        dish_name->setGeometry(QRect(50, 40, 151, 22));
        QFont font;
        font.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        font.setPointSize(12);
        dish_name->setFont(font);
        dish_name->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        main_text = new QTextEdit(centralwidget);
        main_text->setObjectName("main_text");
        main_text->setGeometry(QRect(50, 100, 391, 251));
        main_text->setFont(font);
        main_text->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 20, 50, 15));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(10);
        font1.setBold(true);
        label->setFont(font1);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(50, 73, 50, 15));
        label_2->setFont(font1);
        SubmintWindow->setCentralWidget(centralwidget);

        retranslateUi(SubmintWindow);

        QMetaObject::connectSlotsByName(SubmintWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SubmintWindow)
    {
        SubmintWindow->setWindowTitle(QCoreApplication::translate("SubmintWindow", "MainWindow", nullptr));
        submit_push_button->setText(QCoreApplication::translate("SubmintWindow", "\346\217\220\344\272\244", nullptr));
        cancel_push_button->setText(QCoreApplication::translate("SubmintWindow", "\345\217\226\346\266\210", nullptr));
        label->setText(QCoreApplication::translate("SubmintWindow", "\350\217\234\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("SubmintWindow", "\345\217\215\351\246\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SubmintWindow: public Ui_SubmintWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUBMITWINDOW_H
