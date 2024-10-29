#include "../header/read_conf.hpp"
#include "../header/Main_SerConfig.hpp"
#include "../header/server.hpp"

int main() {
    // Load the configuration from the config file
    Read_conf config("/mnt/c/Users/miche/OneDrive/Desktop/cpp/webtest/WebServ/configurations/config.conf");
    if (config.getPort() != 8080) { // error need fixed 
        std::cerr << "Configuration not loaded properly. Exiting...\n";
        return -1;
    }

    // Create the server instance and start it
    Server server(config.getPort());
    server.start();

    return 0;
}