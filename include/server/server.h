#pragma once
#include<boost/asio.hpp>
#include<iostream>
#include<boost/beast.hpp>
#include <optional>
#include <queue>
#include <unordered_set>


using namespace boost::asio;
using namespace boost::beast;

//Класс, ответственный за инициализацию и управление сервером в целом.
class session : public std::enable_shared_from_this<session>
{
public:
    session(boost::asio::ip::tcp::socket&& socket) :
        socket(std::move(socket)) {}

    void read_message();
    void stop();

private:
    void handle_read(const boost::system::error_code& error, std::size_t bytes_transferred);

    boost::asio::ip::tcp::socket socket;
    boost::asio::streambuf streambuf;
};


class Server
{
public:
    Server(boost::asio::io_context& io_context, std::uint16_t port) :
        io_context(io_context),
        acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}

    void async_accept();
    void stop();

private:
    void handle_accept(const boost::system::error_code& error);

    boost::asio::io_context& io_context;
    boost::asio::ip::tcp::acceptor acceptor;
    std::optional<boost::asio::ip::tcp::socket> socket;
};

//Класс, представляющий отдельное клиентское подключение к серверу.
class ClientConnection
{
private:

public:
    ClientConnection();
    ~ClientConnection();

    //Чтение сокета
    void readData();

    //Запись в сокет
    void writeData();

    void start();
};

//Класс, ответственный за обработку входящих запросов от клиентов.
class RequestHandler
{
private:

public:
    RequestHandler();
    ~RequestHandler();

    //Эта функция будет отвечать за обработку входящих запросов от клиентов.Разбирать запросы, выполнять соответствующие операции и отправлять ответы обратно клиентам.
    void handleRequest();
};

//Класс, отвечающий за выполнение запросов к базе данных.
class DatabaseManager
{
private:

public:
    DatabaseManager();
    ~DatabaseManager();

    //отправлять запросы к базе данных
    void executeQuery();
    //обрабатывать полученные результаты.
    void processResult();
};


// Класс, представляющий поток выполнения сервера.
class ServerThread
{
private:

public:
    ServerThread();
    ~ServerThread();
    //эта функция будет представлять основной цикл сервера.слушать входящие соединения,
    //создавать экземпляры класса ClientConnection для каждого подключения и обрабатывать запросы от клиентов.
    void run();
};

