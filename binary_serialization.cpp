//
// Created by 张琦 on 2020/6/27.
//

#include "binary_serialization.h"

namespace binarySerialization
{
    /* Function:UserDefinedType::serialize(const string &filename)
     * Description: construct serialize for UserDefinedType*/
    void UserDefinedType::serialize(const string &filename)
    {
        serializing_binary::serialize(idx, filename);
        serializing_binary::serialize(name, filename);
        serializing_binary::serialize(data, filename);
    }

    /* Function: UserDefinedType::serialize(const string &filename)
     * Description: Construct deserialize for UserDefinedType*/
    void UserDefinedType::deserialize(const string &filename)
    {
        serializing_binary::deserialize(idx, filename);
        serializing_binary::deserialize(name, filename);
        serializing_binary::deserialize(data, filename);
    }

    /* Function: UserDefinedType::printinfo()
     * Description: Print the informaiton of the UserDefinedType. */
    void UserDefinedType::printinfo()
    {
        cout << "idx = " << idx << endl;
        cout << "name = " << name << endl;
        int i;
        cout << "data = {";
        for (i = 0; i < data.size(); i++) {
            cout << data[i];
            if(i != data.size() - 1) cout << ", ";
            else cout << "}" << endl;
        }
    }
}