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

namespace xmlSerialization
{
    class serializing_xml {
    public:
        /* Function: static bool createXML(const string &filepath)
         * Description: Create the basic XML structure for the object of type T. */
        static bool createXML(const string &);

        /* Function: bool isSTL(T object)
         * Description: Identify if the object of type T is in STL. */
        template<typename T>
        bool isSTL(T object)
        {
            return !(is_arithmetic<T>::value || typeid(object).name() == typeid(string).name());
        }

        /* Function: InsertNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Description: Insert an arithemetic node of type T as a subnode to 'node'. */
        template<typename T>
        void InsertNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
        {
            tinyxml2::XMLElement *subnode;
            subnode = doc.NewElement(getType(object).c_str());
            subnode->SetAttribute("val", convert(object));
            node->InsertEndChild(subnode);
        }

        /* Function: InsertSTLNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Description: To reorient the 'InsertSTLNode' fuction. */
        template<typename T>
        void InsertSTLNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
        {
            InsertSTLNode<T>(object, doc, node);
        }

        /* Function: InsertSTLNode(pair<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Description: Insert a new node of type 'pair' as a subnode to 'node'. */
        template<typename T1, typename T2>
        void InsertSTLNode(pair<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
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

        /* Function: InsertSTLNode(vector<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Description: Insert a new node of type 'vector' as a subnode to 'node'. */
        template<typename T>
        void InsertSTLNode(vector<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
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

        /* Function: InsertSTLNode(list<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Description: Insert a new node of type 'list' as a subnode to 'node'. */
        template<typename T>
        void InsertSTLNode(list<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
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

        /* Function: InsertSTLNode(set<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Description: Insert a new node of type 'set' as a subnode to 'node'. */
        template<typename T>
        void InsertSTLNode(set<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
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

        /* Function: InsertSTLNode(map<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Description: Insert a new node of type 'map' as a subnode to 'node'. */
        template<typename T1, typename T2>
        void InsertSTLNode(map<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
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

        /* Function: serialize_xml(T object, const string &name, const string &filepath)
         * Description: To create an XML file, if necessary, and serialize object of
         * type T to xml format. */
        template<typename T>
        bool serialize_xml(T object, const string &name, const string &filepath, const string &variableName)
        {
            ifstream fin(filepath.c_str());
            if (!fin && createXML(filepath)) {
                cout << "Failed to create XML document." << endl;
                return false;
            }
            tinyxml2::XMLDocument doc;
            bool isNotLoaded = doc.LoadFile(filepath.c_str());
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
            return doc.SaveFile(filepath.c_str());
        }

        /* Fuction: serialize_xml(pair<T1, T2> object, const string &name, const string &filepath)
         * Description: To create an XML file, if necessary, and serialize object of type
         * pair<T1, T2> to xml format. */
        template<typename T1, typename T2>
        bool serialize_xml(pair<T1, T2> object, const string &name, const string &filepath, const string &variableName)
        {
            ifstream fin(filepath.c_str());
            if (!fin && createXML(filepath)) {
                cout << "Failed to create XML document." << endl;
                return false;
            }
            tinyxml2::XMLDocument doc;
            bool isNotLoaded = doc.LoadFile(filepath.c_str());
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
            return doc.SaveFile(filepath.c_str());
        }

        /* Function: serialize_xml(vector<T> object, const string &name, const string &filepath)
         * Description: To create an XML file, if necessary, and serialize object of
         * type vector<T> to xml format. */
        template<typename T>
        bool serialize_xml(vector<T> object, const string &name, const string &filepath, const string &variableName)
        {
            ifstream fin(filepath.c_str());
            if (!fin && createXML(filepath)) {
                cout << "Failed to create XML document." << endl;
                return false;
            }
            tinyxml2::XMLDocument doc;
            bool isNotLoaded = doc.LoadFile(filepath.c_str());
            if (isNotLoaded) {
                cout << "Failed to load XML file." << endl;
                return false;
            } else {
                tinyxml2::XMLElement *root = doc.RootElement();
                tinyxml2::XMLElement *node = doc.NewElement(name.c_str());
                node->SetAttribute("variableName", variableName.c_str());
                node->SetAttribute("type", "vector");
                InsertSTLNode(object, doc, node);
                root->InsertEndChild(node);
            }
            return doc.SaveFile(filepath.c_str());
        }

        /* Function: serialize_xml(list<T> object, const string &name, const string &filepath)
         * Description: To create an XML file, if necessary, and serialize object of
         * type list<T> to xml format. */
        template<typename T>
        bool serialize_xml(list<T> object, const string &name, const string &filepath, const string &variableName)
        {
            ifstream fin(filepath.c_str());
            if (!fin && createXML(filepath)) {
                cout << "Failed to create XML document." << endl;
                return false;
            }
            tinyxml2::XMLDocument doc;
            bool isNotLoaded = doc.LoadFile(filepath.c_str());
            if (isNotLoaded) {
                cout << "Failed to load XML file." << endl;
                return false;
            } else {
                tinyxml2::XMLElement *root = doc.RootElement();
                tinyxml2::XMLElement *node = doc.NewElement(name.c_str());
                node->SetAttribute("variableName", variableName.c_str());
                node->SetAttribute("type", "list");
                InsertSTLNode(object, doc, node);
                root->InsertEndChild(node);
            }
            return doc.SaveFile(filepath.c_str());
        }

        /* Function: serialize_xml(set<T> object, const string &name, const string &filepath)
         * Description: To create an XML file, if necessary, and serialize object of
         * type set<T> to xml format. */
        template<typename T>
        bool serialize_xml(set<T> object, const string &name, const string &filepath, const string &variableName)
        {
            ifstream fin(filepath.c_str());
            if (!fin && createXML(filepath)) {
                cout << "Failed to create XML document." << endl;
                return false;
            }
            tinyxml2::XMLDocument doc;
            bool isNotLoaded = doc.LoadFile(filepath.c_str());
            if (isNotLoaded) {
                cout << "Failed to load XML file." << endl;
                return false;
            } else {
                tinyxml2::XMLElement *root = doc.RootElement();
                tinyxml2::XMLElement *node = doc.NewElement(name.c_str());
                node->SetAttribute("variableName", variableName.c_str());
                node->SetAttribute("type", "set");
                int i = 0;
                for (typename set<T>::const_iterator iter = object.begin(); iter != object.end(); iter++) {
                    string tag = getType(*iter) + "_" + to_string(i);
                    tinyxml2::XMLElement *subnode = doc.NewElement(tag.c_str());
                    if (!isSTL(*iter)) subnode->SetAttribute("val", convert(*iter));
                    else InsertSTLNode(*iter, doc, subnode);
                    node->InsertEndChild(subnode);
                    i++;
                }
                root->InsertEndChild(node);
            }
            return doc.SaveFile(filepath.c_str());
        }

        /* Fuction: serialize_xml(map<T1, T2> object, const string &name, const string &filepath)
         * Description: To create an XML file, if necessary, and serialize object of type
         * map<T1, T2> to xml format. */
        template<typename T1, typename T2>
        bool serialize_xml(map<T1, T2> object, const string &name, const string &filepath, const string &variableName)
        {
            ifstream fin(filepath.c_str());
            if (!fin && createXML(filepath)) {
                cout << "Failed to create XML document." << endl;
                return false;
            }
            tinyxml2::XMLDocument doc;
            bool isNotLoaded = doc.LoadFile(filepath.c_str());
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
            return doc.SaveFile(filepath.c_str());
        }

        /* Fuction: read(tinyxml2::XMLElement *&node, vector<const char *> &contents, vector<int> &pos)
         * Description: Read all the data saved in the node, push them into the vector named
         * contents, and record the position we need to jump to a new node in pos. */
        void read(tinyxml2::XMLElement *&node, vector<const char *> &contents, vector<int> &pos);

        /* Write part:
         * Method: Write the data to object iteratively. */

        /* Fuction: write(int &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Write the data saved in contents[position] to object. */
        static void write(int &object, vector<const char *> &contents, vector<int> &pos, int &position);

        /* Fuction: write(float &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Write the data saved in contents[position] to object. */
        static void write(float &object, vector<const char *> &contents, vector<int> &pos, int &position);

        /* Fuction: write(double &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Write the data saved in contents[position] to object. */
        static void write(double &object, vector<const char *> &contents, vector<int> &pos, int &position);

        /* Fuction: write(char &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Write the data saved in contents[position] to object. */
        static void write(char &object, vector<const char *> &contents, vector<int> &pos, int &position);

        /* Fuction: write(bool &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Write the data saved in contents[position] to object. */
        static void write(bool &object, vector<const char *> &contents, vector<int> &pos, int &position);

        /* Fuction: write(string &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Write the data saved in contents[position] to object. */
        static void write(string &object, vector<const char *> &contents, vector<int> &pos, int &position);

        /* Fuction: write(pair<T1, T2> &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Divide the object to two parts and write each part. */
        template <typename T1, typename T2>
        void write(pair<T1, T2> &object, vector<const char *> &contents, vector<int> &pos, int &position)
        {
            write(object.first, contents, pos, position);
            write(object.second, contents, pos, position);
        }

        /* Fuction: write(vector<T> &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Looping through the vector and write each iterator. */
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

        /* Fuction: write(list<T> &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Looping through the list and write each iterator. */
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

        /* Fuction: write(set<T> &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Looping through the set and write each iterator. */
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

        /* Fuction: write(map<T1, T2> &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Looping through the map and write each iterator. */
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

        /* Function: deserialize_xml(T &object, const string &name, const string &filepath)
         * Description: The main function for deserializing. */
        template<typename T>
        bool deserialize_xml(T &object, const string &name, const string &filepath)
        {
            tinyxml2::XMLDocument doc;
            bool isNotLoaded = doc.LoadFile(filepath.c_str());
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

        /* Function: UserDefinedType()
         * Description: Default constructor with nothing to do. */
        UserDefinedType() {};

        /* Function: UserDefinedType(T1 element1, T2 element2, T3 element3...)
         * Description: Constructor. */
        UserDefinedType(int element1, string element2, vector<double> element3): idx(element1), name(element2), data(element3){};

        /* Function: UserDefinedType(UserDefinedType const &source)
         * Description: Copy constructor. */
        UserDefinedType(UserDefinedType const &source) {
            idx = source.idx;
            name = source.name;
            data = source.data;
        }

        /* Function: createXML(const string &) override
         * An override for createXML() function in class serializing_xml.*/
        static bool createXML(const string &, const string &);

        /* Function: serialize_xml(const string &)
         * An overloaded function for serialize this UserDefinedType data structure. */
        void serialize_xml(const string &, const string &);

        /* Function: deserialize_xml(const string &)
         * An overloaded function for deserialize this UserDefinedType data structure. */
        void deserialize_xml(const string &, const string &);

        void printinfo()
        {
            cout << "idx = " << idx << endl;
            cout << "name = " << name << endl;
            int i;
            cout << "data = {";
            for (i = 0; i < data.size(); i++) {
                cout << data[i];
                if(i != data.size() - 1) cout << ", ";
                else cout << "}" << endl;
            }
        }
    private:
        /* In this part, you can define all the data types appearing in class serializing_xml.
         * Also, don't forget add additional serialze and deserialize functions in serialize_xml()
         * and deserialize_xml().*/
        int idx;
        string name;
        vector<double> data;
    };
}

#endif //OBJECT_SERIALIZATION_XML_SERIALIZATION_H
