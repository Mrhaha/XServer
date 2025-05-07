//
// Created by caizhengyang on 2025/5/7.
//
#include "echoServer/echo_server.h"
#include <iostream>
int main() {
    try {
        asio::io_context ioContext;
        EchoServer server(ioContext,12345);
        std::cout << "Echo server running on port 12345" << std::endl;
        ioContext.run();
    } catch (std::exception e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}