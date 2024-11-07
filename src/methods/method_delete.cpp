#include "../../header/read_conf.hpp"
// this fill will be ...

int met_delete(char *buffer, int new_socket)
{
    char *query_string = strstr(buffer, "DELETE /") + 5;
    char *end_of_uri = strchr(query_string, ' ');
    *end_of_uri = '\0';

    std::string full_uri(query_string);
    std::string file_name = full_uri.empty() ? "index.html" : full_uri;

    //construct file path
    std::string file_path;
    if (find_file("./src", file_name, file_path))
    {
        if (remove(file_path.c_str()) == 0)
        {
            std::string response = "HTTP/1.1 200 OK\r\n"
                                    "Content-Length: 0\r\n"
                                    "Connection: close\r\n\r\n";
            send(new_socket, response.c_str(), response.size(), 0);
        }

        else
        {
            std::string response = "HTTP/1.1 403 Forbidden\r\n"
                                   "Content-Length: 0\r\n"
                                   "Connection: close\r\n\r\n";
            send(new_socket, response.c_str(), response.size(), 0);
        }
    }
    else
    {
        std::string response = "HTTP/1.1 404 Not Found\r\n"
                               "Content-Length: 0\r\n"
                               "Connection: close\r\n\r\n";
        send(new_socket, response.c_str(), response.size(), 0);
    }
    return (0);
}