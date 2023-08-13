#include <boost/asio.hpp>
#include "client/run_client.h"
#include "client/client.h"

RunClient& RunClient::getInstance() {
    static RunClient instance; // Создаем только один экземпляр
    return instance;
}

void RunClient::run(const QString &email, const QString &username, const QString &password) {

    client = std::make_shared<Client>(io_context, 49152);
    client->connectToServer(email.toStdString(), username.toStdString(), password.toStdString());
    io_context.run();
}

void RunClient::startMessage(const std::string &data) {
    // Вызываем sendMessage для клиента
    client->sendMessage(data);
}
RunClient::RunClient() {

}
