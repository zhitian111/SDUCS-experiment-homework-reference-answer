/********************************************************************************
** Form generated from reading UI file 'UserRegistWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERREGISTWINDOW_H
#define UI_USERREGISTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Regist
{
public:
    QWidget *centralwidget;
    QPushButton *cancel_push_button;
    QLabel *label_5;
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *username;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *name;
    QLineEdit *password1;
    QLineEdit *password2;
    QLabel *label_4;
    QPushButton *regist_push_button;

    void setupUi(QMainWindow *Regist)
    {
        if (Regist->objectName().isEmpty())
            Regist->setObjectName("Regist");
        Regist->resize(501, 253);
        Regist->setMinimumSize(QSize(501, 253));
        Regist->setMaximumSize(QSize(501, 253));
        centralwidget = new QWidget(Regist);
        centralwidget->setObjectName("centralwidget");
        cancel_push_button = new QPushButton(centralwidget);
        cancel_push_button->setObjectName("cancel_push_button");
        cancel_push_button->setGeometry(QRect(330, 200, 80, 23));
        cancel_push_button->setCursor(QCursor(Qt::PointingHandCursor));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(230, 10, 50, 15));
        QFont font;
        font.setFamilies({QString::fromUtf8("\351\273\221\344\275\223")});
        font.setPointSize(12);
        label_5->setFont(font);
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(80, 50, 331, 120));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setFieldGrowthPolicy(QFormLayout::FieldGrowthPolicy::ExpandingFieldsGrow);
        formLayout->setRowWrapPolicy(QFormLayout::RowWrapPolicy::DontWrapRows);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        username = new QLineEdit(formLayoutWidget);
        username->setObjectName("username");
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(12);
        username->setFont(font1);
        username->setStyleSheet(QString::fromUtf8("border:1px solid black;"));

        formLayout->setWidget(0, QFormLayout::FieldRole, username);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        name = new QLineEdit(formLayoutWidget);
        name->setObjectName("name");
        name->setFont(font1);
        name->setStyleSheet(QString::fromUtf8("border:1px solid black;"));

        formLayout->setWidget(1, QFormLayout::FieldRole, name);

        password1 = new QLineEdit(formLayoutWidget);
        password1->setObjectName("password1");
        password1->setFont(font1);
        password1->setCursor(QCursor(Qt::IBeamCursor));
        password1->setStyleSheet(QString::fromUtf8("border:1px solid black;"));

        formLayout->setWidget(2, QFormLayout::FieldRole, password1);

        password2 = new QLineEdit(formLayoutWidget);
        password2->setObjectName("password2");
        password2->setFont(font1);
        password2->setStyleSheet(QString::fromUtf8("border:1px solid black;"));

        formLayout->setWidget(3, QFormLayout::FieldRole, password2);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        regist_push_button = new QPushButton(centralwidget);
        regist_push_button->setObjectName("regist_push_button");
        regist_push_button->setGeometry(QRect(80, 200, 80, 23));
        regist_push_button->setCursor(QCursor(Qt::PointingHandCursor));
        Regist->setCentralWidget(centralwidget);

        retranslateUi(Regist);

        QMetaObject::connectSlotsByName(Regist);
    } // setupUi

    void retranslateUi(QMainWindow *Regist)
    {
        Regist->setWindowTitle(QCoreApplication::translate("Regist", "MainWindow", nullptr));
        cancel_push_button->setText(QCoreApplication::translate("Regist", "\345\217\226\346\266\210", nullptr));
        label_5->setText(QCoreApplication::translate("Regist", "\346\263\250\345\206\214", nullptr));
        label->setText(QCoreApplication::translate("Regist", "\350\264\246\345\217\267", nullptr));
        label_2->setText(QCoreApplication::translate("Regist", "\345\247\223\345\220\215", nullptr));
        label_3->setText(QCoreApplication::translate("Regist", "\345\257\206\347\240\201", nullptr));
        label_4->setText(QCoreApplication::translate("Regist", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        regist_push_button->setText(QCoreApplication::translate("Regist", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Regist: public Ui_Regist {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERREGISTWINDOW_H
