#include <iostream>
#include <vector>
#include <string>
#include "tinyxml2.h"
#include "xml_serialization.h"

using namespace std;

int main()
{
    string temp = "hello world";
    serialize_xml(temp, "Test", "../test.xml");
    return 0;
}
