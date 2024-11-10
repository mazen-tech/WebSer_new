#include "../header/read_conf.hpp"
#include "../header/server.hpp"

int main() {

    char buffer[PATH_MAX];
    if (getcwd(buffer, PATH_MAX)) {
        std::cout << "Current working directory: " << buffer << std::endl;
    } else {
        std::cerr << "Error getting current working directory" << std::endl;
        return 1;
    }
    std::string path = std::string(buffer) + std::string("/configurations/config.conf");

    Read_conf config(path.c_str());
    config.setCwd(buffer);

    if (config.loadConfig(path.c_str())) {
        std::cout << "Loaded configuration successfully!" << std::endl;
        
        std::cout << "Listening Port in main: " << config.getPort() << std::endl;
        std::cout << "Document Root: " << config.getDocumentRoot() << std::endl;

    } else {
        std::cerr << "Failed to load configuration." << std::endl;
        return -1;
    }
    
    // Check if port is valid (you can update the validation logic as needed)
    if (config.getPort() == 8080) {
        Server server(config.getPort());
        server.config = &config;
        server.start();
    } else {
        std::cerr << "Configuration not loaded properly. Exiting...\n";
        return -1;
    }

    return 0;
}
