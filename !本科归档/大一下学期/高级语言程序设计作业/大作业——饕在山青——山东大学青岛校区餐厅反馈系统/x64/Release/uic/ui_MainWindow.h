/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QWidget *SystemWidget;
    QLabel *background_on_login;
    QLabel *welcome_text;
    QLabel *please_login;
    QLabel *show_username;
    QLabel *show_password;
    QPushButton *login_push_button;
    QPushButton *exist_push_button;
    QLineEdit *get_username_on_login;
    QLineEdit *get_password_on_login;
    QLabel *background_on_using;
    QPushButton *admin_function_1_button;
    QPushButton *admin_function_2_button;
    QPushButton *admin_function_3_button;
    QPushButton *admin_function_4_button;
    QLabel *let_user_regist;
    QPushButton *regist_push_button;
    QPushButton *exit_user;
    QPushButton *user_function_1_button;
    QPushButton *user_function_2_button;
    QPushButton *user_function_4_button;
    QPushButton *user_function_3_button;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName("MainWindowClass");
        MainWindowClass->setEnabled(true);
        MainWindowClass->resize(960, 540);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindowClass->sizePolicy().hasHeightForWidth());
        MainWindowClass->setSizePolicy(sizePolicy);
        MainWindowClass->setMinimumSize(QSize(960, 540));
        MainWindowClass->setMaximumSize(QSize(960, 540));
        QIcon icon;
        icon.addFile(QString::fromUtf8("icon/icon.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowClass->setWindowIcon(icon);
        SystemWidget = new QWidget(MainWindowClass);
        SystemWidget->setObjectName("SystemWidget");
        background_on_login = new QLabel(SystemWidget);
        background_on_login->setObjectName("background_on_login");
        background_on_login->setEnabled(true);
        background_on_login->setGeometry(QRect(0, -20, 961, 571));
        sizePolicy.setHeightForWidth(background_on_login->sizePolicy().hasHeightForWidth());
        background_on_login->setSizePolicy(sizePolicy);
        background_on_login->setMinimumSize(QSize(961, 571));
        background_on_login->setStyleSheet(QString::fromUtf8("border: 1px solid black;"));
        background_on_login->setPixmap(QPixmap(QString::fromUtf8("background/\347\231\273\345\275\225\347\225\214\351\235\242.png")));
        background_on_login->setScaledContents(true);
        background_on_login->setWordWrap(false);
        background_on_login->setOpenExternalLinks(false);
        welcome_text = new QLabel(SystemWidget);
        welcome_text->setObjectName("welcome_text");
        welcome_text->setGeometry(QRect(350, 90, 581, 111));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(24);
        welcome_text->setFont(font);
        welcome_text->setScaledContents(false);
        welcome_text->setWordWrap(false);
        welcome_text->setOpenExternalLinks(false);
        please_login = new QLabel(SystemWidget);
        please_login->setObjectName("please_login");
        please_login->setGeometry(QRect(400, 260, 50, 15));
        please_login->setMinimumSize(QSize(50, 15));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(10);
        please_login->setFont(font1);
        show_username = new QLabel(SystemWidget);
        show_username->setObjectName("show_username");
        show_username->setGeometry(QRect(500, 255, 50, 21));
        show_username->setMinimumSize(QSize(50, 21));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font2.setPointSize(11);
        show_username->setFont(font2);
        show_password = new QLabel(SystemWidget);
        show_password->setObjectName("show_password");
        show_password->setGeometry(QRect(500, 307, 50, 15));
        show_password->setMinimumSize(QSize(50, 15));
        show_password->setFont(font2);
        login_push_button = new QPushButton(SystemWidget);
        login_push_button->setObjectName("login_push_button");
        login_push_button->setGeometry(QRect(550, 360, 80, 23));
        login_push_button->setMinimumSize(QSize(80, 23));
        login_push_button->setCursor(QCursor(Qt::PointingHandCursor));
        exist_push_button = new QPushButton(SystemWidget);
        exist_push_button->setObjectName("exist_push_button");
        exist_push_button->setGeometry(QRect(700, 360, 80, 23));
        exist_push_button->setMinimumSize(QSize(80, 23));
        exist_push_button->setCursor(QCursor(Qt::PointingHandCursor));
        get_username_on_login = new QLineEdit(SystemWidget);
        get_username_on_login->setObjectName("get_username_on_login");
        get_username_on_login->setGeometry(QRect(550, 250, 231, 31));
        get_username_on_login->setMinimumSize(QSize(231, 31));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("\345\256\213\344\275\223")});
        font3.setPointSize(12);
        get_username_on_login->setFont(font3);
        get_username_on_login->setStyleSheet(QString::fromUtf8("border: 1px solid black;"));
        get_password_on_login = new QLineEdit(SystemWidget);
        get_password_on_login->setObjectName("get_password_on_login");
        get_password_on_login->setGeometry(QRect(550, 300, 231, 31));
        get_password_on_login->setMinimumSize(QSize(231, 31));
        get_password_on_login->setFont(font3);
        get_password_on_login->setStyleSheet(QString::fromUtf8("border: 1px solid black;"));
        background_on_using = new QLabel(SystemWidget);
        background_on_using->setObjectName("background_on_using");
        background_on_using->setGeometry(QRect(0, 0, 971, 511));
        background_on_using->setPixmap(QPixmap(QString::fromUtf8("background/\344\275\277\347\224\250\350\200\205\347\225\214\351\235\242.png")));
        background_on_using->setScaledContents(true);
        admin_function_1_button = new QPushButton(SystemWidget);
        admin_function_1_button->setObjectName("admin_function_1_button");
        admin_function_1_button->setGeometry(QRect(160, 270, 221, 81));
        admin_function_1_button->setMinimumSize(QSize(221, 81));
        admin_function_1_button->setCursor(QCursor(Qt::PointingHandCursor));
        admin_function_1_button->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"    border-image: url(image/01\347\224\250\346\210\267\347\256\241\347\220\206.png);\n"
"}\n"
"QPushButton:hover{\n"
"	border-image: url(image/01\347\224\250\346\210\267\347\256\241\347\220\206\350\242\253\351\200\211\344\270\255.png);\n"
"}\n"
"QPushButton:pressed{\n"
"    border-image: url(image/01\347\224\250\346\210\267\347\256\241\347\220\206\350\242\253\351\200\211\344\270\255.png);\n"
"}  "));
        admin_function_2_button = new QPushButton(SystemWidget);
        admin_function_2_button->setObjectName("admin_function_2_button");
        admin_function_2_button->setGeometry(QRect(570, 270, 241, 81));
        admin_function_2_button->setMinimumSize(QSize(241, 81));
        admin_function_2_button->setCursor(QCursor(Qt::PointingHandCursor));
        admin_function_2_button->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"	border-image: url(image/02\350\217\234\350\211\262\347\256\241\347\220\206.png);\n"
"}\n"
"QPushButton:hover{\n"
"	border-image: url(image/02\350\217\234\350\211\262\347\256\241\347\220\206\350\242\253\351\200\211\344\270\255.png);\n"
"}\n"
"QPushButton:pressed{\n"
"    border-image: url(image/02\350\217\234\350\211\262\347\256\241\347\220\206\350\242\253\351\200\211\344\270\255.png);\n"
"}  "));
        admin_function_3_button = new QPushButton(SystemWidget);
        admin_function_3_button->setObjectName("admin_function_3_button");
        admin_function_3_button->setGeometry(QRect(150, 370, 241, 81));
        admin_function_3_button->setMinimumSize(QSize(241, 81));
        admin_function_3_button->setCursor(QCursor(Qt::PointingHandCursor));
        admin_function_3_button->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"	border-image: url(image/03\346\237\245\347\234\213\345\217\215\351\246\210.png);\n"
"}\n"
"QPushButton:hover{\n"
"	border-image: url(image/03\346\237\245\347\234\213\345\217\215\351\246\210\350\242\253\351\200\211\344\270\255.png);\n"
"}\n"
"QPushButton:pressed{\n"
"    border-image: url(image/03\346\237\245\347\234\213\345\217\215\351\246\210\350\242\253\351\200\211\344\270\255.png);\n"
"}  "));
        admin_function_4_button = new QPushButton(SystemWidget);
        admin_function_4_button->setObjectName("admin_function_4_button");
        admin_function_4_button->setGeometry(QRect(570, 360, 251, 111));
        admin_function_4_button->setMinimumSize(QSize(251, 111));
        admin_function_4_button->setCursor(QCursor(Qt::PointingHandCursor));
        admin_function_4_button->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"	border-image: url(image/04\346\237\245\347\234\213\346\227\245\345\277\227.png);\n"
"}\n"
"QPushButton:hover{\n"
"	border-image: url(image/04\346\237\245\347\234\213\346\227\245\345\277\227\350\242\253\351\200\211\344\270\255.png);\n"
"}\n"
"QPushButton:pressed{\n"
"    border-image: url(image/04\346\237\245\347\234\213\346\227\245\345\277\227\350\242\253\351\200\211\344\270\255.png);\n"
"}  "));
        let_user_regist = new QLabel(SystemWidget);
        let_user_regist->setObjectName("let_user_regist");
        let_user_regist->setGeometry(QRect(550, 440, 81, 16));
        regist_push_button = new QPushButton(SystemWidget);
        regist_push_button->setObjectName("regist_push_button");
        regist_push_button->setGeometry(QRect(620, 436, 31, 23));
        regist_push_button->setCursor(QCursor(Qt::PointingHandCursor));
        regist_push_button->setStyleSheet(QString::fromUtf8("border-style:none;\n"
"color:blue;"));
        exit_user = new QPushButton(SystemWidget);
        exit_user->setObjectName("exit_user");
        exit_user->setGeometry(QRect(859, 502, 101, 41));
        exit_user->setMinimumSize(QSize(80, 23));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font4.setPointSize(8);
        exit_user->setFont(font4);
        exit_user->setCursor(QCursor(Qt::PointingHandCursor));
        user_function_1_button = new QPushButton(SystemWidget);
        user_function_1_button->setObjectName("user_function_1_button");
        user_function_1_button->setGeometry(QRect(160, 270, 241, 81));
        user_function_1_button->setMinimumSize(QSize(241, 81));
        user_function_1_button->setCursor(QCursor(Qt::PointingHandCursor));
        user_function_1_button->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"    border-image: url(image/01\346\237\245\347\234\213\350\217\234\350\211\262.png);\n"
"}\n"
"QPushButton:hover{\n"
"	border-image: url(image/01\346\237\245\347\234\213\350\217\234\350\211\262\350\242\253\351\200\211\344\270\255.png);\n"
"}\n"
"QPushButton:pressed{\n"
"    border-image: url(image/01\346\237\245\347\234\213\350\217\234\350\211\262\350\242\253\351\200\211\344\270\255.png);\n"
"}  "));
        user_function_2_button = new QPushButton(SystemWidget);
        user_function_2_button->setObjectName("user_function_2_button");
        user_function_2_button->setGeometry(QRect(550, 270, 261, 81));
        user_function_2_button->setMinimumSize(QSize(261, 81));
        user_function_2_button->setCursor(QCursor(Qt::PointingHandCursor));
        user_function_2_button->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"	border-image: url(image/02\346\217\220\344\272\244\346\204\217\350\247\201.png);\n"
"}\n"
"QPushButton:hover{\n"
"	border-image: url(image/02\346\217\220\344\272\244\346\204\217\350\247\201\350\242\253\351\200\211\344\270\255.png);\n"
"}\n"
"QPushButton:pressed{\n"
"    border-image: url(image/02\346\217\220\344\272\244\346\204\217\350\247\201\350\242\253\351\200\211\344\270\255.png);\n"
"}  "));
        user_function_4_button = new QPushButton(SystemWidget);
        user_function_4_button->setObjectName("user_function_4_button");
        user_function_4_button->setGeometry(QRect(540, 360, 231, 91));
        user_function_4_button->setMinimumSize(QSize(231, 91));
        user_function_4_button->setCursor(QCursor(Qt::PointingHandCursor));
        user_function_4_button->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"	border-image: url(image/04\346\220\234\347\264\242\350\217\234\350\211\262.png);\n"
"}\n"
"QPushButton:hover{\n"
"	border-image: url(image/04\346\220\234\347\264\242\350\217\234\350\211\262\350\242\253\351\200\211\344\270\255.png);\n"
"}\n"
"QPushButton:pressed{\n"
"    border-image: url(image/04\346\220\234\347\264\242\350\217\234\350\211\262\350\242\253\351\200\211\344\270\255.png);\n"
"}  "));
        user_function_3_button = new QPushButton(SystemWidget);
        user_function_3_button->setObjectName("user_function_3_button");
        user_function_3_button->setGeometry(QRect(160, 360, 241, 81));
        user_function_3_button->setMinimumSize(QSize(241, 81));
        user_function_3_button->setCursor(QCursor(Qt::PointingHandCursor));
        user_function_3_button->setStyleSheet(QString::fromUtf8("QPushButton{ \n"
"	border-image: url(image/03\350\264\246\346\210\267\347\256\241\347\220\206.png);\n"
"}\n"
"QPushButton:hover{\n"
"	border-image: url(image/03\350\264\246\346\210\267\347\256\241\347\220\206\350\242\253\351\200\211\344\270\255.png);\n"
"}\n"
"QPushButton:pressed{\n"
"    border-image: url(image/03\350\264\246\346\210\267\347\256\241\347\220\206\350\242\253\351\200\211\344\270\255.png);\n"
"}  "));
        MainWindowClass->setCentralWidget(SystemWidget);
        background_on_login->raise();
        welcome_text->raise();
        please_login->raise();
        show_username->raise();
        show_password->raise();
        login_push_button->raise();
        exist_push_button->raise();
        get_username_on_login->raise();
        get_password_on_login->raise();
        let_user_regist->raise();
        regist_push_button->raise();
        background_on_using->raise();
        admin_function_4_button->raise();
        admin_function_3_button->raise();
        admin_function_1_button->raise();
        admin_function_2_button->raise();
        exit_user->raise();
        user_function_1_button->raise();
        user_function_2_button->raise();
        user_function_4_button->raise();
        user_function_3_button->raise();
        QWidget::setTabOrder(login_push_button, exist_push_button);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QCoreApplication::translate("MainWindowClass", "\351\245\225\345\234\250\345\261\261\351\235\222\342\200\224\342\200\224\345\261\261\344\270\234\345\244\247\345\255\246\351\235\222\345\262\233\346\240\241\345\214\272\351\244\220\345\216\205\345\217\215\351\246\210\347\263\273\347\273\237", nullptr));
        background_on_login->setText(QString());
        welcome_text->setText(QCoreApplication::translate("MainWindowClass", "\346\254\242\350\277\216\350\256\277\351\227\256\351\245\225\345\234\250\345\261\261\351\235\222\n"
"     \342\200\224\342\200\224\345\261\261\344\270\234\345\244\247\345\255\246\351\235\222\345\262\233\346\240\241\345\214\272\351\244\220\345\216\205\345\217\215\351\246\210\347\263\273\347\273\237", nullptr));
        please_login->setText(QCoreApplication::translate("MainWindowClass", "\350\257\267\347\231\273\345\275\225", nullptr));
        show_username->setText(QCoreApplication::translate("MainWindowClass", "\350\264\246\345\217\267", nullptr));
        show_password->setText(QCoreApplication::translate("MainWindowClass", "\345\257\206\347\240\201", nullptr));
        login_push_button->setText(QCoreApplication::translate("MainWindowClass", "\347\231\273\345\275\225", nullptr));
        exist_push_button->setText(QCoreApplication::translate("MainWindowClass", "\351\200\200\345\207\272", nullptr));
        background_on_using->setText(QString());
        admin_function_1_button->setText(QString());
        admin_function_2_button->setText(QString());
        admin_function_3_button->setText(QString());
        admin_function_4_button->setText(QString());
        let_user_regist->setText(QCoreApplication::translate("MainWindowClass", "\350\277\230\346\262\241\346\234\211\350\264\246\345\217\267\357\274\237", nullptr));
        regist_push_button->setText(QCoreApplication::translate("MainWindowClass", "\346\263\250\345\206\214", nullptr));
        exit_user->setText(QCoreApplication::translate("MainWindowClass", "\351\200\200\345\207\272\350\264\246\345\217\267", nullptr));
        user_function_1_button->setText(QString());
        user_function_2_button->setText(QString());
        user_function_4_button->setText(QString());
        user_function_3_button->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
