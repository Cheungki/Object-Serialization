//
// Created by 张琦 on 2020/6/27.
//

#ifndef OBJECT_SERIALIZATION_BINARY_SERIALIZATION_H
#define OBJECT_SERIALIZATION_BINARY_SERIALIZATION_H

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

namespace binarySerialization
{
    class serializing_binary {
    public:
        serializing_binary() :position(0) {}

        int position;

        template <typename T>
        bool serialize(T object, const string &filename)
        {
            ofstream outFile(filename.c_str(), ios::out | ios::binary | ios::app);
            outFile.write((char *)&object, sizeof(object));
            outFile.close();
            return true;
        }

        template <typename T1, typename T2>
        bool serialize(pair<T1, T2> object, const string &filename)
        {
            serialize(object.first, filename);
            serialize(object.second, filename);
            return true;
        }

        template <typename T>
        bool serialize(vector<T> object, const string &filename)
        {
            int size = object.size();
            ofstream outFile(filename.c_str(), ios::out | ios::binary | ios::app);
            outFile.write((char *)&size, sizeof(size));
            outFile.close();
            for (typename vector<T>::const_iterator iter = object.begin(); iter != object.end(); iter++)
                serialize((*iter), filename);
            return true;
        }

        template <typename T>
        bool serialize(list<T> object, const string &filename)
        {
            int size = object.size();
            ofstream outFile(filename.c_str(), ios::out | ios::binary | ios::app);
            outFile.write((char *)&size, sizeof(size));
            outFile.close();
            for (typename list<T>::const_iterator iter = object.begin(); iter != object.end(); iter++)
                serialize((*iter), filename);
            return true;
        }

        template <typename T>
        bool serialize(set<T> object, const string &filename)
        {
            int size = object.size();
            ofstream outFile(filename.c_str(), ios::out | ios::binary | ios::app);
            outFile.write((char *)&size, sizeof(size));
            outFile.close();
            for (typename set<T>::const_iterator iter = object.begin(); iter != object.end(); iter++)
                serialize((*iter), filename);
            return true;
        }

        template <typename T1, typename T2>
        bool serialize(map<T1, T2> object, const string &filename)
        {
            int size = object.size();
            ofstream outFile(filename.c_str(), ios::out | ios::binary | ios::app);
            outFile.write((char *)&size, sizeof(size));
            outFile.close();
            for (typename map<T1, T2>::const_iterator iter = object.begin(); iter != object.end(); iter++)
                serialize((*iter), filename);
            return true;
        }

        template <typename T>
        bool deserialize(T &object, const string &filename)
        {
            ifstream inFile(filename.c_str(), ios::in | ios::binary);
            inFile.seekg(position);
            position += sizeof(object);
            inFile.read((char*)&object, sizeof(object));
            inFile.close();
            return true;
        }

        template <typename T1, typename T2>
        bool deserialize(pair<T1, T2> &object, const string &filename)
        {
            deserialize(object.first, filename);
            deserialize(object.second, filename);
            return true;
        }

        template <typename T>
        bool deserialize(vector<T> &object, const string &filename)
        {
            int size, i;
            ifstream inFile(filename.c_str(), ios::in | ios::binary);
            inFile.seekg(position);
            inFile.read((char*)&size, sizeof(size));
            position += sizeof(size);
            inFile.close();
            for (i = 0; i < size; i++) {
                T iter;
                deserialize(iter, filename);
                object.push_back(iter);
            }
            return true;
        }

        template <typename T>
        bool deserialize(list<T> &object, const string &filename)
        {
            int size, i;
            ifstream inFile(filename.c_str(), ios::in | ios::binary);
            inFile.seekg(position);
            inFile.read((char*)&size, sizeof(size));
            position += sizeof(size);
            inFile.close();
            for (i = 0; i < size; i++) {
                T iter;
                deserialize(iter, filename);
                object.push_back(iter);
            }
            return true;
        }

        template <typename T>
        bool deserialize(set<T> &object, const string &filename)
        {
            int size, i;
            ifstream inFile(filename.c_str(), ios::in | ios::binary);
            inFile.seekg(position);
            inFile.read((char*)&size, sizeof(size));
            position += sizeof(size);
            inFile.close();
            for (i = 0; i < size; i++) {
                T iter;
                deserialize(iter, filename);
                object.push_back(iter);
            }
            return true;
        }

        template <typename T1, typename T2>
        bool deserialize(map<T1, T2> &object, const string &filename)
        {
            int size, i;
            ifstream inFile(filename.c_str(), ios::in | ios::binary);
            inFile.seekg(position);
            inFile.read((char*)&size, sizeof(size));
            position += sizeof(size);
            inFile.close();
            for (i = 0; i < size; i++) {
                pair<T1, T2> iter;
                deserialize(iter, filename);
                object.insert(iter);
            }
            return true;
        }
    };

    class UserDefinedType: public serializing_binary {
    public:
        UserDefinedType() {}
        UserDefinedType(int element1, string element2, vector<double> element3):idx(element1), name(element2), data(element3) {}
        UserDefinedType(UserDefinedType const &source)  : serializing_binary(source) {
            idx = source.idx;
            name = source.name;
            data = source.data;
        }
        void serialize(const string &);
        void deserialize(const string &);
        void printinfo();
    private:
        int idx;
        string name;
        vector<double> data;
    };
}

#endif //OBJECT_SERIALIZATION_BINARY_SERIALIZATION_H
