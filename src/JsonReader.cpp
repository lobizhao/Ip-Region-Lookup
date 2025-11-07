//
// Created by admin on 10/18/2025.
//
#include "JsonReader.h"
#include <fstream>
#include "../external/nlohmann/json.hpp"

/*
 * Json file reader
 * nlohmann third package for json type
 * get ip-prefix(CIDR) and region(support from cloud service) from json
*/

using json = nlohmann::json;

vector<pair<string, IpInfo>> JsonReader::loadAWS(const std::string &filePath) {
    vector<pair<string, IpInfo>> result;

    ifstream file(filePath);
    if(!file.is_open()){
        cerr << "Error: failed to open file" << filePath << endl;
        return {};
    }
    json data;
    file >> data;

    for(auto& prefix: data["prefixes"]){
        string cidr = prefix["ip-prefix"];
        IpInfo info;
        info.region = prefix["region"];
        info.service = prefix["service"];
        info.provider = "AWS";

        result.push_back({cidr, info});
    }
    return result;
}

vector<pair<string, IpInfo>> JsonReader::loadGCP(const std::string &filePath) {

}

vector<pair<string, IpInfo>> JsonReader::loadFromFiles(const vector<string>& files){
    vector<pair<string, IpInfo>> allData;
    //input file stream
    for(const auto& filePath: files){
        vector<pair<string, IpInfo>> fileData;
        if(filePath.find("ip-ranges.json") != string::npos){
            fileData = loadAWS(filePath);
        }else if(filePath.find("cloud.json") != string::npos){
            fileData = loadGCP(filePath);
        }
        allData.insert(allData.end(), fileData.begin(), fileData.end());
    }
    return allData;
}