//
// Created by admin on 10/18/2025.
//

#ifndef IP_REGION_LOOKUP_IPLOCATOR_H
#define IP_REGION_LOOKUP_IPLOCATOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include <cstdint>

using namespace std;

struct IpInfo{
    string region;
    string service;
    string provider;

    IpInfo(): region(""), service(""),provider(""){}
    IpInfo(string r, string s, string p): region(r), service(s), provider(r){}
};
struct TrieNode {

    IpInfo info;
    bool isEnd = false;
    //binary 0 or 1
    TrieNode* children[2] = {nullptr, nullptr};
};

class IpLocator{
public:
    //constructor function
    IpLocator(const vector<pair<string, IpInfo>>& data);
    IpInfo lookUp(const string& ipAddress) const;

private:
    TrieNode* root;
    void insertCIDR(const string& cidr, const IpInfo& info);
    pair<uint32_t, int> parseCIDR(const string& cidr) const;
    uint32_t ipToBinary(const string& ip) const;
};

#endif //IP_REGION_LOOKUP_IPLOCATOR_H