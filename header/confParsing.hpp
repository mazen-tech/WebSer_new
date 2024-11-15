/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confParsing.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdela <maabdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:45:05 by maabdela          #+#    #+#             */
/*   Updated: 2024/11/13 16:56:05 by maabdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <set>

void checkMultiplePortsDefined(const std::string& filename);
int parseClientMaxBodySize(const std::string& filename);

class ConfigParser {
public:
    ConfigParser() {};
    bool parseConfigFile(const std::string& filepath); // Parses the file and stores the result
    int getPort() const;     // Retrieves the port
    std::string getPath() const; // Retrieves the path (root directory)
    const char* getPythonPath() const;
    const char* getScriptPath() const;
    void save_redirections(std::vector<std::string>& newlist);
private:
    std::map<std::string, std::map<std::string, std::string> > config;
    int port;           // Default port
    std::string path;  // Default path
    void parseDirective(const std::string& line, const std::string& context);
    void trim(std::string& str);
    std::string cgi_path;
    std::string cgi_root;
};

#endif // CONFIGPARSER_HPP
