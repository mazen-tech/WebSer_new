#include "../../header/read_conf.hpp"
#include "../../header/server.hpp"
#include "../../header/confParsing.hpp"

// ZMIANA JANEK !!!!!!!!!

std::string Server::save_request(int new_socket)
{
    char buffer[1024] = {0};
    ssize_t bytes_read;
    std::string request;
    ssize_t bytes = 0;
    // int round = 0;
    std::cout << this->config->getCwd() << "\n";
    std::string path =  this->config->getCwd() + "/configurations/config.conf";
    ssize_t max_by = parseClientMaxBodySize(path);
    int cl = 0;
    while (true)
    {
        bzero(buffer, 1024);
        bytes_read = read(new_socket, buffer, sizeof(buffer) - 1);
        bytes += bytes_read;
        request.append(buffer, bytes_read);
        if (request.find("POST /") != std::string::npos)
        {
            if (cl == 0)
            {
                std::string content_length;
                content_length = &request[request.find("Content-Length: ")];
                content_length = &content_length[sizeof("Content-Length:")];
                content_length[content_length.find('\r')] = 0;
                cl = atoi(content_length.c_str());
                cl += request.find("\r\n\r\n") + 4;
            }
            if (bytes >= cl && cl != 0)
                break;
        }
        else
            break;
    }
    // if (request.find("GET /") != std::string::npos && bytes > 1024)
    // {
    //     stat_code = "413";
    //     return "";
    // }
// END ZMIANA JANEK !!!!!!!!!
    if (bytes > max_by)
    {
        stat_code = "413";
        return "";
    }
    return (request);
}
