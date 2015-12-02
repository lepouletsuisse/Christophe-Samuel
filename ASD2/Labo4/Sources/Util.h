/* 
 * File:   Util.h
 * Author: Olivier Cuisenaire
 * Inspired by: http://stackoverflow.com/a/217605 for triming
 * Created on 26. octobre 2014, 15:26
 */

#ifndef UTIL_H
#define	UTIL_H

#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
std::vector<std::string> split(const std::string &s, char delim);

// trim from start
inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

#endif	/* UTIL_H */

