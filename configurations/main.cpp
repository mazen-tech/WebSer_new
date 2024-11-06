#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <regex>

class ConfigParser {
public:
    void parse(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filepath << std::endl;
            return;
        }

        std::string line;
        std::string currentLocation;
        while (std::getline(file, line)) {
            // Trim whitespace from the line
            trim(line);

            // Skip comments and empty lines
            if (line.empty() || line[0] == '#') continue;

            // Check for server block
            if (line.find("server {") != std::string::npos) {
                currentLocation.clear();
                continue;
            }

            // Check for location block (fix: escape curly braces)
            std::smatch match;
            if (std::regex_search(line, match, std::regex(R"(location\s+(\S+)\s*\{)"))) {
                currentLocation = match[1];
                continue;
            }

            // Parse configuration directives
            if (!currentLocation.empty()) {
                parseDirective(line, currentLocation);
            } else {
                parseDirective(line, "global");
            }
        }

        file.close();
    }

    void printConfig() const {
        for (const auto& entry : config) {
            std::cout << entry.first << ":\n";
            for (const auto& value : entry.second) {
                std::cout << "  " << value.first << ": " << value.second << "\n";
            }
        }
    }

private:
    std::map<std::string, std::map<std::string, std::string>> config;

    void parseDirective(const std::string& line, const std::string& context) {
        std::smatch match;
        // Update regex to avoid errors in the brace expression
        if (std::regex_search(line, match, std::regex(R"(\s*(\S+)\s+(.+);)"))) {
            std::string key = match[1];
            std::string value = match[2];
            config[context][key] = value;
        }
    }

    void trim(std::string& str) {
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), str.end());
    }
};

int main() {
    ConfigParser parser;
    parser.parse("config.conf");  // Update with the actual path
    parser.printConfig();
    return 0;
}
