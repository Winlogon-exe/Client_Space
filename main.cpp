#include "ui/RegWindow/mainwindow.h"
#include <QApplication>
#include <QStyle>
#include <thread>
#include "server/server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    boost::asio::io_context ioContext;
    Server server(ioContext, 8080); // Порт можно изменить на необходимый
    // Создание и запуск сервера в отдельном потоке

    std::thread serverThread([&](){
        server.startAccepting();
        ioContext.run();
    });

    // Завершение работы сервера при выходе из приложения
    QObject::connect(&a, &QApplication::aboutToQuit, [&](){
        // Остановка сервера
        server.stop();

        // Ожидание завершения работы потока сервера
        serverThread.join();
    });

    return a.exec();
}
