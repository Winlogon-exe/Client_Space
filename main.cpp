#include "ui/RegWindow/mainwindow.h"
#include "client/client.h"
#include "server/server.h"
#include"application.h"

#include <QApplication>
#include <QStyle>
#include <thread>

void runServer(boost::asio::io_context& ioContext)
{
    std::string serverAddress = "127.0.0.1";
    std::string serverPort = "8080";

    Server server(ioContext, serverAddress, serverPort);
    server.start();
    //log
    qDebug() << "Server started and listening on" << QString::fromStdString(serverAddress) << ":" << QString::fromStdString(serverPort);
}

void runClient(boost::asio::io_context& ioContext)
{
    std::string serverAddress = "127.0.0.1";
    std::string serverPort = "8080";

    Client client(ioContext, serverAddress, serverPort);
    client.start();
    //log
    qDebug() << "Client connected to" << QString::fromStdString(serverAddress) << ":" << QString::fromStdString(serverPort);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application app;
    app.show();

    boost::asio::io_context ioContext;

    // Запуск сервера и клиента
    std::thread serverThread(runServer, std::ref(ioContext));
    std::thread clientThread(runClient, std::ref(ioContext));


    // После выхода из цикла io_context, убедитесь, что все потоки завершились
    serverThread.join();
    clientThread.join();

    return a.exec();
}
