#include "../../header/read_conf.hpp"
#include "../../header/server.hpp"


int Server::met_delete(char *buffer, int new_socket) {
    char *query_string = strstr(buffer, "DELETE /") + 7;
    char *end_of_uri = strchr(query_string, ' ');
    *end_of_uri = '\0';

    std::string full_uri(query_string);
    std::string file_name = full_uri.empty() ? "index.html" : full_uri;
    std::string file_path = "./src" + file_name;

    std::cout << "Attempting to delete file: " << file_path << std::endl;

    if (remove(file_path.c_str()) == 0) {
        std::string response = "HTTP/1.1 200 OK\r\n"
                               "Content-Length: 0\r\n"
                               "Connection: close\r\n\r\n";
        send(new_socket, response.c_str(), response.size(), 0);
        std::cout << "File deleted successfully.\n";
    } else {
        std::perror("File deletion failed");
        std::string response = "HTTP/1.1 403 Forbidden\r\n"
                               "Content-Length: 0\r\n"
                               "Connection: close\r\n\r\n";
        send(new_socket, response.c_str(), response.size(), 0);
    }

    return 0;
}
