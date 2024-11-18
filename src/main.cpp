/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdela <maabdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:45:05 by maabdela          #+#    #+#             */
/*   Updated: 2024/11/13 16:56:05 by maabdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../header/read_conf.hpp"
#include "../header/server.hpp"
#include "../header/confParsing.hpp"


int main(int argc, char **argv) {

    if (argc < 2) 
    {
        std::cerr << RED << "Error: Configuration file not specified." << RESET << std::endl;
        return 1;
    }


    char buffer[PATH_MAX];
    if (getcwd(buffer, PATH_MAX)) 
    {
        std::cout << "Current working directory: " << buffer << std::endl;
    } 
    else {
        std::cerr << "Error getting current working directory" << std::endl;
        return 1;
    }

    std::string path = std::string(buffer) + "/configurations/" + argv[1];
    std::ifstream configFile(path.c_str());
    if (!configFile) 
    {
        std::cerr << RED << "Error: Configuration file \"" << path << "\" does not exist." << RESET << std::endl;
        return 1;
    }
    configFile.close();


    Read_conf config(path.c_str());
    config.setCwd(buffer);
    checkMultiplePortsDefined(path);
    if (config.loadConfig(path.c_str())) 
    {
        std::cout << "Loaded configuration successfully!" << std::endl;
        std::cout << "Listening Port in main: " << config.getPort() << std::endl;
    } 
    else 
    {
        std::cerr << "Failed to load configuration." << std::endl;
        return -1;
    }


    if (config.getPort() == 8080) 
    {
        Server server(config.getPort());
        server.config = &config;
        config.config.save_redirections(server.red);
        server.start();
    } 
    else 
    {
        std::cerr << "Configuration not loaded properly(port is not allowed). Exiting...\n";
        return -1;
    }

    return 0;
}
