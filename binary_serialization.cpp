//
// Created by 张琦 on 2020/6/27.
//

#include "binary_serialization.h"

namespace binarySerialization
{
    /* Function:UserDefinedType::serialize(const string &filepath)
     * Description: construct serialize for UserDefinedType*/
    void UserDefinedType::serialize(const string &filepath)
    {
        serializing_binary::serialize(idx, filepath);
        serializing_binary::serialize(name, filepath);
        serializing_binary::serialize(data, filepath);
    }

    /* Function: UserDefinedType::serialize(const string &filepath)
     * Description: Construct deserialize for UserDefinedType*/
    void UserDefinedType::deserialize(const string &filepath)
    {
        serializing_binary::deserialize(idx, filepath);
        serializing_binary::deserialize(name, filepath);
        serializing_binary::deserialize(data, filepath);
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