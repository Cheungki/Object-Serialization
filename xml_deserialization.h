//
// Created by 张琦 on 2020/6/29.
//

#ifndef OBJECT_SERIALIZATION_XML_DESERIALIZATION_H
#define OBJECT_SERIALIZATION_XML_DESERIALIZATION_H

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <cstdlib>
#include "tinyxml2.h"
#include "convert_to_char.h"
#include "xml_serialization.h"

using namespace std;

class deserializing_xml {
public:
    void read(tinyxml2::XMLElement *&node, vector<const char *> &contents, vector<int> &pos);

    static void write(int &object, vector<const char *> &contents, vector<int> &pos, int &position) {
        object = (int) strtol(contents[position], nullptr, 10);
        position++;
    }

    static void write(float &object, vector<const char *> &contents, vector<int> &pos, int &position) {
        object = (float) strtod(contents[position], nullptr);
        position++;
    }

    static void write(double &object, vector<const char *> &contents, vector<int> &pos, int &position) {
        object = strtod(contents[position], nullptr);
        position++;
    }

    static void write(char &object, vector<const char *> &contents, vector<int> &pos, int &position) {
        object = contents[position][0];
        position++;
    }

    static void write(string &object, vector<const char *> &contents, vector<int> &pos, int &position) {
        object = contents[position];
        position++;
    }

    template <typename T1, typename T2>
    void write(pair<T1, T2> &object, vector<const char *> &contents, vector<int> &pos, int &position) {
        write(object.first, contents, pos, position);
        write(object.second, contents, pos, position);
    }

    template <typename T>
    void write(vector<T> &object, vector<const char *> &contents, vector<int> &pos, int &position) {
        auto start = find(pos.begin(), pos.end(), position);
        auto end = start + 1;
        while (position < *end) {
            T temp;
            write(temp, contents, pos, position);
            object.push_back(temp);
        }
    }

    template <typename T>
    void write(list<T> &object, vector<const char *> &contents, vector<int> &pos, int &position) {
        auto start = find(pos.begin(), pos.end(), position);
        auto end = start + 1;
        while (position < *end) {
            T temp;
            write(temp, contents, pos, position);
            object.push_back(temp);
        }
    }

    template <typename T>
    void write(set<T> &object, vector<const char *> &contents, vector<int> &pos, int &position) {
        auto start = find(pos.begin(), pos.end(), position);
        auto end = start + 1;
        while (position < *end) {
            T temp;
            write(temp, contents, pos, position);
            object.push_back(temp);
        }
    }

    template <typename T1, typename T2>
    void write(map<T1, T2> &object, vector<const char *> &contents, vector<int> &pos, int &position) {
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
    bool deserialize_xml(T &object, const string &name, const string &filename) {
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

#endif //OBJECT_SERIALIZATION_XML_DESERIALIZATION_H
