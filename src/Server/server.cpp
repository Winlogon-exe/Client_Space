#include"server/server.h"

#include<boost/asio.hpp>
#include<iostream>
#include<boost/beast.hpp>
#include<QDebug>

using namespace boost::asio;
using namespace boost::beast;

void session::read_message()
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
                self->read_message();
            }
            else
            {
                // Обработка ошибки чтения
            }
        });
}

void session::stop()
{
    // Закрыть сокет
    socket.close();
    // Очистить буфер
    streambuf.consume(streambuf.size());
    // Освободить другие ресурсы, связанные с сеансом
}

void Server::async_accept()
{
    socket.emplace(io_context);

    acceptor.async_accept(*socket, [&](boost::system::error_code error) {
        if (!error)
        {
            std::make_shared<session>(std::move(*socket))->read_message();
            async_accept();
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
