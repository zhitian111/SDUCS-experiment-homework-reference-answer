/********************************************************************************
** Form generated from reading UI file 'UserChangeWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERCHANGEWINDOW_H
#define UI_USERCHANGEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserChangeWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *change_password_1;
    QLineEdit *change_password_2;
    QLineEdit *change_password_3;
    QPushButton *change_password_push_button;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_3;
    QLineEdit *change_name_1;
    QLineEdit *change_name_2;
    QLineEdit *change_name_3;
    QPushButton *change_name_push_button;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *delet_user_push_button;
    QLabel *label_8;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *delet_user_1;
    QLineEdit *delet_user_2;
    QLineEdit *delet_user_3;
    QLabel *label_9;

    void setupUi(QMainWindow *UserChangeWindow)
    {
        if (UserChangeWindow->objectName().isEmpty())
            UserChangeWindow->setObjectName("UserChangeWindow");
        UserChangeWindow->resize(319, 487);
        UserChangeWindow->setMinimumSize(QSize(319, 487));
        UserChangeWindow->setMaximumSize(QSize(319, 487));
        centralwidget = new QWidget(UserChangeWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setEnabled(true);
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(80, 20, 201, 101));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        change_password_1 = new QLineEdit(verticalLayoutWidget);
        change_password_1->setObjectName("change_password_1");
        change_password_1->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        verticalLayout->addWidget(change_password_1);

        change_password_2 = new QLineEdit(verticalLayoutWidget);
        change_password_2->setObjectName("change_password_2");
        change_password_2->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        verticalLayout->addWidget(change_password_2);

        change_password_3 = new QLineEdit(verticalLayoutWidget);
        change_password_3->setObjectName("change_password_3");
        change_password_3->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        verticalLayout->addWidget(change_password_3);

        change_password_push_button = new QPushButton(centralwidget);
        change_password_push_button->setObjectName("change_password_push_button");
        change_password_push_button->setGeometry(QRect(80, 140, 80, 23));
        change_password_push_button->setCursor(QCursor(Qt::PointingHandCursor));
        change_password_push_button->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
        change_password_push_button->setCheckable(false);
        change_password_push_button->setAutoDefault(true);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 30, 50, 15));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 60, 50, 15));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(21, 94, 50, 15));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(21, 244, 50, 15));
        verticalLayoutWidget_2 = new QWidget(centralwidget);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(80, 170, 201, 101));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        change_name_1 = new QLineEdit(verticalLayoutWidget_2);
        change_name_1->setObjectName("change_name_1");
        change_name_1->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        verticalLayout_3->addWidget(change_name_1);

        change_name_2 = new QLineEdit(verticalLayoutWidget_2);
        change_name_2->setObjectName("change_name_2");
        change_name_2->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        verticalLayout_3->addWidget(change_name_2);

        change_name_3 = new QLineEdit(verticalLayoutWidget_2);
        change_name_3->setObjectName("change_name_3");
        change_name_3->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        verticalLayout_3->addWidget(change_name_3);

        change_name_push_button = new QPushButton(centralwidget);
        change_name_push_button->setObjectName("change_name_push_button");
        change_name_push_button->setGeometry(QRect(80, 290, 80, 23));
        change_name_push_button->setCursor(QCursor(Qt::PointingHandCursor));
        change_name_push_button->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(20, 180, 50, 15));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(20, 210, 50, 15));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(29, 336, 50, 15));
        delet_user_push_button = new QPushButton(centralwidget);
        delet_user_push_button->setObjectName("delet_user_push_button");
        delet_user_push_button->setGeometry(QRect(79, 446, 80, 23));
        delet_user_push_button->setCursor(QCursor(Qt::PointingHandCursor));
        delet_user_push_button->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(29, 366, 50, 15));
        verticalLayoutWidget_3 = new QWidget(centralwidget);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(79, 326, 201, 101));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        delet_user_1 = new QLineEdit(verticalLayoutWidget_3);
        delet_user_1->setObjectName("delet_user_1");
        delet_user_1->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        verticalLayout_4->addWidget(delet_user_1);

        delet_user_2 = new QLineEdit(verticalLayoutWidget_3);
        delet_user_2->setObjectName("delet_user_2");
        delet_user_2->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        verticalLayout_4->addWidget(delet_user_2);

        delet_user_3 = new QLineEdit(verticalLayoutWidget_3);
        delet_user_3->setObjectName("delet_user_3");
        delet_user_3->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        verticalLayout_4->addWidget(delet_user_3);

        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(30, 400, 50, 15));
        UserChangeWindow->setCentralWidget(centralwidget);

        retranslateUi(UserChangeWindow);

        QMetaObject::connectSlotsByName(UserChangeWindow);
    } // setupUi

    void retranslateUi(QMainWindow *UserChangeWindow)
    {
        UserChangeWindow->setWindowTitle(QCoreApplication::translate("UserChangeWindow", "MainWindow", nullptr));
        change_password_1->setText(QString());
        change_password_2->setText(QString());
        change_password_3->setText(QString());
        change_password_push_button->setText(QCoreApplication::translate("UserChangeWindow", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        label->setText(QCoreApplication::translate("UserChangeWindow", "\345\216\237\345\257\206\347\240\201", nullptr));
        label_2->setText(QCoreApplication::translate("UserChangeWindow", "\346\226\260\345\257\206\347\240\201", nullptr));
        label_3->setText(QCoreApplication::translate("UserChangeWindow", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        label_4->setText(QCoreApplication::translate("UserChangeWindow", "\347\241\256\350\256\244\345\247\223\345\220\215", nullptr));
        change_name_1->setText(QString());
        change_name_2->setText(QString());
        change_name_3->setText(QString());
        change_name_push_button->setText(QCoreApplication::translate("UserChangeWindow", "\344\277\256\346\224\271\345\247\223\345\220\215", nullptr));
        label_5->setText(QCoreApplication::translate("UserChangeWindow", "\345\216\237\345\247\223\345\220\215", nullptr));
        label_6->setText(QCoreApplication::translate("UserChangeWindow", "\346\226\260\345\247\223\345\220\215", nullptr));
        label_7->setText(QCoreApplication::translate("UserChangeWindow", "\350\264\246\345\217\267", nullptr));
        delet_user_push_button->setText(QCoreApplication::translate("UserChangeWindow", "\346\263\250\351\224\200\350\264\246\345\217\267", nullptr));
        label_8->setText(QCoreApplication::translate("UserChangeWindow", "\345\257\206\347\240\201", nullptr));
        delet_user_1->setText(QString());
        delet_user_2->setText(QString());
        delet_user_3->setText(QString());
        label_9->setText(QCoreApplication::translate("UserChangeWindow", "\345\247\223\345\220\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserChangeWindow: public Ui_UserChangeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERCHANGEWINDOW_H
