//
// Created by 张琦 on 2020/7/4.
//

#ifndef OBJECT_SERIALIZATION_MERGE_H
#define OBJECT_SERIALIZATION_MERGE_H

#include <string>
#include <cstdio>
#include "xml_serialization.h"
#include "binary_serialization.h"

#define VNAME(value) (#value)

template <typename T>
void serialize(T &object, string filepath)
{
    remove(filepath.c_str());
    auto t = new binarySerialization::serializing_binary;
    t->serialize(object, filepath);
    delete t;
}

void serialize(binarySerialization::UserDefinedType &object, const string& filepath)
{
    remove(filepath.c_str());
    object.serialize(filepath);
}

template <typename T>
void deserialize(T &object, string filepath)
{
    auto t = new binarySerialization::serializing_binary;
    t->deserialize(object, filepath);
    delete t;
}

void deserialize(binarySerialization::UserDefinedType &object, const string& filepath)
{
    object.deserialize(filepath);
}

template <typename T>
void serialize_xml(T &object, string name, string filepath)
{
    remove(filepath.c_str());
    auto t = new xmlSerialization::serializing_xml;
    t->serialize_xml(object, name, filepath, VNAME(object));
    delete t;
}

void serialize_xml(xmlSerialization::UserDefinedType &object, const string& name, const string& filepath)
{
    remove(filepath.c_str());
    object.serialize_xml(name, filepath);
}

template <typename T>
void deserialize_xml(T &object, string name, string filepath)
{
    auto t = new xmlSerialization::serializing_xml;
    t->deserialize_xml(object, name, filepath);
    delete t;
}

void deserialize_xml(xmlSerialization::UserDefinedType &object, const string& name, const string& filepath)
{
    object.deserialize_xml(name, filepath);
}

#endif //OBJECT_SERIALIZATION_MERGE_H