#ifndef SERVER_HPP
#define SERVER_HPP

#define YELLOW "\033[33m"
#include <iostream>
#include <netinet/in.h>
#include <fcntl.h>  // for O_RDONLY
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
    Read_conf *config;

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
    int met_delete(char *buffer, int new_socket);
    std::string save_request(int new_socket);
    std::string stat_code;
    std::string stat_to_close;

};

#endif
