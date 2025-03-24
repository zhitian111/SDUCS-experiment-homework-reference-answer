/********************************************************************************
** Form generated from reading UI file 'show_table.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOW_TABLE_H
#define UI_SHOW_TABLE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_show_table
{
public:
    QLineEdit *search_what;
    QTableWidget *fired_dish_table;
    QTableWidget *flour_dish_table;
    QTableWidget *halal_dish_table;
    QPushButton *search_push_button;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QCheckBox *checkBox;

    void setupUi(QWidget *show_table)
    {
        if (show_table->objectName().isEmpty())
            show_table->setObjectName("show_table");
        show_table->resize(969, 773);
        show_table->setMinimumSize(QSize(969, 773));
        show_table->setMaximumSize(QSize(969, 773));
        search_what = new QLineEdit(show_table);
        search_what->setObjectName("search_what");
        search_what->setGeometry(QRect(60, 30, 291, 22));
        search_what->setStyleSheet(QString::fromUtf8("border: 1px solid black;"));
        fired_dish_table = new QTableWidget(show_table);
        if (fired_dish_table->columnCount() < 8)
            fired_dish_table->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        fired_dish_table->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        fired_dish_table->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        fired_dish_table->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        fired_dish_table->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        fired_dish_table->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        fired_dish_table->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        fired_dish_table->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        fired_dish_table->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        fired_dish_table->setObjectName("fired_dish_table");
        fired_dish_table->setGeometry(QRect(60, 90, 821, 171));
        fired_dish_table->setMinimumSize(QSize(821, 171));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font.setPointSize(9);
        fired_dish_table->setFont(font);
        fired_dish_table->setStyleSheet(QString::fromUtf8("border: 1px solid gray;"));
        flour_dish_table = new QTableWidget(show_table);
        if (flour_dish_table->columnCount() < 8)
            flour_dish_table->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        flour_dish_table->setHorizontalHeaderItem(0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        flour_dish_table->setHorizontalHeaderItem(1, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        flour_dish_table->setHorizontalHeaderItem(2, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        flour_dish_table->setHorizontalHeaderItem(3, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        flour_dish_table->setHorizontalHeaderItem(4, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        flour_dish_table->setHorizontalHeaderItem(5, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        flour_dish_table->setHorizontalHeaderItem(6, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        flour_dish_table->setHorizontalHeaderItem(7, __qtablewidgetitem15);
        flour_dish_table->setObjectName("flour_dish_table");
        flour_dish_table->setGeometry(QRect(60, 310, 821, 171));
        flour_dish_table->setMinimumSize(QSize(821, 171));
        flour_dish_table->setFont(font);
        flour_dish_table->setStyleSheet(QString::fromUtf8("border: 1px solid gray;"));
        halal_dish_table = new QTableWidget(show_table);
        if (halal_dish_table->columnCount() < 8)
            halal_dish_table->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        halal_dish_table->setHorizontalHeaderItem(0, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        halal_dish_table->setHorizontalHeaderItem(1, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        halal_dish_table->setHorizontalHeaderItem(2, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        halal_dish_table->setHorizontalHeaderItem(3, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        halal_dish_table->setHorizontalHeaderItem(4, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        halal_dish_table->setHorizontalHeaderItem(5, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        halal_dish_table->setHorizontalHeaderItem(6, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        halal_dish_table->setHorizontalHeaderItem(7, __qtablewidgetitem23);
        halal_dish_table->setObjectName("halal_dish_table");
        halal_dish_table->setGeometry(QRect(60, 540, 821, 171));
        halal_dish_table->setMinimumSize(QSize(821, 171));
        halal_dish_table->setFont(font);
        halal_dish_table->setStyleSheet(QString::fromUtf8("border: 1px solid gray;"));
        search_push_button = new QPushButton(show_table);
        search_push_button->setObjectName("search_push_button");
        search_push_button->setGeometry(QRect(370, 30, 80, 23));
        search_push_button->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(show_table);
        label->setObjectName("label");
        label->setGeometry(QRect(60, 70, 50, 15));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(10);
        font1.setBold(true);
        label->setFont(font1);
        label_2 = new QLabel(show_table);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(60, 290, 50, 15));
        label_2->setFont(font1);
        label_3 = new QLabel(show_table);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(60, 520, 50, 15));
        label_3->setFont(font1);
        checkBox = new QCheckBox(show_table);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(460, 30, 101, 21));

        retranslateUi(show_table);

        QMetaObject::connectSlotsByName(show_table);
    } // setupUi

    void retranslateUi(QWidget *show_table)
    {
        show_table->setWindowTitle(QCoreApplication::translate("show_table", "Form", nullptr));
        QTableWidgetItem *___qtablewidgetitem = fired_dish_table->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("show_table", "\350\217\234\345\223\201\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = fired_dish_table->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("show_table", "\351\243\237\346\235\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = fired_dish_table->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("show_table", "\351\244\220\345\216\205", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = fired_dish_table->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("show_table", "\346\245\274\345\261\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = fired_dish_table->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("show_table", "\347\252\227\345\217\243", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = fired_dish_table->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("show_table", "\344\273\267\346\240\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = fired_dish_table->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("show_table", "\350\217\234\347\263\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = fired_dish_table->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("show_table", "\350\215\244\347\264\240", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = flour_dish_table->horizontalHeaderItem(0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("show_table", "\350\217\234\345\223\201\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = flour_dish_table->horizontalHeaderItem(1);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("show_table", "\351\243\237\346\235\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = flour_dish_table->horizontalHeaderItem(2);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("show_table", "\351\244\220\345\216\205", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = flour_dish_table->horizontalHeaderItem(3);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("show_table", "\346\245\274\345\261\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = flour_dish_table->horizontalHeaderItem(4);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("show_table", "\347\252\227\345\217\243", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = flour_dish_table->horizontalHeaderItem(5);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("show_table", "\344\273\267\346\240\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = flour_dish_table->horizontalHeaderItem(6);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("show_table", "\345\217\243\345\221\263", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = flour_dish_table->horizontalHeaderItem(7);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("show_table", "\345\212\240\346\226\231", nullptr));
        QTableWidgetItem *___qtablewidgetitem16 = halal_dish_table->horizontalHeaderItem(0);
        ___qtablewidgetitem16->setText(QCoreApplication::translate("show_table", "\350\217\234\345\223\201\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem17 = halal_dish_table->horizontalHeaderItem(1);
        ___qtablewidgetitem17->setText(QCoreApplication::translate("show_table", "\351\243\237\346\235\220", nullptr));
        QTableWidgetItem *___qtablewidgetitem18 = halal_dish_table->horizontalHeaderItem(2);
        ___qtablewidgetitem18->setText(QCoreApplication::translate("show_table", "\351\244\220\345\216\205", nullptr));
        QTableWidgetItem *___qtablewidgetitem19 = halal_dish_table->horizontalHeaderItem(3);
        ___qtablewidgetitem19->setText(QCoreApplication::translate("show_table", "\346\245\274\345\261\202", nullptr));
        QTableWidgetItem *___qtablewidgetitem20 = halal_dish_table->horizontalHeaderItem(4);
        ___qtablewidgetitem20->setText(QCoreApplication::translate("show_table", "\347\252\227\345\217\243", nullptr));
        QTableWidgetItem *___qtablewidgetitem21 = halal_dish_table->horizontalHeaderItem(5);
        ___qtablewidgetitem21->setText(QCoreApplication::translate("show_table", "\344\273\267\346\240\274", nullptr));
        QTableWidgetItem *___qtablewidgetitem22 = halal_dish_table->horizontalHeaderItem(6);
        ___qtablewidgetitem22->setText(QCoreApplication::translate("show_table", "\350\217\234\347\263\273", nullptr));
        QTableWidgetItem *___qtablewidgetitem23 = halal_dish_table->horizontalHeaderItem(7);
        ___qtablewidgetitem23->setText(QCoreApplication::translate("show_table", "\350\215\244\347\264\240", nullptr));
        search_push_button->setText(QCoreApplication::translate("show_table", "\346\220\234\347\264\242", nullptr));
        label->setText(QCoreApplication::translate("show_table", "\347\202\222\350\217\234\347\261\273", nullptr));
        label_2->setText(QCoreApplication::translate("show_table", "\347\262\211\351\235\242\347\261\273", nullptr));
        label_3->setText(QCoreApplication::translate("show_table", "\346\270\205\347\234\237\347\261\273", nullptr));
        checkBox->setText(QCoreApplication::translate("show_table", "\344\277\235\347\225\231\346\220\234\347\264\242\347\273\223\346\236\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class show_table: public Ui_show_table {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOW_TABLE_H
