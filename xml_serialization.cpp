//
// Created by 张琦 on 2020/6/27.
//

#include "xml_serialization.h"

using namespace std;

template <typename T>
bool createXML(const string &filename, T object) /* Create the basic XML structure for the object of type T. */
{
    tinyxml2::XMLDocument doc;
    string declaration = R"(<?xml version="1.0" encoding="UTF-8" standalone="no"?>)";
    doc.Parse(declaration.c_str());
    tinyxml2::XMLElement* root = doc.NewElement(typeid(object).name());
    doc.InsertEndChild(root);
    return doc.SaveFile(filename.c_str());
}

void serialize_xml(int object, const string &name, const string &filename)
{

}

void serialize_xml(float object, const string &name, const string &filename)
{

}

void serialize_xml(double object, const string &name, const string &filename)
{

}

void serialize_xml(string object, const string &name, const string &filename)
{

}

template <typename T1, typename T2>
void serialize_xml(pair<T1, T2> object, const string &name, const string &filename)
{

}

template <typename T>
void serialize_xml(vector<T> object, const string &name, const string &filename)
{

}

template <typename T>
void serialize_xml(list<T> object, const string &name, const string &filename)
{

}

template <typename T>
void serialize_xml(set<T> object, const string &name, const string &filename)
{

}

template <typename T1, typename T2>
void serialize_xml(map<T1, T2> object, const string &name, const string &filename)
{

}