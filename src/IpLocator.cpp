//
// Created by admin on 10/18/2025.
//
#include "IpLocator.h"
#include <sstream>

IpLocator::IpLocator(const vector<pair<string, IpInfo>>& data): root(new TrieNode){
    //build trie tree
    for(const auto & entry : data){
        insertCIDR(entry.first, entry.second);
    }
}

//run lookup function
IpInfo IpLocator::lookUp(const string& ipAddress) const{
    uint32_t address = ipToBinary(ipAddress);
    TrieNode* current = root;
    IpInfo regionMatch;

    for(int i=0; i<32; i++){
        if(current->isEnd){
            regionMatch = current->info;
        }
        uint32_t bit = (address >> (31-i)) & 1;
        if(current->children[bit] == nullptr){
            break;
        }
        current = current->children[bit];
    }
    if(current->isEnd){
        regionMatch = current->info;
    }
    return regionMatch;
}

//insert CIDR into trie tree
void IpLocator::insertCIDR(const string& cidr, const IpInfo& info){
    //get uint32 ip address and prefix length
    pair<uint32_t, int> parseInfo = parseCIDR(cidr);
    uint32_t address = parseInfo.first;
    int prefixLength = parseInfo.second;

    TrieNode* sourceNode = root;

    for(int i=0; i< prefixLength; i++){
        uint32_t bit = (address >>(31-i)) & 1;
        if(sourceNode->children[bit] == nullptr){
            sourceNode->children[bit] = new TrieNode();
        }
        sourceNode = sourceNode->children[bit];
    }
    sourceNode->isEnd = true;
    sourceNode->info = info;
}

//split CIDR into base ip and prefix length
pair<uint32_t, int> IpLocator::parseCIDR(const string& cidr) const{

    pair<uint32_t, int> result;
    size_t splitPos = cidr.find('/');

    string ipAddress = cidr.substr(0,splitPos);
    int prefixLength = stoi(cidr.substr(splitPos+1));

    result.first = ipToBinary(ipAddress);
    result.second = prefixLength;
    return result;
}

//basic function
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