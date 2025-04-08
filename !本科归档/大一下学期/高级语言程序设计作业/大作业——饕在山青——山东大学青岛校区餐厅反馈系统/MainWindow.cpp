#include"MainWindow.h"
#include "system.h"
#include"regist_window.h"
#include"log.h"
#include"show_table.h"
#include"user_change_window.h"
#include"submit_window.h"
#include"log_window.h"
#include"comment_window.h"
#include"manage_dish_window.h"
#include"manage_admin.h"

void MainWindow::IniView()
{
    ui.SystemWidget->setVisible(true);
    ui.background_on_login->setVisible(false);
    ui.exist_push_button->setVisible(false);
    ui.login_push_button->setVisible(false);
    ui.get_password_on_login->setVisible(false);
    ui.get_username_on_login->setVisible(false);
    ui.please_login->setVisible(false);
    ui.show_password->setVisible(false);
    ui.show_username->setVisible(false);
    ui.welcome_text->setVisible(false);
    ui.admin_function_1_button->setVisible(false);
    ui.admin_function_2_button->setVisible(false);
    ui.admin_function_3_button->setVisible(false);
    ui.admin_function_4_button->setVisible(false);
    ui.background_on_using->setVisible(false);
    ui.let_user_regist->setVisible(false);
    ui.regist_push_button->setVisible(false);
    ui.exit_user->setVisible(false);
    ui.user_function_1_button->setVisible(false);
    ui.user_function_2_button->setVisible(false);
    ui.user_function_3_button->setVisible(false);
    ui.user_function_4_button->setVisible(false);
}


void MainWindow::LoginView(bool view)
{
    IniView();
    ui.background_on_login->setVisible(view);
    ui.exist_push_button->setVisible(view);
    ui.login_push_button->setVisible(view);
    ui.get_password_on_login->setVisible(view);
    ui.get_username_on_login->setVisible(view);
    ui.please_login->setVisible(view);
    ui.show_password->setVisible(view);
    ui.show_username->setVisible(view);
    ui.welcome_text->setVisible(view);
    ui.let_user_regist->setVisible(view);
    ui.regist_push_button->setVisible(view);
}

void MainWindow::AdminView(bool view)
{
    ui.admin_function_1_button->setVisible(view);
    ui.admin_function_2_button->setVisible(view);
    ui.admin_function_3_button->setVisible(view);
    ui.admin_function_4_button->setVisible(view);
    ui.background_on_using->setVisible(view);
    ui.exit_user->setVisible(view);
}

void MainWindow::UserView(bool view)
{
    ui.user_function_1_button->setVisible(view);
    ui.user_function_2_button->setVisible(view);
    ui.user_function_3_button->setVisible(view);
    ui.user_function_4_button->setVisible(view);
    ui.background_on_using->setVisible(view);
    ui.exit_user->setVisible(view);
}



void MainWindow::on_admin_function_1_button_clicked()
{
    ManageAdminWindow* tem = new ManageAdminWindow(this);
    tem->show();
    return;
}

void MainWindow::on_admin_function_2_button_clicked()
{
    ManageDishWindow* tem = new ManageDishWindow(this);
    tem->show();
    return;
}

void MainWindow::on_admin_function_3_button_clicked()
{
    CommentWindow* tem = new CommentWindow(this);
    tem->show();
    return;
}

void MainWindow::on_admin_function_4_button_clicked()
{

    LogWindow* tem = new LogWindow(this);
    tem->show();
    return;

}




void MainWindow::on_user_function_1_button_clicked()
{
    ShowTable* tem = new ShowTable(this , 1);
    tem->show();
    return;
}

void MainWindow::on_user_function_2_button_clicked()
{
    WindowSubmit* tem = new WindowSubmit(this);
    tem->show();
    return;
}

void MainWindow::on_user_function_3_button_clicked()
{
    UserChange* tem = new UserChange(this);
    tem->show();
    return;
}

void MainWindow::on_user_function_4_button_clicked()
{
    ShowTable* tem = new ShowTable(this, 4);
    tem->show();
    return;
}




MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    Log("SYSTEM", "Start running");
    ui.setupUi(this);
    ui.get_password_on_login->setEchoMode(QLineEdit::Password);
    ui.regist_push_button->setFocusPolicy(Qt::NoFocus);
    ui.login_push_button->setFocusPolicy(Qt::NoFocus);
    ui.exist_push_button->setFocusPolicy(Qt::NoFocus);

    connect(ui.login_push_button, &QPushButton::click, this, &MainWindow::on_login_push_button_clicked);
    connect(ui.exist_push_button, &QPushButton::click, this, &MainWindow::on_exist_push_button_clicked);
    
    connect(ui.get_password_on_login, SIGNAL(returnPressed()), this, SLOT(on_login_push_button_clicked()));
    connect(ui.get_username_on_login, SIGNAL(returnPressed()), this, SLOT(on_login_push_button_clicked()));

    connect(ui.admin_function_1_button, &QPushButton::click, this, &MainWindow::on_admin_function_1_button_clicked);
    connect(ui.admin_function_2_button, &QPushButton::click, this, &MainWindow::on_admin_function_2_button_clicked);
    connect(ui.admin_function_3_button, &QPushButton::click, this, &MainWindow::on_admin_function_3_button_clicked);
    connect(ui.admin_function_4_button, &QPushButton::click, this, &MainWindow::on_admin_function_4_button_clicked);

    connect(ui.user_function_1_button, &QPushButton::click, this, &MainWindow::on_user_function_1_button_clicked);
    connect(ui.user_function_2_button, &QPushButton::click, this, &MainWindow::on_user_function_2_button_clicked);
    connect(ui.user_function_3_button, &QPushButton::click, this, &MainWindow::on_user_function_3_button_clicked);
    connect(ui.user_function_4_button, &QPushButton::click, this, &MainWindow::on_user_function_4_button_clicked);


    connect(ui.regist_push_button, &QPushButton::click, this, &MainWindow::on_regist_push_button_clicked);

    connect(ui.exit_user,&QPushButton::click,this,&MainWindow::on_exit_user_clicked);

    IniView();
    Log("SYSTEM", "Open the main window");

}
void MainWindow::closeEvent(QCloseEvent* e)
{
    Log("SYSTEM", "Close the main window");
    delete(this);
    e->accept();
}


MainWindow::~MainWindow()
{
    OutPutData();
    Log("SYSTEM", "Stop running");
}

QString MainWindow::GetLoginPassword()
{
    return ui.get_password_on_login->text();
}
QString MainWindow::GetLoginUsername()
{
    return ui.get_username_on_login->text();
}

void MainWindow::on_login_push_button_clicked()
{
    QString temusername = GetLoginUsername();
    QString tempassword = GetLoginPassword();
    if (temusername == "")
    {
        Log(temusername.toStdString(), "Tried to login,failed");
        QMessageBox::information(this, "登录失败", "请输入账号", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        
        return;
    }
    if (temusername != "" && tempassword == "")
    {
        Log(temusername.toStdString(), "Tried to login,failed");
        QMessageBox::information(this, "登录失败", "请输入密码", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }
    if (students_and_teachers.count(temusername.toStdString()) == 0 && admins.count(temusername.toStdString()) == 0)
    {
        Log(temusername.toStdString(), "Tried to login,failed");
        QMessageBox::information(this, "登录失败", "该用户不存在", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        return;
    }

    if (students_and_teachers.count(temusername.toStdString()) == 1)
    {
        System::usertype = STUDENT_AND_TEACHER;
        System::student_and_teacher = students_and_teachers[temusername.toStdString()];
        if (System::student_and_teacher.Login(tempassword.toStdString()))
        {
            Log(temusername.toStdString(), "Tried to login,successed");
            QMessageBox::information(this, "登录成功", "登录成功,按任意键继续", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            ui.get_password_on_login->clear();
            ui.get_username_on_login->clear();
            LoginView(false);
            UserView(true);
            return;
        }
        else
        {
            Log(temusername.toStdString(), "Tried to login,failed");
            QMessageBox::information(this, "登录失败", "用户名或密码错误", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            System::usertype = NONE;
        }
    }

    if (admins.count(temusername.toStdString()) == 1)
    {
        System::usertype = ADMIN;
        System::admin = admins[temusername.toStdString()];
        if (System::admin.Login(tempassword.toStdString()))
        {
            Log(temusername.toStdString(), "Tried to login,successed");
            QMessageBox::information(this, "登录成功", "登录成功,按任意键继续", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            ui.get_password_on_login->clear();
            ui.get_username_on_login->clear();
            LoginView(false);
            AdminView(true);

            return;
        }
        else
        {
            Log(temusername.toStdString(), "Tried to login,failed");
            QMessageBox::information(this, "登录失败", "用户名或密码错误", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            System::usertype = NONE;
        }
        return;
    }

}

void MainWindow::on_exist_push_button_clicked()
{
    QMessageBox::StandardButton box;
    box = QMessageBox::question(this,"确认退出", "确认要退出系统吗？",QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (box != QMessageBox::Yes)
    {
        return;
    }
    QApplication* app = NULL;
    app->quit();
}






void MainWindow::on_regist_push_button_clicked()
{
    RegistWindow* tem = new RegistWindow(this);
    tem->show();
}

void MainWindow::on_exit_user_clicked()
{
    QMessageBox::StandardButton box;
    box = QMessageBox::question(this, "确认登出", "确认要退出账号吗？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    if (box != QMessageBox::Yes)
    {
        return;
    }
    if (System::usertype == ADMIN)
    {
        Log(System::admin.GetUsername(), "Logout");
        System::admin.Exit();
        AdminView(false);
        LoginView(true);
    }
    if (System::usertype == STUDENT_AND_TEACHER)
    {
        Log(System::student_and_teacher.GetUsername(), "Logout");
        System::student_and_teacher.Exit();
        UserView(false);
        LoginView(true);
    }
    System::student_and_teacher = null_user;
    System::admin = null_admin;
    System::usertype = NONE;

}