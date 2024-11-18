#include "../../header/read_conf.hpp"
#include "../../header/server.hpp"
#include "../../header/confParsing.hpp"

std::string Server::save_request(int new_socket)
{
    char buffer[10000] = {0};
    ssize_t bytes_read;
    std::string request;
    ssize_t bytes = 0;
    int round = 0;
    ssize_t max_by = parseClientMaxBodySize("/mnt/c/Users/miche/OneDrive/Desktop/WebSer_new/configurations/config.conf");
    while (true)
    {
        bytes_read = read(new_socket, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0)
        {
            stat_to_close = 1;
            return "";
        }

        buffer[bytes_read] = '\0';
        request.append(buffer, bytes_read);

        bytes += bytes_read;
        round ++;
        if (bytes_read < 9999)
            break;
    }
    if (request.find("GET /") != std::string::npos && bytes > 1024)
    {
        stat_code = "413";
        return "";
    }
    if (bytes > max_by)
    {
        stat_code = "413";
        return "";
    }
    return (request);
}
