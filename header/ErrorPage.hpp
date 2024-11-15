/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ErrorPage.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maabdela <maabdela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 23:45:05 by maabdela          #+#    #+#             */
/*   Updated: 2024/11/13 16:56:05 by maabdela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
