#include <iostream>
#include <vector>
#include <string>
#include <cxxabi.h>
#include "tinyxml2.h"
#include "xml_serialization.h"
#include "convert_to_char.h"

using namespace std;

int main()
{
    map<int, string> temp;
    temp.insert(pair<int, string>(1, "student_one"));
    temp.insert(pair<int, string>(2, "student_two"));
    temp.insert(pair<int, string>(3, "student_three"));
    document doc;
    doc.serialize_xml(temp, "std_map", "../test.xml");
    return 0;
}
