#include <iostream>
#include <boost/asio.hpp>

#include "client/client.h"
#include"QDebug"

Client::Client(boost::asio::io_context& io_context, uint16_t port, boost::asio::streambuf& buffer)
    : io_context_(io_context),
    socket_(io_context),
    port_(port),
    buffer_(buffer) {}

void Client::ConnectToServer() {
    boost::asio::ip::tcp::resolver resolver(io_context_);
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), "127.0.0.1", std::to_string(port_));
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    boost::asio::async_connect(socket_, endpoint_iterator,
    [this](boost::system::error_code error, boost::asio::ip::tcp::resolver::iterator) {
        if (!error) {
            qDebug() << "Client: Connected to server, port:" << port_;
            SendPostRequest(); // Вызываем функцию для отправки POST-запроса
        } else {
            qDebug() << "Failed to connect to server: " << error.message();
        }
    });
}

void Client::SendPostRequest() {
    std::string request = "POST /post HTTP/1.1\r\n"
                          "Host: localhost\r\n"
                          "Content-Type: text/plain\r\n"
                          "Content-Length: 14\r\n"
                          "\r\n"
                          "Hello, server!";

boost::asio::async_write(socket_, boost::asio::buffer(request),
[this](boost::system::error_code error, std::size_t bytes_transferred) {
    if (!error) {
        qDebug() << "Client: POST request sent to server";
        ReceiveResponse(); // Вызываем функцию для получения ответа от сервера
    } else {
        qDebug() << "Failed to send POST request: " << error.message();
    }
});
}

void Client::ReceiveResponse() {
    boost::asio::async_read_until(socket_, buffer_, "\r\n\r\n",
  [this](boost::system::error_code error, std::size_t bytes_transferred) {
      if (!error) {
          std::istream response_stream(&buffer_);
          std::string http_version;
          response_stream >> http_version;
          unsigned int status_code;
          response_stream >> status_code;
          std::string status_message;
          std::getline(response_stream, status_message);

          if (!response_stream || http_version.substr(0, 5) != "HTTP/") {
              qDebug() << "Invalid response";
              return;
          }

          if (status_code != 200) {
              qDebug() << "Server returned error: " << status_code;
              return;
          }

          std::ostringstream response_body_stream;
          if (bytes_transferred > 4) {
              response_body_stream << &buffer_;
          }
          qDebug() << "Server response: " << QString::fromStdString(response_body_stream.str());
      } else {
          qDebug() << "Failed to receive response: " << error.message();
      }
  });
}
