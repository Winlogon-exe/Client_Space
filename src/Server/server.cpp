#include "server/server.h"
#include <boost/asio.hpp>
#include <iostream>
#include <boost/beast.hpp>
#include <QDebug>

using namespace boost::asio;
using namespace boost::beast;

void ClientSession::startReading()
{
    boost::asio::async_read_until(
        socket,
        streambuf,
        '\n',
        [self = shared_from_this()](const boost::system::error_code& error, std::size_t bytes_transferred) {
            if (!error)
            {
                // Обработка полученного сообщения
                std::istream is(&self->streambuf);
                std::string message;
                std::getline(is, message);

                // Вывод сообщения
                qDebug() << "Received message: " << QString::fromStdString(message);

                // Продолжение чтения
                self->startReading();
            }
            else
            {
                // Обработка ошибки чтения
            }
        });
}

void ClientSession::stop()
{
    // Закрыть сокет
    socket.close();
    // Очистить буфер
    streambuf.consume(streambuf.size());
    // Освободить другие ресурсы, связанные с сеансом
}

void Server::startAccepting()
{
    socket.emplace(io_context);

    acceptor.async_accept(*socket, [&](const boost::system::error_code& error) {
        if (!error)
        {
            std::make_shared<ClientSession>(std::move(*socket))->startReading();
            startAccepting();
        }
        else
        {
            // Обработка ошибки принятия соединения
        }
    });
}

void Server::stop()
{
    // Остановить прослушивание новых соединений
    acceptor.close();
    // Закрыть сокет, если он открыт
    if (socket)
    {
        socket->close();
    }
}
