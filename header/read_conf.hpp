#ifndef READ_CONF_HPP
#define READ_CONF_HPP

#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
#define CYAN "\033[36m"
#define PURPLE "\033[35m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"

#define MAX_EVENTS 10

#include <iostream>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/wait.h>
#include <netinet/in.h>
#include <dirent.h>
#include <poll.h>
#include <cstring>
#include <sys/epoll.h>
#include "confParsing.hpp"

std::string save_request(int new_socket);
bool find_file(const std::string& dir, const std::string& target, std::string& found_path);


class Read_conf
{
private:
    /*ConfigParser config;
    std::string path; //document root path
    int port;
    size_t size;*/
    ConfigParser config;
    std::string path; //document root path
    int port;
    size_t size;
    std::string cwd;

public:
    Read_conf();
    Read_conf(const std::string &configFile = "/home/bartosz/Projects/WebSer_new/configurations/config.conf");
    ~Read_conf();

    static int get_path_type(std::string const path);
    static int check_File_accessibility(std::string const path, int mode);
    static int check_File_Readability(std::string const path, std::string const index);
    std::string read_File(std::string file_path);

    std::string getPath();
    void setCwd(std::string cwd_path);
    std::string getCwd();
    int getSize();
    int getPort();

    //new method
    bool loadConfig(const std::string &configFile);
    std::string getDocumentRoot();
    enum
    {
    REGULAR_FILE = 1,
    DIRECTORY = 2,
    SYM_LINK = 3,
    CHAR_DEV = 4,
    OTHER = 5
    };
};

#endif
