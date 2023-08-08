#include "ui/RegWindow/mainwindow.h"
#include "mainwindow.h"

#include <QApplication>
#include<thread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow app;
    app.show();


    return a.exec();
}
