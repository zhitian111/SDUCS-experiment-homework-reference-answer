/********************************************************************************
** Form generated from reading UI file 'log_window.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOG_WINDOW_H
#define UI_LOG_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ui_log_window
{
public:
    QWidget *centralwidget;
    QTextBrowser *textBrowser;
    QCheckBox *checkBox;
    QPushButton *last;
    QPushButton *next;

    void setupUi(QMainWindow *ui_log_window)
    {
        if (ui_log_window->objectName().isEmpty())
            ui_log_window->setObjectName("ui_log_window");
        ui_log_window->resize(875, 604);
        ui_log_window->setMinimumSize(QSize(875, 604));
        ui_log_window->setMaximumSize(QSize(875, 604));
        centralwidget = new QWidget(ui_log_window);
        centralwidget->setObjectName("centralwidget");
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(55, 33, 761, 481));
        textBrowser->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        checkBox = new QCheckBox(centralwidget);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(55, 533, 91, 21));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(11);
        checkBox->setFont(font);
        last = new QPushButton(centralwidget);
        last->setObjectName("last");
        last->setGeometry(QRect(485, 533, 80, 23));
        last->setCursor(QCursor(Qt::PointingHandCursor));
        next = new QPushButton(centralwidget);
        next->setObjectName("next");
        next->setGeometry(QRect(735, 533, 80, 23));
        next->setCursor(QCursor(Qt::PointingHandCursor));
        ui_log_window->setCentralWidget(centralwidget);

        retranslateUi(ui_log_window);

        QMetaObject::connectSlotsByName(ui_log_window);
    } // setupUi

    void retranslateUi(QMainWindow *ui_log_window)
    {
        ui_log_window->setWindowTitle(QCoreApplication::translate("ui_log_window", "MainWindow", nullptr));
        checkBox->setText(QCoreApplication::translate("ui_log_window", "\346\230\276\347\244\272\345\205\250\351\203\250", nullptr));
        last->setText(QCoreApplication::translate("ui_log_window", "\344\270\212\344\270\200\346\254\241\350\277\220\350\241\214", nullptr));
        next->setText(QCoreApplication::translate("ui_log_window", "\344\270\213\344\270\200\346\254\241\350\277\220\350\241\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ui_log_window: public Ui_ui_log_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOG_WINDOW_H
