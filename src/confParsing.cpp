#include "../header/confParsing.hpp"

/*bool confParsing::loadConfigFile(const std::string &configFile)
{
    std::ifstream file(configFile);
    if (!file.is_open())
    {
        std::cerr << "Error: configuration pasring: can't open file " << configFile << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string key;
        std::string value;

        if (std::getline(iss, key, '=') && std::getline(iss, value))
        {
            //triming the spaces 
            key.erase(0, key.find_first_not_of(" /t "));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            configSittings[key] = value;
        }
    }
    file.close();
    return true;
}

bool confParsing::hasSitting(const std::string &key) const
{
    return configSittings.find(key) != configSittings.end();
}

std::string confParsing::getSetting(const std::string &key) const 
{
    auto it = configSittings.find(key);
    return (it != configSittings.end()) ? it->second : "";
}*/

bool parseConfigFile(const std::string& filename, confParsing& config) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    std::regex key_value_regex(R"(\s*(\w+)\s+(.*);)");

    while (std::getline(file, line)) {
        // Ignore comments and empty lines
        if (line.empty() || line[0] == '#') continue;

        // Check for the start of server block
        if (line.find("server {") != std::string::npos) {
            continue; // Start of server block
        }
        else if (line.find("location") != std::string::npos) {
            std::string location_name = line.substr(line.find_first_of(" ") + 1);
            location_name = location_name.substr(0, location_name.find_first_of(" {"));
            std::vector<std::string> methods;

            while (std::getline(file, line) && line.find("}") == std::string::npos) {
                if (line.empty() || line[0] == '#') continue;

                std::smatch match;
                if (std::regex_match(line, match, key_value_regex)) {
                    std::string key = match[1].str();
                    std::string value = match[2].str();
                    if (key == "allow_methods") {
                        std::istringstream iss(value);
                        std::string method;
                        while (iss >> method) {
                            methods.push_back(method);
                        }
                    }
                    // You can add more parsing logic here for other location configurations.
                }
            }
            config.locations[location_name] = methods;
        } else {
            std::smatch match;
            if (std::regex_match(line, match, key_value_regex)) {
                std::string key = match[1].str();
                std::string value = match[2].str();

                if (key == "listen") {
                    config.listen = std::stoi(value);
                } else if (key == "server_name") {
                    config.server_name = value;
                } else if (key == "host") {
                    config.host = value;
                } else if (key == "root") {
                    config.root = value;
                } else if (key == "client_max_body_size") {
                    config.client_max_body_size = std::stoi(value);
                } else if (key == "index") {
                    config.index = value;
                } else if (key == "error_page") {
                    config.error_page = value;
                }
            }
        }
    }

    file.close();
    return true;
}

void confParsing::display() const {
        std::cout << "Server Configuration:" << std::endl;
        std::cout << "Listen: " << listen << std::endl;
        std::cout << "Server Name: " << server_name << std::endl;
        std::cout << "Host: " << host << std::endl;
        std::cout << "Root: " << root << std::endl;
        std::cout << "Client Max Body Size: " << client_max_body_size << std::endl;
        std::cout << "Index: " << index << std::endl;
        std::cout << "Error Page: " << error_page << std::endl;
        
        for (const auto& location : locations) {
            std::cout << "Location: " << location.first << std::endl;
            for (const auto& method : location.second) {
                std::cout << "  Method: " << method << std::endl;
            }
        }
    }

