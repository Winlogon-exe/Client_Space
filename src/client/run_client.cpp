#include"client/client.h"

void runClient()
{
    boost::asio::io_context io_context;
    boost::asio::streambuf buffer;
    Client client(io_context, 8080, buffer);
    client.ConnectToServer();
    io_context.run();
}
