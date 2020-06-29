//
// Created by 张琦 on 2020/6/27.
//

#include "xml_serialization.h"

using namespace std;

bool document::createXML(const string& filename) /* Create the basic XML structure for the object of type T. */
{
    tinyxml2::XMLDocument doc;
    string declaration = R"(<?xml version="1.0" encoding="UTF-8" standalone="no"?>)";
    doc.Parse(declaration.c_str());
    tinyxml2::XMLElement* root = doc.NewElement("serialization");
    doc.InsertEndChild(root);
    return doc.SaveFile(filename.c_str());
}