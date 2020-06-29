#include <iostream>
#include <vector>
#include <string>
#include <cxxabi.h>
#include "tinyxml2.h"
#include "xml_serialization.h"
#include "convert_to_char.h"
#include "xml_deserialization.h"

using namespace std;

int main()
{
    pair<vector<int>, pair<vector<int>, double>> temp;
    deserializing_xml t;
    t.deserialize_xml(temp, "std_pair", "../test.xml");
    return 0;
}
