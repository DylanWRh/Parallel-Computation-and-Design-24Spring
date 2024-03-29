#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>

namespace StringUtils {
    std::string s_to_lower(const std::string& s);
    void trim(std::string &s);
    int compare_str(const std::string& s1, const std::string& s2);
}

#endif