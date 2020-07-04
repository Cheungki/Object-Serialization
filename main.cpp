#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>
#include <utility>
#include "merge.h"

#define VNAME(value) (#value)

using namespace std;

int main()
{
    /* XML Part */
    pair<vector<int>, pair<vector<int>, bool>> temp1, temp2;
    xmlSerialization::UserDefinedType user1(1, "zhangqi", {1.1, 2.2, 3.3}), user2;
    temp1.first = {0, 1, 2, 3, 4};
    temp1.second.first = {5, 6, 7, 8, 9};
    temp1.second.second = true;

    serialize_xml(temp1, "std_pair", "../test1.xml");
    deserialize_xml(temp2, "std_pair", "../test1.xml");

    serialize_xml(user1, "UserDefinedType", "../test2.xml");
    deserialize_xml(user2, "UserDefinedType", "../test2.xml");

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
    serialize(temp3, "../n.data");
    deserialize(temp4, "../n.data");
    binarySerialization::UserDefinedType user3(123, "zhangqiiii", {3.3, 2.2, 1.1}), user4;
    serialize(user3, "../udt.data");
    deserialize(user4, "../udt.data");
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
