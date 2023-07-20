#pragma once
#include <boost/asio.hpp>

class Client
{
public:
    Client(boost::asio::io_context& ioContext, const std::string& serverAddress, const std::string& serverPort);

    void start();

private:
    void readMessage();
    void sendMessage(const std::string& message);

    boost::asio::io_context& ioContext_;
    boost::asio::ip::tcp::socket socket_;
    boost::asio::ip::tcp::resolver resolver_;
    boost::asio::streambuf receiveBuffer_;
};
