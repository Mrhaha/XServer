//
// Created by caizhengyang on 2025/5/7.
//

#ifndef XSERVER_ECHO_SERVER_H
#define XSERVER_ECHO_SERVER_H
#include <asio.hpp>
using asio::ip::tcp;
class Session : public std::enable_shared_from_this<Session> {
public:
    Session(tcp::socket socket);
    void start();
private:
    void do_read();
    void do_write(std::size_t length);

    tcp::socket socket_;
    enum {max_length = 1024};
    char data_[max_length];
};


class EchoServer {
public:
    EchoServer(asio::io_context& io_context, short port);


private:
    void do_accept();
    tcp::acceptor acceptor_;
};
#endif //XSERVER_ECHO_SERVER_H
