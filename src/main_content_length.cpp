#include "../header/read_conf.hpp"
#include "../header/Main_SerConfig.hpp"
#include "../header/server.hpp"

int main() {
    // Load the configuration from the config file
    Read_conf config("/mnt/c/Users/miche/OneDrive/Desktop/WebSer_new/configurations/config.conf");
    /*if (config.getPort() != 8080) { // error need fixed 
        std::cerr << "Configuration not loaded properly. Exiting...\n";
        return -1;
    }
    
    std::cout << "Document Root: " << config.getPath() << std::endl;
    std::cout << "Port: " << config.getPort() << std::endl;
    // Create the server instance and start it*/
    if (config.loadConfig("/mnt/c/Users/miche/OneDrive/Desktop/WebSer_new/configurations/config.conf")) {
        std::cout << "Loaded configuration successfully!" << std::endl;
        std::cout << "Document Root: " << config.getDocumentRoot() << std::endl;
        std::cout << "Port: " << config.getPort() << std::endl;
    } else {
        std::cerr << "Failed to load configuration." << std::endl;
    }
    Server server(config.getPort());
    server.start();

    return 0;
}