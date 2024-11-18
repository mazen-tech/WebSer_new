/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:00:13 by bkotwica          #+#    #+#             */
/*   Updated: 2024/11/18 12:00:18 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

