#pragma once 

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <regex>

/*class confParsing
{
private:
    std::map<std::string, std::string> configSittings;

public:
    confParsing() = default;
    bool loadConfigFile(const std::string &configFile);
    bool hasSitting(const std::string &key) const;
    std::string getSetting(const std::string &key) const;
};

*/
class confParsing {
public:
    int listen = 0;
    std::string server_name;
    std::string host;
    std::string root;
    int client_max_body_size = 0;
    std::string index;
    std::string error_page;
    std::map<std::string, std::vector<std::string>> locations;

    void display() const;
};

bool parseConfigFile(const std::string& filename, confParsing& config);