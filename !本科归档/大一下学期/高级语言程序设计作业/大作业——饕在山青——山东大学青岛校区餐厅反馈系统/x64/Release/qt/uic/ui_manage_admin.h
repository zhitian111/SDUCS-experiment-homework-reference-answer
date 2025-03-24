/********************************************************************************
** Form generated from reading UI file 'manage_admin.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGE_ADMIN_H
#define UI_MANAGE_ADMIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_manage_admin_window
{
public:
    QWidget *centralwidget;
    QLineEdit *reset_password_1;
    QLineEdit *reset_password_2;
    QLineEdit *reset_password_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *reset_password;
    QLineEdit *add_admin_2;
    QLineEdit *add_admin_1;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *add_admin;
    QListView *admin_list;
    QLabel *label_6;
    QLineEdit *delet_admin_1;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *delete_admin;
    QLineEdit *delet_admin_2;
    QPushButton *delete_user_button;
    QLineEdit *delet_user;
    QLabel *label_10;
    QListView *admin_list_2;
    QLabel *label_9;

    void setupUi(QMainWindow *manage_admin_window)
    {
        if (manage_admin_window->objectName().isEmpty())
            manage_admin_window->setObjectName("manage_admin_window");
        manage_admin_window->resize(597, 699);
        manage_admin_window->setMinimumSize(QSize(320, 699));
        manage_admin_window->setMaximumSize(QSize(597, 699));
        centralwidget = new QWidget(manage_admin_window);
        centralwidget->setObjectName("centralwidget");
        reset_password_1 = new QLineEdit(centralwidget);
        reset_password_1->setObjectName("reset_password_1");
        reset_password_1->setGeometry(QRect(70, 20, 211, 22));
        reset_password_1->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        reset_password_2 = new QLineEdit(centralwidget);
        reset_password_2->setObjectName("reset_password_2");
        reset_password_2->setGeometry(QRect(70, 50, 211, 22));
        reset_password_2->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        reset_password_3 = new QLineEdit(centralwidget);
        reset_password_3->setObjectName("reset_password_3");
        reset_password_3->setGeometry(QRect(70, 82, 211, 22));
        reset_password_3->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(33, 22, 50, 15));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(33, 54, 50, 15));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 84, 50, 15));
        reset_password = new QPushButton(centralwidget);
        reset_password->setObjectName("reset_password");
        reset_password->setGeometry(QRect(200, 120, 80, 23));
        reset_password->setCursor(QCursor(Qt::PointingHandCursor));
        add_admin_2 = new QLineEdit(centralwidget);
        add_admin_2->setObjectName("add_admin_2");
        add_admin_2->setGeometry(QRect(70, 180, 211, 22));
        add_admin_2->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        add_admin_1 = new QLineEdit(centralwidget);
        add_admin_1->setObjectName("add_admin_1");
        add_admin_1->setGeometry(QRect(70, 150, 211, 22));
        add_admin_1->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(32, 153, 50, 15));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(43, 183, 50, 15));
        add_admin = new QPushButton(centralwidget);
        add_admin->setObjectName("add_admin");
        add_admin->setGeometry(QRect(200, 215, 80, 23));
        add_admin->setCursor(QCursor(Qt::PointingHandCursor));
        admin_list = new QListView(centralwidget);
        admin_list->setObjectName("admin_list");
        admin_list->setGeometry(QRect(70, 370, 211, 301));
        admin_list->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(70, 350, 101, 16));
        delet_admin_1 = new QLineEdit(centralwidget);
        delet_admin_1->setObjectName("delet_admin_1");
        delet_admin_1->setGeometry(QRect(70, 260, 211, 22));
        delet_admin_1->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(43, 293, 50, 15));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(32, 263, 50, 15));
        delete_admin = new QPushButton(centralwidget);
        delete_admin->setObjectName("delete_admin");
        delete_admin->setGeometry(QRect(200, 325, 80, 23));
        delete_admin->setCursor(QCursor(Qt::PointingHandCursor));
        delet_admin_2 = new QLineEdit(centralwidget);
        delet_admin_2->setObjectName("delet_admin_2");
        delet_admin_2->setGeometry(QRect(70, 290, 211, 22));
        delet_admin_2->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        delete_user_button = new QPushButton(centralwidget);
        delete_user_button->setObjectName("delete_user_button");
        delete_user_button->setGeometry(QRect(480, 50, 80, 23));
        delete_user_button->setCursor(QCursor(Qt::PointingHandCursor));
        delet_user = new QLineEdit(centralwidget);
        delet_user->setObjectName("delet_user");
        delet_user->setGeometry(QRect(350, 20, 211, 22));
        delet_user->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        label_10 = new QLabel(centralwidget);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(312, 23, 50, 15));
        admin_list_2 = new QListView(centralwidget);
        admin_list_2->setObjectName("admin_list_2");
        admin_list_2->setGeometry(QRect(350, 90, 211, 581));
        admin_list_2->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(350, 70, 101, 16));
        manage_admin_window->setCentralWidget(centralwidget);
        QWidget::setTabOrder(reset_password_1, reset_password_2);
        QWidget::setTabOrder(reset_password_2, reset_password_3);
        QWidget::setTabOrder(reset_password_3, add_admin_1);
        QWidget::setTabOrder(add_admin_1, add_admin_2);
        QWidget::setTabOrder(add_admin_2, delet_admin_1);
        QWidget::setTabOrder(delet_admin_1, delet_admin_2);
        QWidget::setTabOrder(delet_admin_2, delet_user);
        QWidget::setTabOrder(delet_user, reset_password);
        QWidget::setTabOrder(reset_password, delete_admin);
        QWidget::setTabOrder(delete_admin, add_admin);
        QWidget::setTabOrder(add_admin, delete_user_button);
        QWidget::setTabOrder(delete_user_button, admin_list);
        QWidget::setTabOrder(admin_list, admin_list_2);

        retranslateUi(manage_admin_window);

        QMetaObject::connectSlotsByName(manage_admin_window);
    } // setupUi

    void retranslateUi(QMainWindow *manage_admin_window)
    {
        manage_admin_window->setWindowTitle(QCoreApplication::translate("manage_admin_window", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("manage_admin_window", "\345\216\237\345\257\206\347\240\201", nullptr));
        label_2->setText(QCoreApplication::translate("manage_admin_window", "\346\226\260\345\257\206\347\240\201", nullptr));
        label_3->setText(QCoreApplication::translate("manage_admin_window", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        reset_password->setText(QCoreApplication::translate("manage_admin_window", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        label_4->setText(QCoreApplication::translate("manage_admin_window", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_5->setText(QCoreApplication::translate("manage_admin_window", "\345\257\206\347\240\201", nullptr));
        add_admin->setText(QCoreApplication::translate("manage_admin_window", "\346\226\260\345\242\236\347\256\241\347\220\206\345\221\230", nullptr));
        label_6->setText(QCoreApplication::translate("manage_admin_window", "\345\275\223\345\211\215\347\256\241\347\220\206\345\221\230\345\210\227\350\241\250", nullptr));
        label_7->setText(QCoreApplication::translate("manage_admin_window", "\345\257\206\347\240\201", nullptr));
        label_8->setText(QCoreApplication::translate("manage_admin_window", "\347\224\250\346\210\267\345\220\215", nullptr));
        delete_admin->setText(QCoreApplication::translate("manage_admin_window", "\345\210\240\351\231\244\347\256\241\347\220\206\345\221\230", nullptr));
        delete_user_button->setText(QCoreApplication::translate("manage_admin_window", "\345\210\240\351\231\244\347\224\250\346\210\267", nullptr));
        label_10->setText(QCoreApplication::translate("manage_admin_window", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_9->setText(QCoreApplication::translate("manage_admin_window", "\345\275\223\345\211\215\347\224\250\346\210\267\345\210\227\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class manage_admin_window: public Ui_manage_admin_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGE_ADMIN_H
