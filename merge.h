//
// Created by 张琦 on 2020/7/4.
//

#ifndef OBJECT_SERIALIZATION_MERGE_H
#define OBJECT_SERIALIZATION_MERGE_H

#include <string>
#include "xml_serialization.h"
#include "binary_serialization.h"

#define VNAME(value) (#value)

template <typename T>
void serialize(T &object, string filepath)
{
    binarySerialization::serializing_binary t;
    t.serialize(object, filepath);
}

void serialize(binarySerialization::UserDefinedType &object, const string& filepath)
{
    object.serialize(filepath);
}

template <typename T>
void deserialize(T &object, string filepath)
{
    binarySerialization::serializing_binary t;
    t.deserialize(object, filepath);
}

void deserialize(binarySerialization::UserDefinedType &object, const string& filepath)
{
    object.deserialize(filepath);
}

template <typename T>
void serialize_xml(T &object, string name, string filepath)
{
    xmlSerialization::serializing_xml t;
    t.serialize_xml(object, name, filepath, VNAME(object));
}

void serialize_xml(xmlSerialization::UserDefinedType &object, const string& name, const string& filepath)
{
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
