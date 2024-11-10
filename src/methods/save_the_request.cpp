#include "../../header/read_conf.hpp"
#include "../../header/server.hpp"

/*std::string Server::save_request(int new_socket)
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
        {
            stat_to_close = 1;
            return "";
        }

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
        {
            stat_to_close = 1;
            return "";
        }

        buffer[bytes_read] = '\0';
        request.append(buffer, bytes_read);
    }
    return (request);
}*/


std::string Server::save_request(int new_socket)
{
    char buffer[2048] = {0};
    ssize_t bytes_read;
    bool end_of_headers = false;
    int content_length = 0;
    std::string request;
    const int MAX_BODY_SIZE = 1024;  // Set body size limit

    // Read headers
    while (!end_of_headers)
    {
        bytes_read = read(new_socket, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0)
        {
            stat_to_close = 1;
            return "";
        }

        buffer[bytes_read] = '\0';
        request += buffer;

        // Check if the end of headers is reached
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

    // Check if content length exceeds max body size
    if (content_length > MAX_BODY_SIZE)
    {
        std::string error_message = "HTTP/1.1 413 Request Entity Too Large\r\nContent-Type: text/plain\r\nContent-Length: 28\r\n\r\nRequest body is too large.";
        write(new_socket, error_message.c_str(), error_message.length());
        stat_to_close = 1;
        return "";
    }

    // Read body data
    while (request.length() < headers_length + content_length)
    {
        bytes_read = read(new_socket, buffer, sizeof(buffer) - 1);
        if (bytes_read <= 0)
        {
            stat_to_close = 1;
            return "";
        }

        buffer[bytes_read] = '\0';
        request.append(buffer, bytes_read);

        // If the total length exceeds the content length, return error
        if (request.length() > headers_length + content_length)
        {
            std::string error_message = "HTTP/1.1 413 Request Entity Too Large\r\nContent-Type: text/plain\r\nContent-Length: 28\r\n\r\nRequest body is too large.";
            write(new_socket, error_message.c_str(), error_message.length());
            stat_to_close = 1;
            return "";
        }
    }

    return request;
}