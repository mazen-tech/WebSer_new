#ifndef SERVER_HPP
#define SERVER_HPP

#define YELLOW "\033[33m"
#include <iostream>
#include <netinet/in.h>
#include "read_conf.hpp"
#include "ErrorPage.hpp"

class Server {
public:
    Server(int port);
    ~Server();
    void start();
    int epoll_fd;
    struct epoll_event ev;
    struct epoll_event events[MAX_EVENTS];

private:
    int server_fd;
    struct sockaddr_in address;
    ErrorPage _errorPage;
    int addrlen;
    
    void configureSocket();
    void listenForConnections();
    void handleConnection(int new_socket);
    int met_post(char *buffer, int new_socket);
    int met_get(char *buffer, int new_socket);
    std::string stat_code;
};

#endif // SERVER_HPP
