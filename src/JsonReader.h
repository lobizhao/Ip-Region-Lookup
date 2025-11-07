//
// Created by admin on 10/18/2025.
//

#ifndef IP_REGION_LOOKUP_JSONREADER_H
#define IP_REGION_LOOKUP_JSONREADER_H

#include <fstream>
#include <iostream>

#include <string>
#include <vector>
#include "IpLocator.h"

using namespace std;

class JsonReader{
public:
    static vector<pair<string, IpInfo>> loadFromFiles(const vector<string>& files);
private:
    static vector<pair<string, IpInfo>> loadAWS(const string& filePath);
    static vector<pair<string, IpInfo>> loadGCP(const string& filePath);
};

#endif //IP_REGION_LOOKUP_JSONREADER_H
