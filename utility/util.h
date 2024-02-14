#ifndef UTLITY_UTIL_HEADER
#define UTLITY_UTIL_HEADER

#include<string>
#include<vector>
#include<sstream>

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

std::string trim(const std::string& str) {
    size_t start = 0;
    size_t end = str.length()-1;

    auto isTrim = [](char c) {
        if ( isspace(c) ) return true;
        if ( c == '\n' ) return true;
        return false;
    };

    while ( start <= end && isTrim(str[start]) ) {
        start++;
    }

    while ( end >= start && isTrim(str[end]) ) {
        end--;
    }

    return str.substr(start, end-start+1);
}

void removeItemFast(std::vector<int>& vec, int index) {
    vec[index] = vec[vec.size()-1];
    vec.pop_back();
}

#endif