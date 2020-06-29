//
// Created by 张琦 on 2020/6/27.
//

#ifndef OBJECT_SERIALIZATION_XML_SERIALIZATION_H
#define OBJECT_SERIALIZATION_XML_SERIALIZATION_H

#include <iostream>
#include <typeinfo>
#include <string>
#include <list>
#include <set>
#include <map>
#include <fstream>
#include "convert_to_char.h"
#include "tinyxml2.h"

using namespace std;

class document {
public:
    static bool createXML(const string &); /* Create the basic XML structure for the object of type T. */

    template<typename T>
    bool isSTL(T object)
    {
        string type = getType(object);
        return !(type == "int" || type == "float" || type == "double" || type == "char" || type == "string");
    }

    template<typename T>
    void InsertNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node) {
        tinyxml2::XMLElement *subnode;
        subnode = doc.NewElement(getType(object).c_str());
        subnode->SetAttribute("val", convert(object));
        node->InsertEndChild(subnode);
    }

    template<typename T>
    void InsertSTLNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node) {
        InsertSTLNode<T>(object, doc, node);
    }

    template<typename T1, typename T2>
    void InsertSTLNode(pair<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node) {
        tinyxml2::XMLElement *subnode_1 = doc.NewElement("first");
        tinyxml2::XMLElement *subnode_2 = doc.NewElement("second");
        if (!is_arithmetic<T1>::value && getType(object.first) != "basic_string")
            InsertSTLNode(object.first, doc, subnode_1);
        else subnode_1->SetAttribute("val", convert(object.first));
        if (!is_arithmetic<T2>::value && getType(object.second) != "basic_string")
            InsertSTLNode(object.second, doc, subnode_2);
        else subnode_2->SetAttribute("val", convert(object.second));
        node->InsertEndChild(subnode_1);
        node->InsertEndChild(subnode_2);
    }

    template<typename T>
    void InsertSTLNode(vector<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node) {
        int i = 0;
        for (typename vector<T>::const_iterator iter = object.begin(); iter != object.end(); iter++) {
            string tag = getType(*iter) + "_" + to_string(i);
            tinyxml2::XMLElement *subnode = doc.NewElement(tag.c_str());
            if (isSTL(*iter)) InsertSTLNode(*iter, doc, subnode);
            else subnode->SetAttribute("val", convert(*iter));
            node->InsertEndChild(subnode);
            i++;
        }
    }

    template<typename T>
    void InsertSTLNode(list<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node) {
        int i = 0;
        for (typename list<T>::const_iterator iter = object.begin(); iter != object.end(); iter++) {
            string tag = getType(*iter) + "_" + to_string(i);
            tinyxml2::XMLElement *subnode = doc.NewElement(tag.c_str());
            if (isSTL(*iter)) InsertNode(*iter, doc, subnode);
            else subnode->SetAttribute("val", convert(*iter));
            node->InsertEndChild(subnode);
            i++;
        }
    }

    template<typename T>
    void InsertSTLNode(set<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node) {
        int i = 0;
        for (typename set<T>::const_iterator iter = object.begin(); iter != object.end(); iter++) {
            string tag = getType(*iter) + "_" + to_string(i);
            tinyxml2::XMLElement *subnode = doc.NewElement(tag.c_str());
            if (isSTL(*iter)) InsertNode(*iter, doc, subnode);
            else subnode->SetAttribute("val", convert(*iter));
            node->InsertEndChild(subnode);
            i++;
        }
    }

    template<typename T1, typename T2>
    void InsertSTLNode(map<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node) {
        int i = 0;
        for (typename map<T1, T2>::const_iterator iter = object.begin(); iter != object.end(); iter++) {
            string tag = getType(*iter) + "_" + to_string(i);
            tinyxml2::XMLElement *subnode_1 = doc.NewElement("key");
            tinyxml2::XMLElement *subnode_2 = doc.NewElement("value");
            if (!is_arithmetic<T1>::value && getType(iter->first) != "basic_string")
                InsertSTLNode(iter->first, doc, subnode_1);
            else subnode_1->SetAttribute("val", convert(iter->first));
            if (!is_arithmetic<T2>::value && getType(iter->second) != "basic_string")
                InsertSTLNode(iter->second, doc, subnode_2);
            else subnode_2->SetAttribute("val", convert(iter->second));
            node->InsertEndChild(subnode_1);
            node->InsertEndChild(subnode_2);
            i++;
        }
    }

    template<typename T>
    bool serialize_xml(T object, const string &name, const string &filename) {
        ifstream fin(filename.c_str());
        if (!fin && createXML(filename)) {
            cout << "Failed to create XML document." << endl;
            return false;
        }
        tinyxml2::XMLDocument doc;
        bool isNotLoaded = doc.LoadFile(filename.c_str());
        if (isNotLoaded) {
            cout << "Failed to load XML file." << endl;
            return false;
        } else {
            tinyxml2::XMLElement *root = doc.RootElement();
            tinyxml2::XMLElement *node = doc.NewElement(name.c_str());
            InsertNode(object, doc, node);
            root->InsertEndChild(node);
        }
        return doc.SaveFile(filename.c_str());
    }

    template<typename T1, typename T2>
    bool serialize_xml(pair<T1, T2> object, const string &name, const string &filename) {
        ifstream fin(filename.c_str());
        if (!fin && createXML(filename)) {
            cout << "Failed to create XML document." << endl;
            return false;
        }
        tinyxml2::XMLDocument doc;
        bool isNotLoaded = doc.LoadFile(filename.c_str());
        if (isNotLoaded) {
            cout << "Failed to load XML file." << endl;
            return false;
        } else {
            tinyxml2::XMLElement *root = doc.RootElement();
            tinyxml2::XMLElement *node = doc.NewElement(name.c_str());
            InsertSTLNode(object, doc, node);
            root->InsertEndChild(node);
        }
        return doc.SaveFile(filename.c_str());
    }

    template<typename T>
    bool serialize_xml(vector<T> object, const string &name, const string &filename) {
        ifstream fin(filename.c_str());
        if (!fin && createXML(filename)) {
            cout << "Failed to create XML document." << endl;
            return false;
        }
        tinyxml2::XMLDocument doc;
        bool isNotLoaded = doc.LoadFile(filename.c_str());
        if (isNotLoaded) {
            cout << "Failed to load XML file." << endl;
            return false;
        } else {
            tinyxml2::XMLElement *root = doc.RootElement();
            tinyxml2::XMLElement *node = doc.NewElement(name.c_str());
            int i = 0;
            for (typename vector<T>::const_iterator iter = object.begin(); iter != object.end(); iter++) {
                string tag = getType(*iter) + "_" + to_string(i);
                tinyxml2::XMLElement *subnode = doc.NewElement(tag.c_str());
                if (!isSTL(*iter)) subnode->SetAttribute("val", convert(*iter));
                else InsertSTLNode(*iter, doc, subnode);
                node->InsertEndChild(subnode);
                i++;
            }
            root->InsertEndChild(node);
        }
        return doc.SaveFile(filename.c_str());
    }

    template<typename T>
    bool serialize_xml(list<T> object, const string &name, const string &filename) {
        ifstream fin(filename.c_str());
        if (!fin && createXML(filename)) {
            cout << "Failed to create XML document." << endl;
            return false;
        }
        tinyxml2::XMLDocument doc;
        bool isNotLoaded = doc.LoadFile(filename.c_str());
        if (isNotLoaded) {
            cout << "Failed to load XML file." << endl;
            return false;
        } else {
            tinyxml2::XMLElement *root = doc.RootElement();
            tinyxml2::XMLElement *node = doc.NewElement(name.c_str());
            int i = 0;
            for (typename vector<T>::const_iterator iter = object.begin(); iter != object.end(); iter++) {
                string tag = getType(*iter) + "_" + to_string(i);
                tinyxml2::XMLElement *subnode = doc.NewElement(tag.c_str());
                if (!isSTL(*iter)) subnode->SetAttribute("val", convert(*iter));
                else InsertSTLNode(*iter, doc, subnode);
                node->InsertEndChild(subnode);
                i++;
            }
            root->InsertEndChild(node);
        }
        return doc.SaveFile(filename.c_str());
    }

    template<typename T>
    bool serialize_xml(set<T> object, const string &name, const string &filename) {
        ifstream fin(filename.c_str());
        if (!fin && createXML(filename)) {
            cout << "Failed to create XML document." << endl;
            return false;
        }
        tinyxml2::XMLDocument doc;
        bool isNotLoaded = doc.LoadFile(filename.c_str());
        if (isNotLoaded) {
            cout << "Failed to load XML file." << endl;
            return false;
        } else {
            tinyxml2::XMLElement *root = doc.RootElement();
            tinyxml2::XMLElement *node = doc.NewElement(name.c_str());
            int i = 0;
            for (typename vector<T>::const_iterator iter = object.begin(); iter != object.end(); iter++) {
                string tag = getType(*iter) + "_" + to_string(i);
                tinyxml2::XMLElement *subnode = doc.NewElement(tag.c_str());
                if (!isSTL(*iter)) subnode->SetAttribute("val", convert(*iter));
                else InsertSTLNode(*iter, doc, subnode);
                node->InsertEndChild(subnode);
                i++;
            }
            root->InsertEndChild(node);
        }
        return doc.SaveFile(filename.c_str());
    }

    template<typename T1, typename T2>
    bool serialize_xml(map<T1, T2> object, const string &name, const string &filename) {
        ifstream fin(filename.c_str());
        if (!fin && createXML(filename)) {
            cout << "Failed to create XML document." << endl;
            return false;
        }
        tinyxml2::XMLDocument doc;
        bool isNotLoaded = doc.LoadFile(filename.c_str());
        if (isNotLoaded) {
            cout << "Failed to load XML file." << endl;
            return false;
        } else {
            tinyxml2::XMLElement *root = doc.RootElement();
            tinyxml2::XMLElement *node = doc.NewElement(name.c_str());
            InsertSTLNode(object, doc, node);
            root->InsertEndChild(node);
        }
        return doc.SaveFile(filename.c_str());
    }
};

#endif //OBJECT_SERIALIZATION_XML_SERIALIZATION_H
