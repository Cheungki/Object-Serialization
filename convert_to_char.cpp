//
// Created by 张琦 on 2020/6/28.
//

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
    string value = to_string(object);
    char *result = new char[value.length()];
    strcpy(result, value.c_str());
    return result;
}

const char *convert(double object)
{
    string value = to_string(object);
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

const char *convert(const string& object)
{
    char *result = new char[object.length()];
    strcpy(result, object.c_str());
    return result;
}
