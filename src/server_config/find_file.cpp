/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_file.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkotwica <bkotwica@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 11:59:11 by bkotwica          #+#    #+#             */
/*   Updated: 2024/11/18 11:59:11 by bkotwica         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/read_conf.hpp"

bool find_file(const std::string& dir, const std::string& target, std::string& found_path)
{
    DIR* dp = opendir(dir.c_str());
    if (dp == NULL) return false;

    struct dirent* entry;
    while ((entry = readdir(dp)) != NULL) {
        std::string path = dir + "/" + entry->d_name;

        if (entry->d_type == DT_DIR) {
            // Pomijamy '.' i '..'
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                if (find_file(path, target, found_path)) {
                    closedir(dp);
                    return true;
                }
            }
        } else if (entry->d_type == DT_REG && target == entry->d_name) {
            found_path = path;
            closedir(dp);
            return true;
        }
    }
    closedir(dp);
    return false;
}
