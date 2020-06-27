#include <iostream>
#include <vector>
#include <string>
#include "tinyxml2.h"
#include "xml_serialization.h"

using namespace std;

int main()
{
    int temp = 10;
    serialize_xml(temp, "Test", "../Int.xml");
    return 0;
}
