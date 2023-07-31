#include "server/server.h"
#include"client/client.h"

#include<mainwindow.h>
#include <QDebug> // Включаем заголовочный файл для использования qDebug()

Server::Server(boost::asio::io_context& io_context, uint16_t port, boost::asio::streambuf& buffer)
    : io_context_(io_context),
    port_(port),
    acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

Connection::Connection(boost::asio::io_context& io_context) :
    socket_(io_context),
    buffer_(std::make_shared<boost::asio::streambuf>()) {}

void Connection::Start()
{
    ReadData();
}

boost::asio::ip::tcp::socket& Connection::socket()
{
    return socket_;
}

void Connection::ReadData()
{
    auto self = shared_from_this();
    boost::asio::async_read_until(socket_, *buffer_, "\n",
    [this, self](boost::system::error_code error, std::size_t bytes_transferred)
    {
        if (!error)
        {
            std::istream input_stream(buffer_.get());
            std::string data;
            std::getline(input_stream, data);
            qDebug()<< "\nПрочитанные данные:" << data;
            ReadData();
        }
        else
        {
            qDebug()<< "Failed to read data: " << error.message();
        }
    });
}

void Server::Listening()
{
    //create object when makes connection
    auto connection = std::make_shared<Connection>(io_context_);
    acceptor_.async_accept(connection->socket(), [this, connection](const boost::system::error_code& error)
    {
        if (!error)
        {
           qDebug() << "Server: Listening " << "port:"<<port_;
           connection->Start();
        }
        else
        {
          qDebug() << "\nFailed listening server: \n" << error.message();
        }
        Listening();
    });
}


