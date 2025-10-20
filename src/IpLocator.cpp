//
// Created by admin on 10/18/2025.
//
#include "IpLocator.h"
#include <sstream>

IpLocator::IpLocator(const vector<pair<string, string>>& data): root(new TrieNode){

}

string IpLocator::lookUp(const string& ipAddress) const{

}

void IpLocator::insertCIDR(const string& cidr, const string& region){

}

pair<uint32_t, int> IpLocator::parseCIDR(const string& cidr) const{

}

uint32_t IpLocator::ipToBinary(const string& ip) const{
    vector<int> octets;
    stringstream ss(ip);
    string token;

    while (getline(ss, token, '.')){
        octets.push_back(stoi(token));
    }

    uint32_t result = 0;
    for(int i=0; i<4; i++){
        result = (result << 8) + octets[i];
    }
    return result;
}