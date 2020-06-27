//
// Created by 张琦 on 2020/6/27.
//

#ifndef OBJECT_SERIALIZATION_XML_SERIALIZATION_H
#define OBJECT_SERIALIZATION_XML_SERIALIZATION_H

#include <iostream>
#include <typeinfo>
#include <string>
#include <list>
#include <map>
#include <set>
#include "tinyxml2.h"

using namespace std;

bool createXML(const string&, const string&); /* Create the basic XML structure for the object of type T. */

bool serialize_xml(int object, const string& name, const string& filename);

bool serialize_xml(float object, const string &name, const string &filename);

bool serialize_xml(double object, const string &name, const string &filename);

bool serialize_xml(const string& object, const string &name, const string &filename);

template <typename T1, typename T2>
bool serialize_xml(pair<T1, T2> object, const string &name, const string &filename);

template <typename T>
bool serialize_xml(vector<T> object, const string &name, const string &filename);

template <typename T>
bool serialize_xml(list<T> object, const string &name, const string &filename);

template <typename T>
bool serialize_xml(set<T> object, const string &name, const string &filename);

template <typename T1, typename T2>
bool serialize_xml(map<T1, T2> object, const string &name, const string &filename);

#endif //OBJECT_SERIALIZATION_XML_SERIALIZATION_H
