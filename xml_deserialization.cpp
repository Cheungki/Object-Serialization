//
// Created by 张琦 on 2020/6/29.
//

#include "xml_deserialization.h"

void deserializing_xml::read(tinyxml2::XMLElement *&node, std::vector<const char *> &v, std::vector<int> &pos)
{
    if(node == nullptr) return;
    else {
        const tinyxml2::XMLAttribute *attribute = node->FirstAttribute();
        const char *content = nullptr;
        if(attribute != nullptr) content = attribute->Value();
        if(content != nullptr) {
            v.push_back(content);
            tinyxml2::XMLElement *sibnode = node->NextSiblingElement();
            read(sibnode, v, pos);
        }
        else {
            tinyxml2::XMLElement *subnode = node->FirstChildElement();
            read(subnode, v, pos);
            pos.push_back(v.size());
            if(node->NextSiblingElement() != nullptr) {
                tinyxml2::XMLElement *sibnode = node->NextSiblingElement();
                read(sibnode, v, pos);
            }
        }
    }
}