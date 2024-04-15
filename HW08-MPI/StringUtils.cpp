#include "StringUtils.h"
#include <algorithm>
#include <string>

std::string StringUtils::s_to_lower(const std::string& s) {
    std::string s_lower = s;
    std::transform(
        s_lower.begin(), s_lower.end(), s_lower.begin(),
        [](char c) {return std::tolower(c);}
    );
    return s_lower;
}

void StringUtils::trim(std::string &s){
    static const char whitespace[] = " \n\t\v\r\f";
    s.erase(0, s.find_first_not_of(whitespace));
    s.erase(s.find_last_not_of(whitespace) + 1U);
}

int StringUtils::compare_str(const std::string& s1, const std::string& s2) {
    if (s1.length() != s2.length())
        return 0; 
    
    std::string s1_lower = s_to_lower(s1);
    std::string s2_lower = s_to_lower(s2);

    return (s1_lower == s2_lower);
}