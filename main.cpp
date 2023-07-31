#include "ui/RegWindow/mainwindow.h"
#include "mainwindow.h"
#include "server/server.h"
#include "client/client.h"
#include "server/server_utils.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow app;
    app.show();

    return a.exec();
}
