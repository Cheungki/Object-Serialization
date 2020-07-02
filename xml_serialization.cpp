//
// Created by 张琦 on 2020/6/27.
//

#include "xml_serialization.h"

#define VNAME(value) (#value)

namespace serialize_xml
{
    bool serializing_xml::createXML(const string &filename) /* Create the basic XML structure for the object of type T. */
    {
        tinyxml2::XMLDocument doc;
        string declaration = R"(<?xml version="1.0" encoding="UTF-8" standalone="no"?>)";
        doc.Parse(declaration.c_str());
        tinyxml2::XMLElement *root = doc.NewElement("serialization");
        doc.InsertEndChild(root);
        return doc.SaveFile(filename.c_str());
    }

    void serializing_xml::read(tinyxml2::XMLElement *&node, std::vector<const char *> &v, std::vector<int> &pos)
    {
        if(node == nullptr) return;
        else {
            const tinyxml2::XMLAttribute *attribute = node->FirstAttribute();
            const char *content = nullptr;
            if(attribute != nullptr) content = attribute->Value();

            /* To check if the attribute consists of a parameter named "val".
             * If yes, pushing the content of the parameter into the vector
             * and turning to the sibling node of the current one. */
            if(strcmp(attribute->Name(), "val") == 0) {
                v.push_back(content);
                tinyxml2::XMLElement *sibnode = node->NextSiblingElement();
                read(sibnode, v, pos);
            }
            else {
                tinyxml2::XMLElement *subnode = node->FirstChildElement();
                read(subnode, v, pos);

                /* Record the position when we need to deserialize a sibling node. */
                pos.push_back(v.size());

                /* To check if the node is NULL. */
                if(node->NextSiblingElement() != nullptr) {
                    tinyxml2::XMLElement *sibnode = node->NextSiblingElement();
                    read(sibnode, v, pos);
                }
            }
        }
    }

    void serializing_xml::write(int &object, vector<const char *> &contents, vector<int> &pos, int &position)
    {
        object = (int) strtol(contents[position], nullptr, 10);
        position++;
    }

    void serializing_xml::write(float &object, vector<const char *> &contents, vector<int> &pos, int &position)
    {
        object = (float) strtod(contents[position], nullptr);
        position++;
    }

    void serializing_xml::write(double &object, vector<const char *> &contents, vector<int> &pos, int &position)
    {
        object = strtod(contents[position], nullptr);
        position++;
    }

    void serializing_xml::write(char &object, vector<const char *> &contents, vector<int> &pos, int &position)
    {
        object = contents[position][0];
        position++;
    }

    void serializing_xml::write(string &object, vector<const char *> &contents, vector<int> &pos, int &position)
    {
        object = contents[position];
        position++;
    }

    template<typename T1, typename T2>
    void serializing_xml::write(pair<T1, T2> &object, vector<const char *> &contents, vector<int> &pos, int &position)
    {
        write(object.first, contents, pos, position);
        write(object.second, contents, pos, position);
    }

    template<typename T>
    void serializing_xml::write(vector<T> &object, vector<const char *> &contents, vector<int> &pos, int &position)
    {
        auto start = find(pos.begin(), pos.end(), position);
        auto end = start + 1;
        while (position < *end) {
            T temp;
            write(temp, contents, pos, position);
            object.push_back(temp);
        }
    }

    template<typename T>
    void serializing_xml::write(list<T> &object, vector<const char *> &contents, vector<int> &pos, int &position)
    {
        auto start = find(pos.begin(), pos.end(), position);
        auto end = start + 1;
        while (position < *end) {
            T temp;
            write(temp, contents, pos, position);
            object.push_back(temp);
        }
    }

    template<typename T>
    void serializing_xml::write(set<T> &object, vector<const char *> &contents, vector<int> &pos, int &position)
    {
        auto start = find(pos.begin(), pos.end(), position);
        auto end = start + 1;
        while (position < *end) {
            T temp;
            write(temp, contents, pos, position);
            object.push_back(temp);
        }
    }

    template<typename T1, typename T2>
    void serializing_xml::write(map<T1, T2> &object, vector<const char *> &contents, vector<int> &pos, int &position)
    {
        auto start = find(pos.begin(), pos.end(), position);
        auto end = start + 1;
        while (position < *end) {
            T1 first;
            T2 second;
            write(first, contents, pos, position);
            write(second, contents, pos, position);
            object.push_back(make_pair(first, second));
        }
    }

    template<typename T>
    bool serializing_xml::deserialize_xml(T &object, const string &name, const string &filename)
    {
        tinyxml2::XMLDocument doc;
        bool isNotLoaded = doc.LoadFile(filename.c_str());
        if (isNotLoaded) {
            cout << "Failed to load XML file." << endl;
            return false;
        } else {
            tinyxml2::XMLElement *root = doc.RootElement();
            tinyxml2::XMLElement *node = root->FirstChildElement(name.c_str());
            vector<const char *> contents;
            vector<int> pos;
            pos.push_back(0);
            int position = 0;
            read(node, contents, pos);
            write(object, contents, pos, position);
            return true;
        }
    }

    template<typename T1, typename T2>
    bool serializing_xml::serialize_xml(map<T1, T2> object, const string &name, const string &filename, const string &variableName)
    {
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
            node->SetAttribute("variableName", variableName.c_str());
            node->SetAttribute("type", "map");
            InsertSTLNode(object, doc, node);
            root->InsertEndChild(node);
        }
        return doc.SaveFile(filename.c_str());
    }

    template<typename T>
    bool serializing_xml::serialize_xml(set<T> object, const string &name, const string &filename, const string &variableName)
    {
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
            node->SetAttribute("variableName", variableName.c_str());
            node->SetAttribute("type", "set");
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
    bool serializing_xml::isSTL(T object) {
        string type = getType(object);
        return !(type == "int" || type == "float" || type == "double" || type == "char" || type == "string");
    }

    template<typename T>
    void serializing_xml::InsertNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
    {
        tinyxml2::XMLElement *subnode;
        subnode = doc.NewElement(getType(object).c_str());
        subnode->SetAttribute("val", convert(object));
        node->InsertEndChild(subnode);
    }

    template<typename T>
    void serializing_xml::InsertSTLNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
    {
        InsertSTLNode<T>(object, doc, node);
    }

    template<typename T1, typename T2>
    void serializing_xml::InsertSTLNode(pair<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
    {
        node->SetAttribute("type", "pair");
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
    void serializing_xml::InsertSTLNode(vector<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
    {
        node->SetAttribute("type", "vector");
        node->SetAttribute("size", convert((int)object.size()));
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
    void serializing_xml::InsertSTLNode(list<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
    {
        node->SetAttribute("type", "list");
        node->SetAttribute("size", convert((int)object.size()));
        int i = 0;
        for (typename list<T>::const_iterator iter = object.begin(); iter != object.end(); iter++) {
            string tag = getType(*iter) + "_" + to_string(i);
            tinyxml2::XMLElement *subnode = doc.NewElement(tag.c_str());
            if (isSTL(*iter)) InsertSTLNode(*iter, doc, subnode);
            else subnode->SetAttribute("val", convert(*iter));
            node->InsertEndChild(subnode);
            i++;
        }
    }

    template<typename T>
    void serializing_xml::InsertSTLNode(set<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
    {
        node->SetAttribute("type", "set");
        node->SetAttribute("size", convert((int)object.size()));
        int i = 0;
        for (typename set<T>::const_iterator iter = object.begin(); iter != object.end(); iter++) {
            string tag = getType(*iter) + "_" + to_string(i);
            tinyxml2::XMLElement *subnode = doc.NewElement(tag.c_str());
            if (isSTL(*iter)) InsertSTLNode(*iter, doc, subnode);
            else subnode->SetAttribute("val", convert(*iter));
            node->InsertEndChild(subnode);
            i++;
        }
    }

    template<typename T1, typename T2>
    void serializing_xml::InsertSTLNode(map<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
    {
        node->SetAttribute("type", "map");
        node->SetAttribute("size", convert((int)object.size()));
        int i = 0;
        for (typename map<T1, T2>::const_iterator iter = object.begin(); iter != object.end(); iter++) {
            string tag = getType(*iter) + "_" + to_string(i);
            tinyxml2::XMLElement *subnode_1 = doc.NewElement("key");
            tinyxml2::XMLElement *subnode_2 = doc.NewElement("value");
            subnode_1->SetAttribute("type", getType(iter->first));
            subnode_2->SetAttribute("type", getType(iter->second));
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
    bool
    serializing_xml::serialize_xml(T object, const string &name, const string &filename, const string &variableName)
    {
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
            node->SetAttribute("variableName", variableName.c_str());
            node->SetAttribute("type", getType(object).c_str());
            InsertNode(object, doc, node);
            root->InsertEndChild(node);
        }
        return doc.SaveFile(filename.c_str());
    }

    template<typename T1, typename T2>
    bool serializing_xml::serialize_xml(pair<T1, T2> object, const string &name, const string &filename, const string &variableName)
    {
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
            node->SetAttribute("variableName", variableName.c_str());
            node->SetAttribute("type", "pair");
            InsertSTLNode(object, doc, node);
            root->InsertEndChild(node);
        }
        return doc.SaveFile(filename.c_str());
    }

    template<typename T>
    bool serializing_xml::serialize_xml(vector<T> object, const string &name, const string &filename, const string &variableName)
    {
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
            node->SetAttribute("variableName", variableName.c_str());
            node->SetAttribute("type", "vector");
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
    bool serializing_xml::serialize_xml(list<T> object, const string &name, const string &filename, const string &variableName)
    {
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
            node->SetAttribute("variableName", variableName.c_str());
            node->SetAttribute("type", "list");
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

    bool UserDefinedType::createXML(const string &filename)
    {
        tinyxml2::XMLDocument doc;
        string declaration = R"(<?xml version="1.0" encoding="UTF-8" standalone="no"?>)";
        doc.Parse(declaration.c_str());
        tinyxml2::XMLElement *root = doc.NewElement("UserDefinedType");
        doc.InsertEndChild(root);
        return doc.SaveFile(filename.c_str());
    }

    void UserDefinedType::serialize_xml(const string &filename)
    {
        createXML(filename);
        serializing_xml::serialize_xml(idx, "element_1", filename, VNAME(idx));
        serializing_xml::serialize_xml(name, "element_2", filename, VNAME(name));
        serializing_xml::serialize_xml(data, "element_3", filename, VNAME(data));
    }

    void UserDefinedType::deserialize_xml(const string &filename)
    {
        serializing_xml::deserialize_xml(idx, "element_1", filename);
        serializing_xml::deserialize_xml(name, "element_2", filename);
        serializing_xml::deserialize_xml(data, "element_3", filename);
    }
}