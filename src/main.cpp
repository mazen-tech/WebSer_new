#include "../header/read_conf.hpp"
#include "../header/server.hpp"
#include "../header/confParsing.hpp"

/*int main() {

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
    
    if (config.getPort() == 8080) {
        Server server(config.getPort());
        server.config = &config;
        server.start();
    } else {
        std::cerr << "Configuration not loaded properly(port is not allowed). Exiting...\n";
        return -1;
    }

    return 0;
}*/



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
    if (config.loadConfig(path.c_str())) 
    {
        ConfigParser test;
        std::cout << "Loaded configuration successfully!" << std::endl;
        std::cout << "Listening Port in main: " << config.getPort() << std::endl;
        std::cout << "Document Root: " << config.getDocumentRoot() << std::endl;

    } else {
        std::cerr << "Failed to load configuration." << std::endl;
        return -1;
    }
    if (config.getPort() == 8080) 
    {
        Server server(config.getPort());
        server.config = &config;
        config.config.save_redirections(server.red);
        server.start();
    } else {
        std::cerr << "Configuration not loaded properly(port is not allowed). Exiting...\n";
        return -1;
    }

    return 0;
}