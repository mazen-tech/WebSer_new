/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confParsing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdela <maabdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:45:05 by maabdela          #+#    #+#             */
/*   Updated: 2024/11/13 16:56:05 by maabdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../header/confParsing.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <set>

int parseClientMaxBodySize(const std::string& filename) {
    std::ifstream confFile(filename.c_str());
    if (!confFile.is_open()) {
    throw std::runtime_error("Error: Unable to open configuration file.");
    }

    std::string line;
    int clientMaxBodySize = -1;

    while (std::getline(confFile, line)) {
        std::istringstream iss(line);
        std::string key;
        
        if (line.find("client_max_body_size") != std::string::npos) {
            iss >> key;
            if (key == "client_max_body_size") {
                int value;
                iss >> value;
                clientMaxBodySize = value;
                break;
            }
        }
    }

    confFile.close();

    if (clientMaxBodySize == -1) {
        throw std::runtime_error("Error: client_max_body_size not defined in the configuration file.");
    }

    return clientMaxBodySize;
}   


void checkMultiplePortsDefined(const std::string& filename) {
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open configuration file." << std::endl;
        return;
    }

    std::string line;
    std::set<int> ports;
    bool errorFlag = false;

    while (std::getline(file, line)) {
        // Check if the line contains the "listen" directive
        if (line.find("listen") != std::string::npos) {
            std::istringstream iss(line);
            std::string token;
            bool listenFound = false;

            // Parse the line
            while (iss >> token) {
                // After finding "listen", get the following port numbers
                if (token == "listen") {
                    listenFound = true;
                    continue;
                }
                
                // If "listen" was found, process the ports
                if (listenFound) {
                    int port;
                    std::istringstream portStream(token);
                    while (portStream >> port) {
                        // Check if port already exists
                        if (ports.find(port) != ports.end()) {
                            std::cerr << "Error: Multiple ports are defined." << std::endl;
                            errorFlag = true;
                            break;
                        } else {
                            ports.insert(port);
                        }
                    }
                    if (errorFlag) break;
                }
            }
        }
    }

    if (!errorFlag) {
        std::cout << "Configuration check passed: No duplicate ports found." << std::endl;
    }

    file.close();
}

bool ConfigParser::parseConfigFile(const std::string& filepath) {
    port = 8080;
    path = "/default/path";
    std::ifstream file(filepath.c_str());
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return false;
    }

    std::string line;
    std::string currentLocation;
    bool portDefined = false;  // Track if the port is already defined

    while (std::getline(file, line)) {
        trim(line);

        // Skip comments and empty lines
        if (line.empty() || line[0] == '#') continue;

        // Check for server block
        if (line.find("server {") != std::string::npos) {
            currentLocation.clear();
            continue;
        }

        // Check for location block
        size_t locationPos = line.find("location");
        if (locationPos != std::string::npos) {
            size_t start = line.find_first_not_of(" \t", locationPos + 8);
            size_t end = line.find_first_of(" \t{", start);
            if (start != std::string::npos && end != std::string::npos) {
                currentLocation = line.substr(start, end - start);
                continue;
            }
        }

        // Parse configuration directives
        if (!currentLocation.empty()) {
            parseDirective(line, currentLocation);
        } else {
            parseDirective(line, "global");
        }

        // Check for listen directive and multiple port definitions
        if (line.find("listen") != std::string::npos) {
            size_t start = line.find_first_not_of(" \t", line.find("listen") + 6);
            size_t end = line.find_first_of(" \t;", start);
            if (start != std::string::npos && end != std::string::npos) {
                if (portDefined) {
                    std::cerr << "Error: Port is defined multiple times!" << std::endl;
                    return false;  // Return false to indicate an error
                }
                portDefined = true;  // Mark port as defined
            }
        }
    }

    file.close();

    // Extract needed data (port and path)
    if (config["global"].count("listen") > 0) {
        port = std::atoi(config["global"]["listen"].c_str());
    }
    if (config["global"].count("root") > 0) {
        path = config["global"]["root"];
    }

    return true;
}

void ConfigParser::parseDirective(const std::string& line, const std::string& context) {
    size_t start = line.find_first_not_of(" \t");
    size_t end = line.find_first_of(" \t", start);
    if (start != std::string::npos && end != std::string::npos) {
        std::string key = line.substr(start, end - start);
        start = line.find_first_not_of(" \t", end);
        end = line.find_first_of(";", start);
        if (start != std::string::npos && end != std::string::npos) {
            std::string value = line.substr(start, end - start);
            config[context][key] = value;
        }
    }
}

bool isNotSpace(unsigned char ch) {
    return !std::isspace(ch);
}

void ConfigParser::trim(std::string& str) {
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), isNotSpace));
    str.erase(std::find_if(str.rbegin(), str.rend(), isNotSpace).base(), str.end());
}

int ConfigParser::getPort() const {
    return port;
}

std::string ConfigParser::getPath() const {
    return path;
}

void ConfigParser::save_redirections(std::vector<std::string>& newlist) {
    std::map<std::string, std::map<std::string, std::string> >::const_iterator sectionIt;
    for (sectionIt = config.begin(); sectionIt != config.end(); ++sectionIt) {
        std::map<std::string, std::string>::const_iterator kvIt;
        for (kvIt = sectionIt->second.begin(); kvIt != sectionIt->second.end(); ++kvIt) {
            if (kvIt->first == "return") {
                newlist.push_back(sectionIt->first + " " + kvIt->second);
            }
        }
    }
}

const char* ConfigParser::getPythonPath() const {
    ConfigParser configParser;
    const char *path = "/usr/bin/python3";
    if (!configParser.parseConfigFile("/nfs/homes/bkotwica/WebSer_new/configurations/config.conf")) {
        std::cerr << "Failed to load configuration file" << std::endl;
        return NULL;
    }
    return path;
}

const char* ConfigParser::getScriptPath() const {
    ConfigParser configParser;
    const char *path = "./src/cgi/mycgi.py";
    if (!configParser.parseConfigFile("/nfs/homes/bkotwica/WebSer_new/configurations/config.conf")) {
        std::cerr << "Failed to load configuration file" << std::endl;
        return NULL;
    }
    return path;
}
