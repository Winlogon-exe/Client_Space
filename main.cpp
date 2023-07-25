#include "ui/RegWindow/mainwindow.h"
#include "client/client.h"
#include "server/server.h"
#include"application.h"

#include <QApplication>
#include <QStyle>
#include <thread>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Application app;
    app.show();

    boost::asio::io_context server_io_context;
    boost::asio::io_context client_io_context;

    uint16_t server_port = 8080;

    // Создаем объект сервера и передаем io_context и порт в конструктор
    boost::asio::streambuf server_buffer;
    auto  server = std::make_shared<Server>(server_io_context, server_port, server_buffer);

    // Создаем объект клиента и передаем io_context и порт в конструктор
     auto client = std::make_shared<Client>(client_io_context, server_port, server_buffer);

    server->Listening();
    client->ConnectToServer();

    // Запускаем io_context для сервера и клиента
    // Запускаем io_context для сервера и клиента
    std::thread server_thread([&]() {
        server_io_context.run_for(std::chrono::seconds::max());
    });

    std::thread client_thread([&]() {
        client_io_context.run_for(std::chrono::seconds::max());
    });
    server_thread.join();
    client_thread.join();

    return a.exec();
}
