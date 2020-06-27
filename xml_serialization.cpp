//
// Created by 张琦 on 2020/6/27.
//

#include "xml_serialization.h"

using namespace std;

bool serialize_xml(int object, const string& name, const string& filename)
{
    if(!createXML(filename, name)) {
        tinyxml2::XMLDocument doc;
        bool isNotLoaded = doc.LoadFile(filename.c_str());
        if(isNotLoaded) {
            cout << "Failed to load XML file." << endl;
            return false;
        }
        else {
            tinyxml2::XMLElement* root = doc.RootElement();
            tinyxml2::XMLElement* node = doc.NewElement(name.c_str());
            node->SetAttribute("INT", object);
            root->InsertEndChild(node);
        }
        return doc.SaveFile(filename.c_str());
    }
    else {
        cout << "Failed to create XML document." << endl;
        return false;
    }
}

bool serialize_xml(float object, const string &name, const string &filename)
{
    if(!createXML(filename, name)) {
        tinyxml2::XMLDocument doc;
        bool isNotLoaded = doc.LoadFile(filename.c_str());
        if(isNotLoaded) {
            cout << "Failed to load XML file." << endl;
            return false;
        }
        else {
            tinyxml2::XMLElement* root = doc.RootElement();
            tinyxml2::XMLElement* node = doc.NewElement(name.c_str());
            node->SetAttribute("FLOAT", object);
            root->InsertEndChild(node);
        }
        return doc.SaveFile(filename.c_str());
    }
    else {
        cout << "Failed to create XML document." << endl;
        return false;
    }
}

bool serialize_xml(double object, const string &name, const string &filename)
{
    if(!createXML(filename, name)) {
        tinyxml2::XMLDocument doc;
        bool isNotLoaded = doc.LoadFile(filename.c_str());
        if(isNotLoaded) {
            cout << "Failed to load XML file." << endl;
            return false;
        }
        else {
            tinyxml2::XMLElement* root = doc.RootElement();
            tinyxml2::XMLElement* node = doc.NewElement(name.c_str());
            node->SetAttribute("DOUBLE", object);
            root->InsertEndChild(node);
        }
        return doc.SaveFile(filename.c_str());
    }
    else {
        cout << "Failed to create XML document." << endl;
        return false;
    }
}

bool serialize_xml(const string& object, const string &name, const string &filename)
{

}

template <typename T1, typename T2>
bool serialize_xml(pair<T1, T2> object, const string &name, const string &filename)
{

}

template <typename T>
bool serialize_xml(vector<T> object, const string &name, const string &filename)
{

}

template <typename T>
bool serialize_xml(list<T> object, const string &name, const string &filename)
{

}

template <typename T>
bool serialize_xml(set<T> object, const string &name, const string &filename)
{

}

template <typename T1, typename T2>
bool serialize_xml(map<T1, T2> object, const string &name, const string &filename)
{

}

bool createXML(const string& filename, const string& name) /* Create the basic XML structure for the object of type T. */
{
    tinyxml2::XMLDocument doc;
    string declaration = R"(<?xml version="1.0" encoding="UTF-8" standalone="no"?>)";
    doc.Parse(declaration.c_str());
    tinyxml2::XMLElement* root = doc.NewElement(name.c_str());
    doc.InsertEndChild(root);
    return doc.SaveFile(filename.c_str());
}