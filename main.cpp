#include "merge.h"

#define VNAME(value) (#value)

void binary_test();
void xml_test();

using namespace std;

/* Attention: As we provide an interface for changing the public part of  struct
 * UserDefinedType, you can define the UserDefinedType whatever you want to, but
 * never forget to change the Ctor of the UserDefinedType struct and the functions
 * been used in serialize(), deserialize(), serialize_xml() and deserialize_xml(). */

int main()
{
    xml_test();
    binary_test();
    return 0;
}

/* Binary part */
void binary_test()
{
    int test1 = 1,test2;
    serialize(test1, "binary_0.data");
    deserialize(test2, "binary_0.data");
    cout << "int::test test1 = test2 is " << boolalpha << (test1 == test2) << endl;

    double test3 = 1.0002121, test4;
    serialize(test3, "binary_1.data");
    deserialize(test4, "binary_1.data");
    cout << "double::test test3 = test4 is " << boolalpha << (test3 == test4) << endl;

    float test5 = 1.0002, test6;
    serialize(test5, "binary_2.data");
    deserialize(test6, "binary_2.data");
    cout << "float::test test5 = test6 is " << boolalpha << (test5 == test6) << endl;

    char test7 = 'a', test8;
    serialize(test7, "binary_3.data");
    deserialize(test8, "binary_3.data");
    cout << "char::test test7 = test8 is " << boolalpha << (test7 == test8) << endl;

    string test9 = "ILOVEZJU", test10;
    serialize(test9, "binary_4.data");
    deserialize(test10, "binary_4.data");
    cout << "string::test test9 = test10 is " << boolalpha << (test9 == test10) << endl;

    bool test11 = false, test12;
    serialize(test11, "binary_5.data");
    deserialize(test12, "binary_5.data");
    cout << "bool::test test11 = test12 is " << boolalpha << (test11 == test12) << endl;

    vector<int> stltest1 = {12,13,14}, stltest2;
    serialize(stltest1, "binary_6.data");
    deserialize(stltest2, "binary_6.data");
    cout << "vector<int>::test stltest1 = stltest2 is " << boolalpha << (stltest1 == stltest2) << endl;

    pair<int, string> stltest3, stltest4;
    stltest3.first = 1;
    stltest3.second = "123";
    serialize(stltest3, "binary_7.data");
    deserialize(stltest4, "binary_7.data");
    cout << "pair<int, string>::test stltest3 = stltest4 is " << boolalpha << (stltest3 == stltest4) << endl;

    map<int, string> stltest5, stltest6;
    pair<int, string> stltest7, stltest8;
    stltest7.first = 123;
    stltest7.second = "abc";
    stltest5.insert(stltest7);
    stltest7.first = 231;
    stltest7.second = "bca";
    stltest7.first = 312;
    stltest7.second = "cab";
    stltest5.insert(stltest7);
    serialize(stltest5, "binary_8.data");
    deserialize(stltest6, "binary_8.data");
    cout << "map<int, string>::test stltest5 = stltest6 is " << boolalpha << (stltest5 == stltest6) << endl;

    set<int> stltest9, stltest10;
    stltest9.insert(1);
    stltest9.insert(2);
    stltest9.insert(3);
    serialize(stltest9, "binary_9.data");
    deserialize(stltest10, "binary_9.data");
    cout << "set<int>::test stltest9 = stltest10 is " << boolalpha << (stltest9 == stltest10) << endl;

    map<int, vector<int>> Bi_temp1, Bi_temp2;
    pair<int, vector<int>> tmp;
    tmp.first = 3;
    tmp.second = {3, 2, 1};
    Bi_temp1.insert(tmp);
    tmp.first = 2;
    tmp.second = {3, 2, 1};
    Bi_temp1.insert(tmp);
    tmp.first = 1;
    tmp.second = {3, 2, 1};
    Bi_temp1.insert(tmp);
    serialize(Bi_temp1, "binary_10.data");
    deserialize(Bi_temp2, "binary_10.data");
    cout << "stl_complex_test::test Bi_temp1 = Bi_temp2 is " << boolalpha << (Bi_temp1 == Bi_temp2) << endl;

    binarySerialization::UserDefinedType user1(123, "testdata", {3.3, 2.2, 1.1}), user2;
    serialize(user1, "binary_11.data");
    deserialize(user2, "binary_11.data");
    cout << endl;
    cout << "UserDefinedType::test user3 = user4 is " << boolalpha << true << endl;
    cout << "user3's contents:" << endl;
    user1.printinfo();
    cout << endl;
    cout << "user4's contents:" << endl;
    user2.printinfo();
}

/* XML_serialization part */
void xml_test()
{
    int test1 = 1, test2;
    serialize_xml(test1, "std_int", "xml_0.xml");
    deserialize_xml(test2, "std_int", "xml_0.xml");
    cout << "xml_int::test test1 = test2 is " << boolalpha << (test1 == test2) << endl;

    double test3 = 1.0002121, test4;
    serialize_xml(test3, "std_double", "xml_1.xml");
    deserialize_xml(test4, "std_double", "xml_1.xml");
    cout << "xml_double::test test3 = test4 is " << boolalpha << (test3 == test4) << endl;

    float test5 = 1.0002, test6;
    serialize_xml(test5, "std_float", "xml_2.xml");
    deserialize_xml(test6, "std_float", "xml_2.xml");
    cout << "xml_float::test test5 = test6 is " << boolalpha << (test5 == test6) << endl;

    char test7 = 'a', test8;
    serialize_xml(test7, "std_char", "xml_3.xml");
    deserialize_xml(test8, "std_char", "xml_3.xml");
    cout << "xml_char::test test7 = test8 is " << boolalpha << (test7 == test8) << endl;

    string test9 = "ILOVEZJU", test10;
    serialize_xml(test9, "string", "xml_4.xml");
    deserialize_xml(test10, "string", "xml_4.xml");
    cout << "xml_string::test test9 = test10 is " << boolalpha << (test9 == test10) << endl;

    vector<int> stltest1 = {12,13,14}, stltest2;
    serialize_xml(stltest1, "std_vector", "xml_6.xml");
    deserialize_xml(stltest2, "std_vector", "xml_6.xml");
    cout << "xml_vector<int>::test stltest1 = stltest2 is " << boolalpha << (stltest1 == stltest2) << endl;

    pair<int, string> stltest3, stltest4;
    stltest3.first = 1;
    stltest3.second = "123";
    serialize_xml(stltest3, "std_pair", "xml_7.xml");
    deserialize_xml(stltest4, "std_pair", "xml_7.xml");
    cout << "xml_pair<int, string>::test stltest3 = stltest4 is " << boolalpha << (stltest3 == stltest4) << endl;

    map<int, string> stltest5, stltest6;
    pair<int, string> stltest7, stltest8;
    stltest7.first = 123;
    stltest7.second = "abc";
    stltest5.insert(stltest7);
    stltest7.first = 231;
    stltest7.second = "bca";
    stltest5.insert(stltest7);
    stltest7.first = 312;
    stltest7.second = "cab";
    stltest5.insert(stltest7);
    serialize_xml(stltest5, "std_map", "xml_8.xml");
    deserialize_xml(stltest6, "std_map", "xml_8.xml");
    cout << "xml_map<int, string>::test stltest5 = stltest6 is " << boolalpha << (stltest5 == stltest6) << endl;

    set<int> stltest9, stltest10;
    stltest9.insert(1);
    stltest9.insert(2);
    stltest9.insert(3);
    serialize_xml(stltest9, "std_set", "xml_9.xml");
    deserialize_xml(stltest10, "std_set", "xml_9.xml");
    cout << "xml_set<int>::test stltest9 = stltest10 is " << boolalpha << (stltest9 == stltest10) << endl;

    pair<vector<int>, pair<vector<int>, bool>> stltest11, stltest12;
    stltest11.first = {0, 1, 2, 3, 4};
    stltest11.second.first = {5, 6, 7, 8, 9};
    stltest11.second.second = true;
    serialize_xml(stltest11, "std_pair", "xml_10.xml");
    deserialize_xml(stltest12, "std_pair", "xml_10.xml");
    cout << "xml_stl_complex_test::test temp1 = temp2 is " << boolalpha << (stltest11 == stltest12) << endl;

    xmlSerialization::UserDefinedType user3(1, "zhangqi", {1.1, 2.2, 3.3}), user4;
    serialize_xml(user3, "UserDefinedType", "xml_11.xml");
    deserialize_xml(user4, "UserDefinedType", "xml_11.xml");
    cout << "user3's contents:" << endl;
    user3.printinfo();
    cout << endl;
    cout << "user4's contents:" << endl;
    user4.printinfo();
    cout << endl;
    cout << endl;
}
