#include"client/client.h"
#include"client/run_client.h"
void runClient(const QString &email, const QString &username, const QString &password) {
    boost::asio::io_context io_context;
    boost::asio::streambuf buffer;
    std::shared_ptr<Client> client;
    client = std::make_shared<Client>(io_context, 49152);
    client->connectToServer(email.toStdString(), username.toStdString(), password.toStdString());

    client->sendMessage("123");
    io_context.run();
}
