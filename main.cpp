#include <iostream>
#include <vector>
#include <string>
#include "tinyxml2.h"

using namespace std;

int main()
{
    tinyxml2::XMLDocument docXml;
    tinyxml2::XMLError errXml = docXml.LoadFile("../example.xml");
    if (tinyxml2::XML_SUCCESS == errXml)
    {
        tinyxml2::XMLElement* elmtRoot = docXml.RootElement();
        tinyxml2::XMLElement *elmtUser = elmtRoot->FirstChildElement("User");
        tinyxml2::XMLElement *elmtName = elmtUser->FirstChildElement("Name");
        if (elmtName)
        {
            const char* pContent= elmtName->GetText();
            printf( "%s", pContent);
        }
        tinyxml2::XMLElement *elmtAge = elmtName->NextSiblingElement();
        if (elmtAge)
        {
            const char* pContent= elmtAge->GetText();
            printf( "%s", pContent);
        }
    }
    return 0;
}
