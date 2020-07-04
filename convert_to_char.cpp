//
// Created by 张琦 on 2020/6/28.
//

#include <sstream>
#include <iomanip>
#include "convert_to_char.h"

const char *convert(int object)
{
    string value = to_string(object);
    char *result = new char[value.length()];
    strcpy(result, value.c_str());
    return result;
}

const char *convert(float object)
{
    std::ostringstream ss;
    ss << std::setprecision(7) << object;
    string value = ss.str();
    char *result = new char[value.length()];
    strcpy(result, value.c_str());
    return result;
}

const char *convert(double object)
{
    std::ostringstream ss;
    ss << std::setprecision(16) << object;
    string value = ss.str();
    char *result = new char[value.length()];
    strcpy(result, value.c_str());
    return result;
}

const char *convert(char object)
{
    char *result = new char[2];
    result[0] = object;
    result[1] = '\0';
    return result;
}

const char *convert(bool object)
{
    if(object) return "true";
    else return "false";
}

const char *convert(const string& object)
{
    char *result = new char[object.length()];
    strcpy(result, object.c_str());
    return result;
}
