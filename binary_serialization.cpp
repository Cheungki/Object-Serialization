//
// Created by 张琦 on 2020/6/27.
//

#include "binary_serialization.h"

namespace binarySerialization
{
    void UserDefinedType::serialize(const string &filename)
    {
        serializing_binary::serialize(idx, filename);
        serializing_binary::serialize(name, filename);
        serializing_binary::serialize(data, filename);
    }

    void UserDefinedType::deserialize(const string &filename)
    {
        serializing_binary::deserialize(idx, filename);
        serializing_binary::deserialize(name, filename);
        serializing_binary::deserialize(data, filename);
    }

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