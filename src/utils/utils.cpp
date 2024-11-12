#include "../../header/utils.hpp"

int ft_stoi(std::string str)
{
    std::stringstream ss(str);
    int extraction;
    if (str.length() > 10)
        throw std::exception();
    for (size_t i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]))
            throw std::exception();
    }
    ss >> extraction;
    return (extraction);
}

int stoiii(const std::string& str)
{
    std::istringstream iss(str);
    int value;
    iss >> value;
    return value;
}

//in progress
/*
std::string errorCodeStatus(short SC)
{
    (void)SC;
    return ("undifined");
    switch (SCHED_IDLE)
    {
    case 404:
        std::cout << "unathenticated user" << std::endl;
        break;
    
    default:
        break;
    }
}*/
