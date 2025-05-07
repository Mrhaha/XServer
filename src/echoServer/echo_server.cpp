//
// Created by caizhengyang on 2025/5/7.
//
#include "echoServer/echo_server.h"
#include <iostream>
#include <memory>

Session::Session(tcp::socket socket): socket_(std::move(socket)){}
void Session::start() {
    do_read();
}
void Session::do_read() {
    auto self = shared_from_this();
    socket_.async_read_some(asio::buffer(data_,max_length),[this,self](std::error_code ec,std::size_t length){
        if (!ec) {
            do_write(length);
        }
    });
}

void Session::do_write(std::size_t length) {
    auto self = shared_from_this();
    asio::async_write(socket_, asio::buffer(data_, length),
                      [this, self](std::error_code ec, std::size_t /*length*/) {
                          if (!ec)
                              do_read();
                      });
}


EchoServer::EchoServer(asio::io_context& io_context, short port):
    acceptor_(io_context,tcp::endpoint (tcp::v4(),port)) {
        do_accept();
    }


void EchoServer::do_accept() {
    acceptor_.async_accept([this](std::error_code ec,tcp::socket socket){
        if(!ec) {
            std::make_shared<Session>(std::move(socket))->start();
            do_accept();
        }
    });
}





















