#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "xml_serialization.h"

using namespace std;

//struct User {
//    string idx;
//    std::string name;
//    std::vector<double> data;
//    User(string element1, string element2, vector<double> element3) : idx(element1), name(element2), data(element3){};
//};

int main()
{
//    pair<vector<int>, pair<vector<int>, double>> temp1, temp2;
//    temp1.first = {0, 1, 2, 3, 4};
//    temp1.second.first = {5, 6, 7, 8, 9};
//    temp1.second.second = 2.33;
//    serialize_xml::serializing_xml t1;
//    t1.serialize_xml(temp1, "std_pair", "../test.xml");
//    serialize_xml::deserializing_xml t2;
//    t2.deserialize_xml(temp2, "test", "../test.xml");
//    cout << boolalpha << (temp1 == temp2) << endl;
    serialize_xml::UserDefinedType user(1, "zhangqi", {1.1, 2.2});
    user.serialize_xml("../test.xml");
    serialize_xml::UserDefinedType user_copy;
    user_copy.deserialize_xml("../test.xml");
    return 0;
}
