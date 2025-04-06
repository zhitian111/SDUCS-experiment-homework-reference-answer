#include "MainWindow.h"
#include"regist_window.h"
#include"system.h"
#include"qdir.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    init();
    QDir::addSearchPath("image",QDir::currentPath() + "/image/");
    //QMessageBox::information(NULL, "", QDir::currentPath() + "/image/", QMessageBox::Ok);
    System::main_window = new MainWindow;

    System::main_window->LoginView();
    System::main_window->show();

    return app.exec();
}
