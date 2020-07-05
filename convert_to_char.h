//
// Created by 张琦 on 2020/6/28.
//

#ifndef OBJECT_SERIALIZATION_CONVERT_TO_CHAR_H
#define OBJECT_SERIALIZATION_CONVERT_TO_CHAR_H

#include <iostream>
#include <typeinfo>
#include <string>
#include <string.h>
#include <vector>
#include <list>
#include <set>
#include <map>

using namespace std;

string getType(int object);

string getType(float object);

string getType(double object);

string getType(char object);

string getType(bool object);

string getType(string object);

template <typename T1, typename T2>
string getType(pair<T1, T2> object)
{
    return "pair";
}

template <typename T>
string getType(vector<T> object)
{
    return "vector";
}

template <typename T>
string getType(list<T> object)
{
    return "list";
}

template <typename T>
string getType(set<T> object)
{
    return "set";
}

template <typename T1, typename T2>
string getType(map<T1, T2> object)
{
    return "map";
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
