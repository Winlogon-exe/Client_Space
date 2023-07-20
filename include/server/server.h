#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <boost/beast.hpp>
#include <QDebug>

class Session : public std::enable_shared_from_this<Session>
{
public:
    explicit Session(boost::asio::ip::tcp::socket socket);

    void read_message();
    void stop();

private:
    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
};

class Server
{
public:
    Server(boost::asio::io_context& ioContext, const std::string& address, const std::string& port);

    void start();
    void async_accept();
    void stop();

private:
    boost::asio::ip::tcp::acceptor acceptor;
    boost::asio::io_context& io_context;
    std::optional<boost::asio::ip::tcp::socket> socket;
};
