#pragma once

#include <string>
#include <unordered_map>

class ErrorPage
{
public:
    ErrorPage();
    std::string getErrPage(int statusCode);

private:
    std::unordered_map<int, std::string> errorPages;
    void initErrMsg(); // load HTML templetes for error pages 
};
