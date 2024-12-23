/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   method_get.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:59:16 by bkotwica          #+#    #+#             */
/*   Updated: 2024/11/18 11:59:16 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../header/read_conf.hpp"
#include "../../header/server.hpp"
#include "../../header/ErrorPage.hpp"

int Server::met_get(char *buffer, int new_socket)
{
    char* query_string = strstr(buffer, "GET /") + 5;
    char* end_of_uri = strchr(query_string, ' ');
    *end_of_uri = '\0';

    std::string full_uri(query_string);
    std::string file_name;

    // Rozdzielenie nazwy pliku i query string
    size_t query_pos = full_uri.find('?');
    std::string query_params;
    if (query_pos != std::string::npos) {
        file_name = full_uri.substr(0, query_pos); // tylko nazwa pliku
        query_params = full_uri.substr(query_pos + 1); // część po "?"
    } else {
        file_name = full_uri; // brak query string
        if (file_name.length() == 0)
            file_name = "index.html";
    }
    std::string file_path;
    if (file_name.find(".py") != std::string::npos)
    {
        // Obsługa skryptu CGI
        int pipefd[2];
        if (pipe(pipefd) == -1) {
            std::cerr << "Błąd przy tworzeniu pipe." << std::endl;
            return 1;
        }

        pid_t pid = fork();
        if (pid == 0) {
            // Proces potomny (skrypt CGI)
            close(pipefd[0]);  // Zamykamy odczytanie w dziecku
            dup2(pipefd[1], STDOUT_FILENO);  // Przekierowanie `stdout` na zapis potoku
            close(pipefd[1]);
        // std::cout << "j ";
            // Ustawianie zmiennej QUERY_STRING dla skryptu CGI
        const char *python_path = "/usr/bin/python3";
        const char *script_path = "./src/cgi/mycgi.py";
        const char *page = file_name.c_str();
        const char *method = "GET";
        // PASS REQUESTED PAGE (eg. index.html) AS ARG
        const char *args[] = {python_path, script_path, page, method, NULL};
        std::string qs = "QUERY_STRING=" + (std::string)query_string;
        // std::cout << qs << std::endl;
        char *envp[] = {
            (char *)"REQUEST_METHOD=GET",
            (char *)"CONTENT_TYPE=text/html",
            (char *)qs.c_str(),
            NULL
        };
        execve(python_path, (char* const*)args, envp);
            exit(EXIT_FAILURE);
        }
        else
        {
            // Proces rodzica (odczytanie wyników z potoku)
            close(pipefd[1]);  // Zamykamy zapis w rodzicu

            char buffer[100000];
            ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);
            if (bytesRead > 0)
            {
                buffer[bytesRead] = '\0';
                std::string sta_code = std::string(strstr(buffer, "stat_cod: ") + 10).substr(0, 3);

                // Wysyłanie odpowiedzi CGI do klienta
                std::string http_response;
                if (sta_code != "200")
                {
                    stat_code = sta_code;
                    http_response = "HTTP/1.1 " + sta_code + " Not found\r\n"
                                                "Content-Type: text/html\r\n"
                                                "Content-Length: " + to_string((_errorPage.getErrPage(stoiii(sta_code))).length()) +
                                                "\r\n\r\n" +
                                                _errorPage.getErrPage(stoiii(sta_code));
                }
                else
                {
                    http_response = "HTTP/1.1 " + sta_code + " OK\r\n"
                                                "Content-Type: text/html\r\n"
                                                "Content-Length: " + to_string(bytesRead) + "\r\n"
                                                "Connection: close\r\n\r\n" + std::string(buffer + 14);
                }
                send(new_socket, http_response.c_str(), http_response.size(), 0);
            }
            close(pipefd[0]);
            waitpid(pid, NULL, 0);
        }
    }
    else if (find_file("./src/cgi", file_name, file_path))
    {
        // Obsługa pliku statycznego
        std::ifstream file(file_path.c_str());
        if (file)
        {
            std::stringstream file_stream;
            file_stream << file.rdbuf();
            std::string file_content = file_stream.str();

            // Ustalanie typu MIME
            std::string content_type = "Content-Type: text/html\r\n";
            
            if (file_name.find(".css") != std::string::npos)
                content_type = "Content-Type: text/css\r\n";
            else if (file_name.find(".jpg") != std::string::npos)
                content_type = "Content-Type: image/jpeg\r\n";

            // Wysyłanie odpowiedzi HTTP dla pliku statycznego
            
            std::string http_response = "HTTP/1.1 " + stat_code + " OK\r\n" +
                                        content_type +
                                        "Content-Length: " + to_string(file_content.size()) + "\r\n"
                                        "Connection: close\r\n\r\n" + file_content;
            send(new_socket, http_response.c_str(), http_response.size(), 0);
        }
        else
        {
            // Obsługa błędu 404
            stat_code = "404";
            std::string error_response = "HTTP/1.1 404 Not found\r\n"
                                        "Content-Type: text/html\r\n"
                                        "Content-Length: " + to_string((_errorPage.getErrPage(404)).length()) +  "\r\n"
                                        "\r\n\r\n" +
                                        _errorPage.getErrPage(404);
            // std::cout << error_response << std::endl;
            send(new_socket, error_response.c_str(), error_response.size(), 0);
        }
    }
    else if (find_file("./src/uploads", file_name, file_path))
    {
        // Obsługa pliku statycznego
        std::ifstream file(file_path.c_str());
        if (file)
        {
            std::stringstream file_stream;
            file_stream << file.rdbuf();
            std::string file_content = file_stream.str();

            // Ustalanie typu MIME
            std::string content_type = "Content-Type: text/html\r\n";

            content_type = "Content-Type: application/octet-stream";
            
            if (file_name.find(".css") != std::string::npos)
                content_type = "Content-Type: text/css\r\n";
            else if (file_name.find(".jpg") != std::string::npos)
                content_type = "Content-Type: image/jpeg\r\n";

            // Wysyłanie odpowiedzi HTTP dla pliku statycznego
            
            std::string http_response = "HTTP/1.1 " + stat_code + " OK\r\n" +
                                        content_type +
                                        "Content-Length: " + to_string(file_content.size()) + "\r\n"
                                        "Content-Disposition: attachment; filename=" + file_name + "\r\n"
                                        "Connection: close\r\n\r\n" + file_content;
            send(new_socket, http_response.c_str(), http_response.size(), 0);
        }
        else
        {
            // Obsługa błędu 404
            stat_code = "404";
            std::string error_response = "HTTP/1.1 404 Not foundt\r\n"
                                        "Content-Type: text/html\r\n"
                                        "Content-Length: " + to_string((_errorPage.getErrPage(404)).length()) +  "\r\n"
                                        "\r\n\r\n" +
                                        _errorPage.getErrPage(404);
            // std::cout << error_response << std::endl;
            send(new_socket, error_response.c_str(), error_response.size(), 0);
        }
    }
    else
    {
        // Obsługa błędu 404
        stat_code = "404";
        std::ifstream file("src/cgi/html/404.html");
        std::stringstream file_stream;
        file_stream << file.rdbuf();
        std::string file_content = file_stream.str();
        std::string content_type = "Content-Type: text/html\r\n";
        std::string http_response = "HTTP/1.1 " + stat_code + " Not found\r\n" +
                                    content_type +
                                    "Content-Length: " + to_string(file_content.size()) + "\r\n\r\n"
                                        + file_content;
        send(new_socket, http_response.c_str(), http_response.size(), 0);
    }
    return (0);
}
