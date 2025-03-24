#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

#include <QMessagebox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void IniView();
    void LoginView(bool view = true);
    void AdminView(bool view = true);
    void UserView(bool view = true);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QString GetLoginUsername();
    QString GetLoginPassword();
private:
    Ui::MainWindowClass ui;
protected slots:
    void on_login_push_button_clicked();
    void on_exist_push_button_clicked();

    void on_admin_function_1_button_clicked();
    void on_admin_function_2_button_clicked();
    void on_admin_function_3_button_clicked();
    void on_admin_function_4_button_clicked();
    
    void on_user_function_1_button_clicked();
    void on_user_function_2_button_clicked();
    void on_user_function_3_button_clicked();
    void on_user_function_4_button_clicked();
    
    void on_regist_push_button_clicked();
    void on_exit_user_clicked();
protected:
    void closeEvent(QCloseEvent* e);
};

