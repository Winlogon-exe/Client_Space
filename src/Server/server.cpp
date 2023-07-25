#include "server/server.h"

Session::Session(boost::asio::ip::tcp::socket socket)
    : socket(std::move(socket)){}


void Session::read_message()
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
                qDebug() << "Error reading message: " << error.message();
            }
        });
}

void Session::stop()
{
    socket.close();
    streambuf.consume(streambuf.size());
}

Server::Server(boost::asio::io_context& ioContext, const std::string& address, const std::string& port)
    : acceptor(ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(address), std::stoi(port))),
    io_context(ioContext){}

void Server::start()
{
    async_accept();
}

void Server::async_accept()
{
    socket.emplace(io_context);

    acceptor.async_accept(*socket, [&](const boost::system::error_code& error) {
        if (!error)
        {
            std::make_shared<Session>(std::move(*socket))->read_message();
            async_accept();
        }
        else
        {
            qDebug() << "Error async_accept: " << error.message();
        }
    });
}

void Server::stop()
{
    acceptor.close();
    if (socket)
    {
        socket->close();
    }
}
