#include "client/client.h"
#include <iostream>

Client::Client(boost::asio::io_context& ioContext, const std::string& serverAddress, const std::string& serverPort)
    : ioContext_(ioContext), socket_(ioContext), resolver_(ioContext)
{
    boost::asio::ip::tcp::resolver::results_type endpoints = resolver_.resolve(serverAddress, serverPort);
    boost::asio::connect(socket_, endpoints);
}

void Client::start()
{
    readMessage();
}

void Client::readMessage()
{
    boost::asio::async_read_until(
        socket_,
        receiveBuffer_,
        '\n',
        [this](const boost::system::error_code& error, std::size_t bytes_transferred) {
            if (!error)
            {
                std::istream is(&receiveBuffer_);
                std::string message;
                std::getline(is, message);

                std::cout << "Received message from server: " << message << std::endl;

                readMessage();
            }
            else
            {
                // Обработка ошибки чтения
            }
        });
}

void Client::sendMessage(const std::string& message)
{
    boost::asio::write(socket_, boost::asio::buffer(message + "\n"));
}
