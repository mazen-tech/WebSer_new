#include "../../header/server.hpp"
#include "../../header/read_conf.hpp"
#include "../../header/ErrorPage.hpp"

Server::Server(int port) {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    stat_to_close = "0";
    if (server_fd == 0) {
        std::cerr << "Failed to create socket\n";
        exit(EXIT_FAILURE);
    }

    configureSocket();

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        std::cerr << "Bind Failed\n";
        exit(EXIT_FAILURE);
    }
}

Server::~Server() {
    close(server_fd);
    close(epoll_fd);
}

void Server::configureSocket() {
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
}

void Server::start() {
    listenForConnections();
}

void Server::listenForConnections() {
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Listening failed\n";
        exit(EXIT_FAILURE);
    }

    epoll_fd = epoll_create1(EPOLL_CLOEXEC); // flaga zamykajaca automatycznie deskryptor
    ev.events = EPOLLIN | EPOLLOUT; // okresla jakie typy eventow ma monitorowac
    // w naszym przypadku odczyt i zapis
    ev.data.fd = server_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_fd, &ev);// pozwala zarzadzac zdarzeniami w kolejce
    // EPOLL_CTL_ADD dodaje desktyptor pliku do epolla

    std::cout << GREEN << "Server is running...\n" << RESET;
    std::cout << GREEN << "Server is listening on port.... " << RESET << std::endl; 

    while (true) {
        int nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, 100);// bedzie czekac na zdarzenia oraz je monitor
        for (int i = 0; i < nfds; i ++)
        {
            if (events[i].data.fd == server_fd) //oznacza to ze mamy nowe polaczenie przychodzace
            {
                int addrlen = sizeof(address);
                int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
                if (new_socket < 0)
                {
                    std::cerr << "Connection error\n";
                    continue;
                }
                ev.events = EPOLLIN | EPOLLOUT;
                ev.data.fd = new_socket;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_socket, &ev);
            }
            else
            {
                handleConnection(events[i].data.fd);
                close(events[i].data.fd);
            }
        }

    }
}

void Server::handleConnection(int new_socket) {
    std::string request;

    request = save_request(new_socket);
    // std::cout << request << std::endl;
    if (stat_to_close == "1")
    {
        return ;
    }
    stat_code = "200";
    if (request.find("POST /") != std::string::npos)
    {
        
        if (met_post((char *)request.c_str(), new_socket))
        {
            std::cerr << "POST request handling failed\n";
            return;
        }
        else 
        {
            std::cout << RED << "Response sent to client " << RESET << new_socket << " " << "[POST]" << RED << " with status code: " << RESET << stat_code << std::endl;
        }
    }

    else if (request.find("GET /") != std::string::npos)
    {
        if (met_get((char *)request.c_str(), new_socket))
        {
            std::cerr << "GET request handling failed\n";
            return;
        }
        else 
        {
            std::cout << YELLOW << "Response sent to client " << RESET << new_socket << " " << "[GET]" << YELLOW << " with status code: " << RESET << stat_code << std::endl;
        }

    }

    else if (request.find("DELETE /") != std::string::npos)
    {
        if (met_delete((char *)request.c_str(), new_socket))
        {
            std::cerr << "Delete request handling failed\n";
            return;
        }
        else 
        {
            std::cout << PURPLE << "Response sent to client " << RESET << "[DELETE]" << PURPLE << " with status code: " << RESET << stat_code << std::endl;
        }
    }

    else
    {
        stat_code = "400";
        std::string http_response =
            "HTTP/1.1 400 Bad request\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: " + std::to_string((_errorPage.getErrPage(400)).length()) +
            "\r\n\r\n" +
            _errorPage.getErrPage(400);
        // std::cout << http_response << std::endl;
        send(new_socket, http_response.c_str(), http_response.length(), 0);
        std::cout << BLUE << "Response sent to client" << RESET << " [GENERIC] " << PURPLE << "with status code: " << RESET << stat_code << std::endl;
    }

    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, new_socket, NULL);
    close(new_socket);
}
