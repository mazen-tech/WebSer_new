#ifndef SERVER_HPP
#define SERVER_HPP

#define YELLOW "\033[33m"
#include <iostream>
#include <netinet/in.h>
#include "read_conf.hpp"

class Server {
public:
    Server(int port);
    ~Server();
    void start();

private:
    int server_fd;
    int epoll_fd;
    struct sockaddr_in address;
    struct epoll_event ev;
    struct epoll_event events[MAX_EVENTS];
    int addrlen;
    void configureSocket();
    void listenForConnections();
    void handleConnection(int new_socket);
};

#endif // SERVER_HPP
