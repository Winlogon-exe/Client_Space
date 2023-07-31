#include "server/server.h"
#include "client/client.h"
#include <boost/asio.hpp>

void runServerAndClient()
{
    auto server_io_context = std::make_shared<boost::asio::io_context>();
    auto server_buffer = std::make_shared<boost::asio::streambuf>();
    auto server = std::make_shared<Server>(*server_io_context, 8080, *server_buffer);
    server->Listening();

    auto client_io_context = std::make_shared<boost::asio::io_context>();
    auto client = std::make_shared<Client>(*client_io_context, 8080, *server_buffer);
    client->ConnectToServer();

    std::thread server_thread([server_io_context]() {
        server_io_context->run();
    });

    std::thread client_thread([client_io_context]() {
        client_io_context->run();
    });

    server_thread.join();
    client_thread.join();

    // Остановка io_context после завершения потоков
    server_io_context->stop();
    client_io_context->stop();
}
