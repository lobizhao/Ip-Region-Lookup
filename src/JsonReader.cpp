//
// Created by admin on 10/18/2025.
//
#include "JsonReader.h"
#include <fstream>
#include "../external/nlohmann/json.hpp"

using json = nlohmann::json;

vector<pair<string, string>> jsonRead(const string& filePath){

    //input file stream
    ifstream file(filePath);
    if(!file.is_open()){
        cerr<<"Error, failed to open file" << filePath << endl;
        return {};
    }

    json baseData;
    //get file contain to baseData
    file >> baseData;

    vector<pair<string, string>> result;

    for(const auto& item: baseData){
        string cidr = item["ip_prefix"];
        string region = item["region"];

        result.emplace_back(cidr, region);
    }
    return result;
}