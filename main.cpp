#include"application.h"
#include <QApplication>
#include<thread>

#include "ui/RegWindow/mainwindow.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow app;
    app.show();


    return a.exec();
}
