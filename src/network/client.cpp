#include <iostream>
#include <boost/asio.hpp>
#include <memory>

int main(int argc, char* argv[])
{
    boost::asio::io_context io_context;

    // we need a socket and a resolver
    boost::asio::ip::tcp::socket socket(io_context);
    boost::asio::ip::tcp::resolver resolver(io_context);

    // now we can use connect(..)
    boost::asio::connect(socket, resolver.resolve("127.0.0.1", "25000"));

    // and use write(..) to send some data which is here just a string
    std::string data{"some client data ..."};
    boost::asio::async_write(socket, boost::asio::buffer(data),
    [&socket, &io_context](const boost::system::error_code& ec, std::size_t bytes_transferred) {
        if (!ec) {
            std::cout << "data sent: " << bytes_transferred << std::endl;
            // keep the connection open and wait for server response
            boost::asio::streambuf response;
            boost::asio::async_read(socket, response,
                boost::asio::transfer_at_least(1),
                [&socket, &io_context, &response](const boost::system::error_code& ec, std::size_t bytes_transferred) {
                    if (!ec) {
                        std::string response_str(boost::asio::buffer_cast<const char*>(response.data()), bytes_transferred);
                        std::cout << "received response: " << response_str << std::endl;
                    } else {
                        std::cerr << "error: " << ec.message() << std::endl;
                    }
                });
        } else {
            std::cerr << "error: " << ec.message() << std::endl;
        }
    });

    // run the io_context to process the asynchronous operations
    io_context.run();

    return 0;
}