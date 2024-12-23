/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdela <maabdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:45:05 by maabdela          #+#    #+#             */
/*   Updated: 2024/11/13 16:56:05 by maabdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef SERVER_HPP
#define SERVER_HPP

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
    Read_conf *config;
    std::vector <std::string> red;
    std::string redarections(std::string &request);


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
