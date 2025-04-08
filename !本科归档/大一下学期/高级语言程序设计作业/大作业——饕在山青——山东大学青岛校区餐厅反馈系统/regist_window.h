#pragma once
#include"ui_UserRegistWindow.h"
#include<QtWidgets/qwidget.h>
#include <QtWidgets/QMainWindow>
#include <QCloseEvent> 

class RegistWindow : public QMainWindow
{
    Q_OBJECT

public:
    RegistWindow(QWidget* parent = nullptr);
    ~RegistWindow() {};
private:
    Ui::Regist ui;
protected slots:
    void on_regist_push_button_clicked();
    void on_cancel_push_button_clicked();
protected:
    void closeEvent(QCloseEvent* e);
};

