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
         * Description: Create the basic XML structure for the object of type T. */
        virtual bool createXML(const string &);

        /* Function: bool isSTL(T object)
         * Description: Identify if the object of type T is in STL. */
        template<typename T>
        bool isSTL(T object);

        /* Function: InsertNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Description: Insert an arithemetic node of type T as a subnode to 'node'. */
        template<typename T>
        void InsertNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node);

        /* Function: InsertSTLNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Description: To reorient the 'InsertSTLNode' fuction. */
        template<typename T>
        void InsertSTLNode(T object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node);

        /* Function: InsertSTLNode(pair<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Description: Insert a new node of type 'pair' as a subnode to 'node'. */
        template<typename T1, typename T2>
        void InsertSTLNode(pair<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node);

        /* Function: InsertSTLNode(vector<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Description: Insert a new node of type 'vector' as a subnode to 'node'. */
        template<typename T>
        void InsertSTLNode(vector<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node);

        /* Function: InsertSTLNode(list<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Description: Insert a new node of type 'list' as a subnode to 'node'. */
        template<typename T>
        void InsertSTLNode(list<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node);

        /* Function: InsertSTLNode(set<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Description: Insert a new node of type 'set' as a subnode to 'node'. */
        template<typename T>
        void InsertSTLNode(set<T> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node);

        /* Function: InsertSTLNode(map<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node)
         * Description: Insert a new node of type 'map' as a subnode to 'node'. */
        template<typename T1, typename T2>
        void InsertSTLNode(map<T1, T2> object, tinyxml2::XMLDocument &doc, tinyxml2::XMLElement *&node);

        /* Function: serialize_xml(T object, const string &name, const string &filename)
         * Description: To create an XML file, if necessary, and serialize object of
         * type T to xml format. */
        template<typename T>
        bool serialize_xml(T object, const string &name, const string &filename, const string &variableName);

        /* Fuction: serialize_xml(pair<T1, T2> object, const string &name, const string &filename)
         * Description: To create an XML file, if necessary, and serialize object of type
         * pair<T1, T2> to xml format. */
        template<typename T1, typename T2>
        bool serialize_xml(pair<T1, T2> object, const string &name, const string &filename, const string &variableName);

        /* Function: serialize_xml(vector<T> object, const string &name, const string &filename)
         * Description: To create an XML file, if necessary, and serialize object of
         * type vector<T> to xml format. */
        template<typename T>
        bool serialize_xml(vector<T> object, const string &name, const string &filename, const string &variableName);

        /* Function: serialize_xml(list<T> object, const string &name, const string &filename)
         * Description: To create an XML file, if necessary, and serialize object of
         * type list<T> to xml format. */
        template<typename T>
        bool serialize_xml(list<T> object, const string &name, const string &filename, const string &variableName);

        /* Function: serialize_xml(set<T> object, const string &name, const string &filename)
         * Description: To create an XML file, if necessary, and serialize object of
         * type set<T> to xml format. */
        template<typename T>
        bool serialize_xml(set<T> object, const string &name, const string &filename, const string &variableName);

        /* Fuction: serialize_xml(map<T1, T2> object, const string &name, const string &filename)
         * Description: To create an XML file, if necessary, and serialize object of type
         * map<T1, T2> to xml format. */
        template<typename T1, typename T2>
        bool serialize_xml(map<T1, T2> object, const string &name, const string &filename, const string &variableName);

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

        /* Fuction: write(string &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Write the data saved in contents[position] to object. */
        static void write(string &object, vector<const char *> &contents, vector<int> &pos, int &position);

        /* Fuction: write(pair<T1, T2> &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Divide the object to two parts and write each part. */
        template <typename T1, typename T2>
        void write(pair<T1, T2> &object, vector<const char *> &contents, vector<int> &pos, int &position);

        /* Fuction: write(vector<T> &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Looping through the vector and write each iterator. */
        template <typename T>
        void write(vector<T> &object, vector<const char *> &contents, vector<int> &pos, int &position);

        /* Fuction: write(list<T> &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Looping through the list and write each iterator. */
        template <typename T>
        void write(list<T> &object, vector<const char *> &contents, vector<int> &pos, int &position);

        /* Fuction: write(set<T> &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Looping through the set and write each iterator. */
        template <typename T>
        void write(set<T> &object, vector<const char *> &contents, vector<int> &pos, int &position);

        /* Fuction: write(map<T1, T2> &object, vector<const char *> &contents, vector<int> &pos, int &position);
         * Description: Looping through the map and write each iterator. */
        template <typename T1, typename T2>
        void write(map<T1, T2> &object, vector<const char *> &contents, vector<int> &pos, int &position);

        /* Function: deserialize_xml(T &object, const string &name, const string &filename)
         * Description: The main function for deserializing. */
        template<typename T>
        bool deserialize_xml(T &object, const string &name, const string &filename);
    };

    struct UserDefinedType : public serializing_xml {
    public:

        /* Function: UserDefinedType()
         * Description: Default constructor with nothing to do. */
        UserDefinedType() {};

        /* Function: UserDefinedType(T1 element1, T2 element2, T3 element3...)
         * Description: Constructor. */
        UserDefinedType(int element1, string element2, pair<vector<int>, pair<vector<int>, double>> element3): idx(element1), name(element2), data(element3){};

        /* Function: UserDefinedType(UserDefinedType const &source)
         * Description: Copy constructor. */
        UserDefinedType(UserDefinedType const &source) {
            idx = source.idx;
            name = source.name;
            data = source.data;
        }

        /* Function: createXML(const string &) override
         * An override for createXML() function in class serializing_xml.*/
        bool createXML(const string &) override;

        /* Function: serialize_xml(const string &)
         * An overloaded function for serialize this UserDefinedType data structure. */
        void serialize_xml(const string &);

        /* Function: deserialize_xml(const string &)
         * An overloaded function for deserialize this UserDefinedType data structure. */
        void deserialize_xml(const string &);
    private:
        /* In this part, you can define all the data types appearing in class serializing_xml.
         * Also, don't forget add additional serialze and deserialize functions in serialize_xml()
         * and deserialize_xml().*/
        int idx;
        string name;
        pair<vector<int>, pair<vector<int>, double>> data;
    };
}

#endif //OBJECT_SERIALIZATION_XML_SERIALIZATION_H
