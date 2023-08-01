#include"client/client.h"

void runClient()
{
    auto client_io_context = std::make_shared<boost::asio::io_context>();
    auto server_buffer = std::make_shared<boost::asio::streambuf>();
    auto client = std::make_shared<Client>(*client_io_context, 8080, *server_buffer);
    client->ConnectToServer();

    std::thread client_thread([client_io_context]() {
        client_io_context->run();
    });

    client_thread.join();

    // Остановка io_context после завершения потока клиента
    client_io_context->stop();
}
