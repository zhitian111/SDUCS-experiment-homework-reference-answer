#include "MainWindow.h"
#include"regist_window.h"
#include"system.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    init();

    System::main_window = new MainWindow;

    System::main_window->LoginView();
    System::main_window->show();

    return app.exec();
}
