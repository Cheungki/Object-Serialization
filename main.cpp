#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "xml_serialization.h"
#include "xml_deserialization.h"

using namespace std;

int main()
{
    pair<vector<int>, pair<vector<int>, double>> temp1, temp2;
    temp1.first = {0, 1, 2, 3, 4};
    temp1.second.first = {5, 6, 7, 8, 9};
    temp1.second.second = 2.33;
    serializing_xml t1;
    t1.serialize_xml(temp1, "std_pair", "../test.xml");
    deserializing_xml t2;
    t2.deserialize_xml(temp2, "std_pair", "../test.xml");
    cout << boolalpha << (temp1 == temp2) << endl;
    return 0;
}
