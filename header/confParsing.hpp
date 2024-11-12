#ifndef CONFIGPARSER_HPP
#define CONFIGPARSER_HPP

#include <string>
#include <map>
#include <iostream>
#include <vector>

class ConfigParser {
public:
    ConfigParser() = default;
    bool parseConfigFile(const std::string& filepath); // Parses the file and stores the result
    int getPort() const;     // Retrieves the port
    std::string getPath() const; // Retrieves the path (root directory)
    const char* getPythonPath() const;
    const char* getScriptPath() const;

    // void displayConfig() const
    // {
    //     std::map<std::string, std::map<std::string, std::string> >::const_iterator sectionIt;
    //     for (sectionIt = config.begin(); sectionIt != config.end(); ++sectionIt)
    //     {
    //         std::cout << "[" << sectionIt->first << "]" << std::endl;
    //         std::map<std::string, std::string>::const_iterator kvIt;
    //         for (kvIt = sectionIt->second.begin(); kvIt != sectionIt->second.end(); ++kvIt)
    //         {
    //                 std::cout << kvIt->first << kvIt->second << std::endl;
    //         }
    //         std::cout << std::endl;
    //     }
    // }
    void save_redirections(std::vector<std::string>& newlist);
private:
    std::map<std::string, std::map<std::string, std::string>> config;
    int port = 8080;           // Default port
    std::string path = "/default/path";  // Default path
    void parseDirective(const std::string& line, const std::string& context);
    void trim(std::string& str);
    std::string cgi_path;
    std::string cgi_root;
};

#endif // CONFIGPARSER_HPP