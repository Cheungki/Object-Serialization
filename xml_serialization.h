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

namespace serialize_xml
{
    class serializing_xml {
    public:
        /* Function: static bool createXML(const string &filename)
         * Create the basic XML structure for the object of type T. */
        virtual bool createXML(const string &);

        /* Function: bool isSTL(T object)
         * Identify if the object of type T is in STL. */
        template<typename T>
        bool isSTL(T object)
        {
            string type = getType(object);
            return !(type == "int" || type == "float" || type == "double" || type == "char" || type == "string");
        }

        /* Function: InsertNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Insert an arithemetic node of type T as a subnode to 'node'. */
        template<typename T>
        void InsertNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
        {
            tinyxml2::XMLElement *subnode;
            subnode = doc.NewElement(getType(object).c_str());
            subnode->SetAttribute("val", convert(object));
            node->InsertEndChild(subnode);
        }

        /* Function: InsertSTLNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * To reorient the 'InsertSTLNode' fuction. */
        template<typename T>
        void InsertSTLNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
        {
            InsertSTLNode<T>(object, doc, node);
        }

        /* Function: InsertSTLNode(pair<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Insert a new node of type 'pair' as a subnode to 'node'. */
        template<typename T1, typename T2>
        void InsertSTLNode(pair<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
        {
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

        /* Function: InsertSTLNode(vector<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Insert a new node of type 'vector' as a subnode to 'node'. */
        template<typename T>
        void InsertSTLNode(vector<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
        {
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

        /* Function: InsertSTLNode(list<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Insert a new node of type 'list' as a subnode to 'node'. */
        template<typename T>
        void InsertSTLNode(list<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
        {
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

        /* Function: InsertSTLNode(set<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Insert a new node of type 'set' as a subnode to 'node'. */
        template<typename T>
        void InsertSTLNode(set<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
        {
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

        /* Function: InsertSTLNode(map<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Insert a new node of type 'map' as a subnode to 'node'. */
        template<typename T1, typename T2>
        void InsertSTLNode(map<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
        {
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

        /* Function: serialize_xml(T object, const string &name, const string &filename)
         * */
        template<typename T>
        bool serialize_xml(T object, const string &name, const string &filename)
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
                InsertNode(object, doc, node);
                root->InsertEndChild(node);
            }
            return doc.SaveFile(filename.c_str());
        }

        template<typename T1, typename T2>
        bool serialize_xml(pair<T1, T2> object, const string &name, const string &filename)
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
                InsertSTLNode(object, doc, node);
                root->InsertEndChild(node);
            }
            return doc.SaveFile(filename.c_str());
        }

        template<typename T>
        bool serialize_xml(vector<T> object, const string &name, const string &filename)
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
        bool serialize_xml(list<T> object, const string &name, const string &filename)
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
        bool serialize_xml(set<T> object, const string &name, const string &filename)
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
        bool serialize_xml(map<T1, T2> object, const string &name, const string &filename)
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
                InsertSTLNode(object, doc, node);
                root->InsertEndChild(node);
            }
            return doc.SaveFile(filename.c_str());
        }

        void read(tinyxml2::XMLElement *&node, vector<const char *> &contents, vector<int> &pos);

        static void write(int &object, vector<const char *> &contents, vector<int> &pos, int &position);

        static void write(float &object, vector<const char *> &contents, vector<int> &pos, int &position);

        static void write(double &object, vector<const char *> &contents, vector<int> &pos, int &position);

        static void write(char &object, vector<const char *> &contents, vector<int> &pos, int &position);

        static void write(string &object, vector<const char *> &contents, vector<int> &pos, int &position);

        template <typename T1, typename T2>
        void write(pair<T1, T2> &object, vector<const char *> &contents, vector<int> &pos, int &position)
        {
            write(object.first, contents, pos, position);
            write(object.second, contents, pos, position);
        }

        template <typename T>
        void write(vector<T> &object, vector<const char *> &contents, vector<int> &pos, int &position)
        {
            auto start = find(pos.begin(), pos.end(), position);
            auto end = start + 1;
            while (position < *end) {
                T temp;
                write(temp, contents, pos, position);
                object.push_back(temp);
            }
        }

        template <typename T>
        void write(list<T> &object, vector<const char *> &contents, vector<int> &pos, int &position)
        {
            auto start = find(pos.begin(), pos.end(), position);
            auto end = start + 1;
            while (position < *end) {
                T temp;
                write(temp, contents, pos, position);
                object.push_back(temp);
            }
        }

        template <typename T>
        void write(set<T> &object, vector<const char *> &contents, vector<int> &pos, int &position)
        {
            auto start = find(pos.begin(), pos.end(), position);
            auto end = start + 1;
            while (position < *end) {
                T temp;
                write(temp, contents, pos, position);
                object.push_back(temp);
            }
        }

        template <typename T1, typename T2>
        void write(map<T1, T2> &object, vector<const char *> &contents, vector<int> &pos, int &position)
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
        bool deserialize_xml(T &object, const string &name, const string &filename)
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
    };

    struct UserDefinedType : public serializing_xml {
    public:
        UserDefinedType() {};
        UserDefinedType(int element1, string element2, vector<double> element3): idx(element1), name(element2), data(element3){};
        UserDefinedType(UserDefinedType const &source) {
            idx = source.idx;
            name = source.name;
            data = source.data;
        }
        bool createXML(const string &) override;
        void serialize_xml(const string &);
        void deserialize_xml(const string &);
    private:
        int idx;
        string name;
        vector<double> data;
    };
}

#endif //OBJECT_SERIALIZATION_XML_SERIALIZATION_H
