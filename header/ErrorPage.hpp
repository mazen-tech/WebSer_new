#pragma once

#include <string>
#include <map>

class ErrorPage
{
public:
    ErrorPage();
    std::string getErrPage(int statusCode);

private:
    std::map<int, std::string> errorPages;
    void initErrMsg(); // load HTML templetes for error pages 
};
