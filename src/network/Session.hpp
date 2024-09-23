/*
** EPITECH PROJECT, 2024
** R-Type-epitech
** File description:
** Session
*/

#ifndef SESSION_HPP_
#define SESSION_HPP_


#include <boost/asio.hpp>
#include <string>
#include <iostream>


class session : public std::enable_shared_from_this<session>
{
public:
    // our sesseion holds the socket
    session(boost::asio::ip::tcp::socket socket)  
    : m_socket(std::move(socket)) { }
    
    // and run was already called in our server, where we just wait for requests
    void run() {
        wait_for_request();
    }
private:
    void wait_for_request() {
        // since we capture `this` in the callback, we need to call shared_from_this()
        auto self(shared_from_this());
        // and now call the lambda once data arrives
        // we read a string until the null termination character
        boost::asio::async_read_until(m_socket, m_buffer, "\0", 
        [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            // if there was no error, everything went well and for this demo
            // we print the data to stdout and wait for the next request
            if (!ec)  {
                std::string data{
                    std::istreambuf_iterator<char>(&m_buffer), 
                    std::istreambuf_iterator<char>() 
                };
                // we just print the data, you can here call other api's 
                // or whatever the server needs to do with the received data
                std::cout << data << std::endl;
                wait_for_request();
            } else {
                std::cout << "error: " << ec << std::endl;;
            }
        });
    }
private:
    boost::asio::ip::tcp::socket m_socket;
    boost::asio::streambuf m_buffer;
};

#endif /* !SESSION_HPP_ */
