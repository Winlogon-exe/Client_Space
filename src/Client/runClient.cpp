#include"client/client.h"
#include"client/run_client.h"
void runClient(const QString& email, const QString& username, const QString& password) {
    boost::asio::io_context io_context;
    boost::asio::streambuf buffer;
    Client client(io_context, 80, buffer);
    client.connectToServer(email.toStdString(), username.toStdString(), password.toStdString());
    io_context.run();
}
