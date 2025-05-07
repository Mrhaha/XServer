//
// Created by caizhengyang on 2025/5/7.
//
#define ASIO_STANDALONE
#include <asio.hpp>
#include <iostream>
#include <thread>

using asio::ip::tcp;

int main() {
    try {
        asio::io_context io_context;

        // 连接到服务器
        tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve("127.0.0.1", "12345"); // 端口需与 server 一致
        tcp::socket socket(io_context);
        asio::connect(socket, endpoints);

        std::cout << "Connected to echo server. Type messages and press Enter.\n";

        // 启动读线程
        std::thread reader([&socket]() {
            try {
                for (;;) {
                    char data[1024];
                    std::size_t len = socket.read_some(asio::buffer(data));
                    std::cout << "Echoed: " << std::string(data, len) << std::endl;
                }
            } catch (std::exception& e) {
                std::cerr << "[Reader exited] " << e.what() << "\n";
            }
        });

        // 主线程负责发送
        for (std::string line; std::getline(std::cin, line);) {
            asio::write(socket, asio::buffer(line));
        }

        socket.close();
        reader.join();
    } catch (std::exception& e) {
        std::cerr << "[Exception] " << e.what() << "\n";
    }

    return 0;
}
