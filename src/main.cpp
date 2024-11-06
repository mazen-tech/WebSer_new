#include "../header/read_conf.hpp"
#include "../header/server.hpp"

/*int main() {
    // Load the configuration from the config file
    Read_conf config("/mnt/c/Users/miche/OneDrive/Desktop/WebSer_new/configurations/config.conf");
    // Create the server instance and start it
    if (config.loadConfig("/mnt/c/Users/miche/OneDrive/Desktop/WebSer_new/configurations/config.conf")) {
        std::cout << "Loaded configuration successfully!" << std::endl;

        std::cout << "Listening Port in main: " << config.getPort() << std::endl;

        std::cout << "Listening Port: " << config.getPort() << std::endl;
    } 
    else {
        std::cerr << "Failed to load configuration." << std::endl;
    }
    
    if (config.getPort() != 8080) { // error need fixed 
        std::cerr << "Configuration not loaded properly. Exiting...\n";
        return -1;
    }
    Server server(config.getPort());
    server.start();

    return 0;
}*/

int main() {
    // Initialize Read_conf with the config file path
    Read_conf config("/mnt/c/Users/miche/OneDrive/Desktop/WebSer_new/configurations/config.conf");

    // Create the server instance after loading the configuration
    if (config.loadConfig("/mnt/c/Users/miche/OneDrive/Desktop/WebSer_new/configurations/config.conf")) {
        std::cout << "Loaded configuration successfully!" << std::endl;
        
        std::cout << "Listening Port in main: " << config.getPort() << std::endl;
        std::cout << "Document Root: " << config.getDocumentRoot() << std::endl;

    } else {
        std::cerr << "Failed to load configuration." << std::endl;
        return -1;
    }
    
    // Check if port is valid (you can update the validation logic as needed)
    if (config.getPort() == 8080) {
        // Create the Server instance using the loaded port
        Server server(config.getPort());
        server.start();
    } else {
        std::cerr << "Configuration not loaded properly. Exiting...\n";
        return -1;
    }

    return 0;
}