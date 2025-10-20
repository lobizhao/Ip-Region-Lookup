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

class IpLocator{
public:
    //constructor function
    IpLocator(const vector<pair<string, string>>& data);

    string lookUp(const string& ipAddress) const;

private:
    struct TrieNode {
        string region;
        bool isEnd = false;
        //binary 0 or 1
        TrieNode* children[2] = {nullptr, nullptr};
    };
    TrieNode* root;

    void insertCIDR(const string& cidr, const string& region);
    pair<uint32_t, int> parseCIDR(const string& cidr) const;
    uint32_t ipToBinary(const string& ip) const;
};

#endif //IP_REGION_LOOKUP_IPLOCATOR_H