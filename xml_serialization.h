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

bool createXML(const string&); /* Create the basic XML structure for the object of type T. */

template <typename T>
bool serialize_xml(T object, const string& name, const string& filename)
{
    if(!createXML(filename)) {
        tinyxml2::XMLDocument doc;
        bool isNotLoaded = doc.LoadFile(filename.c_str());
        if(isNotLoaded) {
            cout << "Failed to load XML file." << endl;
            return false;
        }
        else {
            tinyxml2::XMLElement* root = doc.RootElement();
            tinyxml2::XMLElement* node = doc.NewElement(name.c_str());
            tinyxml2::XMLElement* subnode;
            if(typeid(T) == typeid(int)) {
                subnode = doc.NewElement("int");
                subnode->InsertEndChild(doc.NewText(to_string(object).c_str()));
            }
            else if(typeid(T) == typeid(float)) {
                subnode = doc.NewElement("float");
                subnode->InsertEndChild(doc.NewText(to_string(object).c_str()));
            }
            else if(typeid(T) == typeid(double)) {
                subnode = doc.NewElement("double");
                subnode->InsertEndChild(doc.NewText(to_string(object).c_str()));
            }
            else if(typeid(T) == typeid(char)) {
                subnode = doc.NewElement("char");
                subnode->InsertEndChild(doc.NewText(object));
            }
            else if(typeid(T) == typeid(string)) {
                subnode = doc.NewElement("string");
                subnode->InsertEndChild(doc.NewText(object));
            }
            node->InsertEndChild(subnode);
            root->InsertEndChild(node);
        }
        return doc.SaveFile(filename.c_str());
    }
    else {
        cout << "Failed to create XML document." << endl;
        return false;
    }
}

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
