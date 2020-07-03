#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include "xml_serialization.h"
#include "binary_serialization.h"

#define VNAME(value) (#value)

using namespace std;

int main()
{
    /* XML Part */
    pair<vector<int>, pair<vector<int>, double>> temp1, temp2;
    temp1.first = {0, 1, 2, 3, 4};
    temp1.second.first = {5, 6, 7, 8, 9};
    temp1.second.second = 2.33;
    xmlSerialization::serializing_xml t1;
    t1.serialize_xml(temp1, "std_pair", "../test1.xml", VNAME(temp1));
    t1.deserialize_xml(temp2, "std_pair", "../test1.xml");
    xmlSerialization::UserDefinedType user1(1, "zhangqi", {1.1, 2.2, 3.3});
    user1.serialize_xml("../test2.xml");
    xmlSerialization::UserDefinedType user2;
    user2.deserialize_xml("../test2.xml");
    cout << "temp1 = temp2 is " << boolalpha << (temp1 == temp2) << endl;
    cout << endl;
    cout << endl;
    cout << "user's contents:" << endl;
    user1.printinfo();
    cout << endl;
    cout << "user2's contents:" << endl;
    user2.printinfo();
    cout << endl;
    cout << endl;

    /* Binary Part */
    binarySerialization::serializing_binary t2;
    map<int, vector<int>> temp3, temp4;
    pair<int, vector<int>> tmp;
    tmp.first = 3;
    tmp.second = {3, 2, 1};
    temp3.insert(tmp);
    tmp.first = 2;
    tmp.second = {2, 1, 3};
    temp3.insert(tmp);
    tmp.first = 1;
    tmp.second = {1, 3, 2};
    temp3.insert(tmp);
    t2.serialize(temp3, "../n.data");
    t2.deserialize(temp4, "../n.data");
    binarySerialization::UserDefinedType user3(123, "zhangqiiii", {3.3, 2.2, 1.1}), user4;
    user3.serialize("../udt.data");
    user4.deserialize("../udt.data");
    cout << "temp3 = temp4 is " << boolalpha << (temp3 == temp4) << endl;
    cout << endl;
    cout << endl;
    cout << "user4's contents:" << endl;
    user3.printinfo();
    cout << endl;
    cout << "user4's contents:" << endl;
    user4.printinfo();

    return 0;
}
