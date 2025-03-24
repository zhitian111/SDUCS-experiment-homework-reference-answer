/********************************************************************************
** Form generated from reading UI file 'comment_window.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMMENT_WINDOW_H
#define UI_COMMENT_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_comment_window
{
public:
    QAction *action;
    QAction *action_2;
    QWidget *centralwidget;
    QLabel *label;
    QPushButton *pushButton;
    QLineEdit *seach_what;
    QTextBrowser *show_text;
    QLabel *label_2;
    QToolBar *toolBar;

    void setupUi(QMainWindow *comment_window)
    {
        if (comment_window->objectName().isEmpty())
            comment_window->setObjectName("comment_window");
        comment_window->resize(589, 709);
        comment_window->setMinimumSize(QSize(589, 709));
        comment_window->setMaximumSize(QSize(589, 709));
        action = new QAction(comment_window);
        action->setObjectName("action");
        action->setMenuRole(QAction::MenuRole::NoRole);
        action_2 = new QAction(comment_window);
        action_2->setObjectName("action_2");
        action_2->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(comment_window);
        centralwidget->setObjectName("centralwidget");
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 10, 141, 51));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(14);
        font.setBold(true);
        label->setFont(font);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(290, 80, 80, 23));
        seach_what = new QLineEdit(centralwidget);
        seach_what->setObjectName("seach_what");
        seach_what->setGeometry(QRect(30, 80, 241, 22));
        seach_what->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        show_text = new QTextBrowser(centralwidget);
        show_text->setObjectName("show_text");
        show_text->setGeometry(QRect(30, 120, 521, 521));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(10);
        show_text->setFont(font1);
        show_text->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        show_text->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(30, 10, 141, 51));
        label_2->setFont(font);
        comment_window->setCentralWidget(centralwidget);
        toolBar = new QToolBar(comment_window);
        toolBar->setObjectName("toolBar");
        comment_window->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        toolBar->addAction(action);
        toolBar->addAction(action_2);

        retranslateUi(comment_window);

        QMetaObject::connectSlotsByName(comment_window);
    } // setupUi

    void retranslateUi(QMainWindow *comment_window)
    {
        comment_window->setWindowTitle(QCoreApplication::translate("comment_window", "MainWindow", nullptr));
        action->setText(QCoreApplication::translate("comment_window", "\346\220\234\347\264\242\350\217\234\345\223\201\345\217\215\351\246\210", nullptr));
        action_2->setText(QCoreApplication::translate("comment_window", "\346\237\245\347\234\213\346\211\200\346\234\211\345\217\215\351\246\210", nullptr));
        label->setText(QCoreApplication::translate("comment_window", "\346\220\234\347\264\242\350\217\234\345\223\201\345\217\215\351\246\210", nullptr));
        pushButton->setText(QCoreApplication::translate("comment_window", "\346\220\234\347\264\242", nullptr));
        label_2->setText(QCoreApplication::translate("comment_window", "\346\237\245\347\234\213\346\211\200\346\234\211\345\217\215\351\246\210", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("comment_window", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class comment_window: public Ui_comment_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMMENT_WINDOW_H
