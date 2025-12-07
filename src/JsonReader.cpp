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
        if(prefix.contains("ip_prefix") && !prefix["ip_prefix"].is_null()){
            string cidr = prefix["ip_prefix"];
            IpInfo info;
            info.region = prefix.contains("region") && !prefix["region"].is_null() ? prefix["region"].get<string>() : "";
            info.service = prefix.contains("service") && !prefix["service"].is_null() ? prefix["service"].get<string>() : "";
            info.provider = "AWS";

            result.emplace_back(cidr, info);
        }
    }
    return result;
}

vector<pair<string, IpInfo>> JsonReader::loadGCP(const std::string &filePath) {
    vector<pair<string, IpInfo>> result;

    ifstream file(filePath);
    if(!file.is_open()){
        cerr <<"Error: Failed to open file" << endl;
        return {};
    }
    json data;
    file >> data;

    for(auto& prefix: data["prefixes"]){
        if(prefix.contains("ipv4Prefix") && !prefix["ipv4Prefix"].is_null()){
            string cidr = prefix["ipv4Prefix"];
            IpInfo info;
            info.region = prefix.contains("scope") && !prefix["scope"].is_null() ? prefix["scope"].get<string>() : "";
            info.service = prefix.contains("service") && !prefix["service"].is_null() ? prefix["service"].get<string>() : "";
            info.provider = "GCP";
            result.emplace_back(cidr, info);
        }
    }
    return result;

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