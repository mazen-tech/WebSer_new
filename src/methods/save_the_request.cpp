#include "../../header/read_conf.hpp"

std::string save_request(int new_socket)
{
    char buffer[2048] = {0};
    ssize_t bytes_read;
    bool end_of_headers = false;
    int content_length = 0;
    std::string request;

    while (!end_of_headers)
    {
        bytes_read = read(new_socket, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0)
            break;

        buffer[bytes_read] = '\0';
        request += buffer;

        if (request.find("\r\n\r\n") != std::string::npos)
            end_of_headers = true;
    }
    size_t headers_length = request.find("\r\n\r\n") + 4;
    size_t content_length_pos = request.find("Content-Length: ");
    if (content_length_pos != std::string::npos)
    {
        size_t start_pos = content_length_pos + 16;
        size_t end_pos = request.find("\r\n", start_pos);
        if (end_pos != std::string::npos)
        {
            std::string content_length_str = request.substr(start_pos, end_pos - start_pos);
            content_length = std::stoi(content_length_str);
        }
    }
    while (request.length() < headers_length + content_length)
    {
        bytes_read = read(new_socket, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0)
            break;

        buffer[bytes_read] = '\0';
        request.append(buffer, bytes_read);
        std::cout << request.length() << std::endl;
    }
    return (request);
}
