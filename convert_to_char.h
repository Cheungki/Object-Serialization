//
// Created by 张琦 on 2020/6/28.
//

#ifndef OBJECT_SERIALIZATION_CONVERT_TO_CHAR_H
#define OBJECT_SERIALIZATION_CONVERT_TO_CHAR_H

#include <iostream>
#include <typeinfo>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <cxxabi.h>

using namespace std;

template <typename T>
string getType(T object)
{
    string type = abi::__cxa_demangle(typeid(object).name(), nullptr, nullptr, nullptr);
    if(is_arithmetic<T>::value || type.find(':') == string::npos) return type;
    else {
        int pos = type.find('<');
        type = type.substr(10, pos - 10);
        return type;
    }
}

const char *convert(int);

const char *convert(float);

const char *convert(double);

const char *convert(char);

const char *convert(bool);

const char *convert(const string&);

template <typename T1, typename T2>
const char *convert(pair<T1, T2>)
{
    return "";
}

template <typename T>
const char *convert(vector<T>)
{
    return "";
}

template <typename T>
const char *convert(list<T>)
{
    return "";
}

template <typename T>
const char *convert(set<T>)
{
    return "";
}

template <typename T1, typename T2>
const char *convert(map<T1, T2>)
{
    return "";
}

#endif //OBJECT_SERIALIZATION_CONVERT_TO_CHAR_H
