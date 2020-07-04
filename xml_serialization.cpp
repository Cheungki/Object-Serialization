//
// Created by 张琦 on 2020/6/27.
//

#include "xml_serialization.h"

#define VNAME(value) (#value)

namespace xmlSerialization
{
    bool serializing_xml::createXML(const string &filepath) /* Create the basic XML structure for the object of type T. */
    {
        tinyxml2::XMLDocument doc;
        string declaration = R"(<?xml version="1.0" encoding="UTF-8" standalone="no"?>)";
        doc.Parse(declaration.c_str());
        tinyxml2::XMLElement *root = doc.NewElement("serialization");
        doc.InsertEndChild(root);
        return doc.SaveFile(filepath.c_str());
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

    void serializing_xml::write(bool &object, vector<const char *> &contents, vector<int> &pos, int &position)
    {
        object = strcmp(contents[position], "true") == 0;
        position++;
    }

    void serializing_xml::write(string &object, vector<const char *> &contents, vector<int> &pos, int &position)
    {
        object = contents[position];
        position++;
    }

    bool UserDefinedType::createXML(const string &filename, const string &filepath)
    {
        tinyxml2::XMLDocument doc;
        string declaration = R"(<?xml version="1.0" encoding="UTF-8" standalone="no"?>)";
        doc.Parse(declaration.c_str());
        tinyxml2::XMLElement *root = doc.NewElement(filename.c_str());
        doc.InsertEndChild(root);
        return doc.SaveFile(filepath.c_str());
    }

    void UserDefinedType::serialize_xml(const string &filename, const string &filepath)
    {
        createXML(filename, filepath);
        serializing_xml::serialize_xml(idx, "element_1", filepath, VNAME(idx));
        serializing_xml::serialize_xml(name, "element_2", filepath, VNAME(name));
        serializing_xml::serialize_xml(data, "element_3", filepath, VNAME(data));
    }

    void UserDefinedType::deserialize_xml(const string &filename, const string &filepath)
    {
        serializing_xml::deserialize_xml(idx, "element_1", filepath);
        serializing_xml::deserialize_xml(name, "element_2", filepath);
        serializing_xml::deserialize_xml(data, "element_3", filepath);
    }
}