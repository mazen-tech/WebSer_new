#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <string>
#include <map>

class ConfigParser {
public:
    ConfigParser() = default;
    bool parseConfigFile(const std::string& filepath); // Parses the file and stores the result
    int getPort() const;     // Retrieves the port
    std::string getPath() const; // Retrieves the path (root directory)

private:
    std::map<std::string, std::map<std::string, std::string>> config;
    int port = 8080;           // Default port
    std::string path = "/default/path";  // Default path
    void parseDirective(const std::string& line, const std::string& context);
    void trim(std::string& str);
};

#endif // CONFIGPARSER_HPP
