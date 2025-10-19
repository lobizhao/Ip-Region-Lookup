//
// Created by admin on 10/18/2025.
//

#ifndef IP_REGION_LOOKUP_JSONREADER_H
#define IP_REGION_LOOKUP_JSONREADER_H

#include <fstream>
#include <iostream>

#include <string>
#include <vector>

using namespace std;

class JsonReader{
public:
    vector<pair<string, string>> jsonRead(const string& filePath);
};

#endif //IP_REGION_LOOKUP_JSONREADER_H
