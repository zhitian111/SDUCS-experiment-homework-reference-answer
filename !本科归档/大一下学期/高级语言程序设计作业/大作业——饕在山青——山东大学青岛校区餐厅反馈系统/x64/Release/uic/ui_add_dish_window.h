/********************************************************************************
** Form generated from reading UI file 'add_dish_window.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_DISH_WINDOW_H
#define UI_ADD_DISH_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_add_window
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_9;
    QLineEdit *lineEdit_6;
    QLabel *label_8;
    QLabel *label_7;
    QLabel *label_2;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_9;
    QLineEdit *lineEdit_5;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QMainWindow *add_window)
    {
        if (add_window->objectName().isEmpty())
            add_window->setObjectName("add_window");
        add_window->resize(800, 156);
        add_window->setMinimumSize(QSize(800, 156));
        add_window->setMaximumSize(QSize(800, 156));
        centralwidget = new QWidget(add_window);
        centralwidget->setObjectName("centralwidget");
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(30, 20, 751, 61));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit_9 = new QLineEdit(gridLayoutWidget);
        lineEdit_9->setObjectName("lineEdit_9");
        lineEdit_9->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        gridLayout->addWidget(lineEdit_9, 1, 8, 1, 1);

        lineEdit_6 = new QLineEdit(gridLayoutWidget);
        lineEdit_6->setObjectName("lineEdit_6");
        lineEdit_6->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        gridLayout->addWidget(lineEdit_6, 1, 5, 1, 1);

        label_8 = new QLabel(gridLayoutWidget);
        label_8->setObjectName("label_8");

        gridLayout->addWidget(label_8, 0, 7, 1, 1);

        label_7 = new QLabel(gridLayoutWidget);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 0, 6, 1, 1);

        label_2 = new QLabel(gridLayoutWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 1, 1, 1);

        lineEdit_7 = new QLineEdit(gridLayoutWidget);
        lineEdit_7->setObjectName("lineEdit_7");
        lineEdit_7->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        gridLayout->addWidget(lineEdit_7, 1, 6, 1, 1);

        lineEdit_8 = new QLineEdit(gridLayoutWidget);
        lineEdit_8->setObjectName("lineEdit_8");
        lineEdit_8->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        gridLayout->addWidget(lineEdit_8, 1, 7, 1, 1);

        lineEdit_2 = new QLineEdit(gridLayoutWidget);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        lineEdit_4 = new QLineEdit(gridLayoutWidget);
        lineEdit_4->setObjectName("lineEdit_4");
        lineEdit_4->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        gridLayout->addWidget(lineEdit_4, 1, 3, 1, 1);

        label_5 = new QLabel(gridLayoutWidget);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 0, 4, 1, 1);

        label_6 = new QLabel(gridLayoutWidget);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 0, 5, 1, 1);

        label_9 = new QLabel(gridLayoutWidget);
        label_9->setObjectName("label_9");

        gridLayout->addWidget(label_9, 0, 8, 1, 1);

        lineEdit_5 = new QLineEdit(gridLayoutWidget);
        lineEdit_5->setObjectName("lineEdit_5");
        lineEdit_5->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        gridLayout->addWidget(lineEdit_5, 1, 4, 1, 1);

        label_4 = new QLabel(gridLayoutWidget);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 0, 3, 1, 1);

        lineEdit_3 = new QLineEdit(gridLayoutWidget);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        gridLayout->addWidget(lineEdit_3, 1, 2, 1, 1);

        label_3 = new QLabel(gridLayoutWidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        label = new QLabel(gridLayoutWidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setStyleSheet(QString::fromUtf8("border:1px solid black"));

        gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(30, 100, 80, 23));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(700, 100, 80, 23));
        pushButton_2->setCursor(QCursor(Qt::PointingHandCursor));
        add_window->setCentralWidget(centralwidget);
        QWidget::setTabOrder(lineEdit, lineEdit_2);
        QWidget::setTabOrder(lineEdit_2, lineEdit_3);
        QWidget::setTabOrder(lineEdit_3, lineEdit_4);
        QWidget::setTabOrder(lineEdit_4, lineEdit_5);
        QWidget::setTabOrder(lineEdit_5, lineEdit_6);
        QWidget::setTabOrder(lineEdit_6, lineEdit_7);
        QWidget::setTabOrder(lineEdit_7, lineEdit_8);
        QWidget::setTabOrder(lineEdit_8, lineEdit_9);
        QWidget::setTabOrder(lineEdit_9, pushButton);
        QWidget::setTabOrder(pushButton, pushButton_2);

        retranslateUi(add_window);

        QMetaObject::connectSlotsByName(add_window);
    } // setupUi

    void retranslateUi(QMainWindow *add_window)
    {
        add_window->setWindowTitle(QCoreApplication::translate("add_window", "MainWindow", nullptr));
        label_8->setText(QCoreApplication::translate("add_window", "\351\242\235\345\244\226\345\261\236\346\200\2471", nullptr));
        label_7->setText(QCoreApplication::translate("add_window", "\344\273\267\346\240\274", nullptr));
        label_2->setText(QCoreApplication::translate("add_window", "\350\217\234\345\223\201\345\220\215", nullptr));
        label_5->setText(QCoreApplication::translate("add_window", "\346\245\274\345\261\202", nullptr));
        label_6->setText(QCoreApplication::translate("add_window", "\347\252\227\345\217\243", nullptr));
        label_9->setText(QCoreApplication::translate("add_window", "\351\242\235\345\244\226\345\261\236\346\200\2472", nullptr));
        label_4->setText(QCoreApplication::translate("add_window", "\351\244\220\345\216\205", nullptr));
        label_3->setText(QCoreApplication::translate("add_window", "\351\243\237\346\235\220", nullptr));
        label->setText(QCoreApplication::translate("add_window", "\350\217\234\345\223\201\347\261\273", nullptr));
        pushButton->setText(QCoreApplication::translate("add_window", "\346\217\220\344\272\244", nullptr));
        pushButton_2->setText(QCoreApplication::translate("add_window", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class add_window: public Ui_add_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_DISH_WINDOW_H
