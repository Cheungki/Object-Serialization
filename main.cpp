#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "xml_serialization.h"

#define VNAME(value) (#value)

using namespace std;

int main()
{
    pair<vector<int>, pair<vector<int>, double>> temp1, temp2;
    temp1.first = {0, 1, 2, 3, 4};
    temp1.second.first = {5, 6, 7, 8, 9};
    temp1.second.second = 2.33;
    serialize_xml::serializing_xml t;
    t.serialize_xml(temp1, "std_pair", "../test2.xml", VNAME(temp1));
    t.deserialize_xml(temp2, "std_pair", "../test2.xml");
    cout << boolalpha << (temp1 == temp2) << endl;
    serialize_xml::UserDefinedType user(1, "zhangqi", temp1);
    user.serialize_xml("../test.xml");
    serialize_xml::UserDefinedType user_copy;
    user_copy.deserialize_xml("../test.xml");
    return 0;
}
