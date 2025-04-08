/********************************************************************************
** Form generated from reading UI file 'manage_dish_window.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANAGE_DISH_WINDOW_H
#define UI_MANAGE_DISH_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_manage_dish_window
{
public:
    QAction *app_dish;
    QAction *delete_dish;
    QWidget *centralwidget;
    QTableWidget *dish_table;
    QLineEdit *seach_what;
    QPushButton *search_button;
    QToolBar *toolBar;

    void setupUi(QMainWindow *manage_dish_window)
    {
        if (manage_dish_window->objectName().isEmpty())
            manage_dish_window->setObjectName("manage_dish_window");
        manage_dish_window->resize(988, 600);
        manage_dish_window->setMinimumSize(QSize(988, 600));
        manage_dish_window->setMaximumSize(QSize(988, 600));
        app_dish = new QAction(manage_dish_window);
        app_dish->setObjectName("app_dish");
        app_dish->setMenuRole(QAction::MenuRole::NoRole);
        delete_dish = new QAction(manage_dish_window);
        delete_dish->setObjectName("delete_dish");
        delete_dish->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(manage_dish_window);
        centralwidget->setObjectName("centralwidget");
        dish_table = new QTableWidget(centralwidget);
        if (dish_table->columnCount() < 9)
            dish_table->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        dish_table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        dish_table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        dish_table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        dish_table->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        dish_table->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        dish_table->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        dish_table->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        dish_table->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        dish_table->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        dish_table->setObjectName("dish_table");
        dish_table->setGeometry(QRect(30, 80, 921, 451));
        dish_table->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        seach_what = new QLineEdit(centralwidget);
        seach_what->setObjectName("seach_what");
        seach_what->setGeometry(QRect(30, 30, 221, 22));
        seach_what->setStyleSheet(QString::fromUtf8("border:1px solid black"));
        search_button = new QPushButton(centralwidget);
        search_button->setObjectName("search_button");
        search_button->setGeometry(QRect(270, 30, 80, 23));
        manage_dish_window->setCentralWidget(centralwidget);
        toolBar = new QToolBar(manage_dish_window);
        toolBar->setObjectName("toolBar");
        manage_dish_window->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        toolBar->addAction(app_dish);
        toolBar->addAction(delete_dish);

        retranslateUi(manage_dish_window);

        QMetaObject::connectSlotsByName(manage_dish_window);
    } // setupUi

    void retranslateUi(QMainWindow *manage_dish_window)
    {
        manage_dish_window->setWindowTitle(QCoreApplication::translate("manage_dish_window", "MainWindow", nullptr));
        app_dish->setText(QCoreApplication::translate("manage_dish_window", "\346\267\273\345\212\240", nullptr));
        delete_dish->setText(QCoreApplication::translate("manage_dish_window", "\345\210\240\351\231\244", nullptr));
        QTableWidgetItem *___qtablewidgetitem = dish_table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("manage_dish_window", "\350\217\234\345\223\201\347\261\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = dish_table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("manage_dish_window", "\350\217\234\345\223\201\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = dish_table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("manage_dish_window", "\351\243\237\346\235\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = dish_table->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("manage_dish_window", "\351\244\220\345\216\205", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = dish_table->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("manage_dish_window", "\346\245\274\345\261\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = dish_table->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("manage_dish_window", "\347\252\227\345\217\243", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = dish_table->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("manage_dish_window", "\344\273\267\346\240\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = dish_table->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("manage_dish_window", "\351\242\235\345\244\226\345\261\236\346\200\2471", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = dish_table->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("manage_dish_window", "\351\242\235\345\244\226\345\261\236\346\200\2472", nullptr));
        search_button->setText(QCoreApplication::translate("manage_dish_window", "\346\220\234\347\264\242", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("manage_dish_window", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class manage_dish_window: public Ui_manage_dish_window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANAGE_DISH_WINDOW_H
