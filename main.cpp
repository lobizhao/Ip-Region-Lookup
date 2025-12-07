#include <iostream>
#include "src/IpLocator.h"
#include "src/JsonReader.h"

int main() {
    auto data = JsonReader::loadFromFiles({
        "../data/ip-ranges.json",
        "../data/cloud.json"
    });

    cout << "Loaded " << data.size() << " IP ranges" << endl;

    for(const auto& entry : data) {
        if(entry.first == "52.93.178.158/32") {
            cout << "Found 52.93.178.158/32 - Region: " << entry.second.region << endl;
        }
    }

    IpLocator locator(data);

    vector<string> testIps = {
        "35.220.27.1",       // GCP asia-east2
        "15.230.15.29",        // AWS
        "34.157.254.1",           // Google Public DNS
        "40.65.72.174"        // Private IP
    };

    cout << "IP Region Lookup Test Results:\n" << string(50, '=') << endl;

    for(const auto& ip : testIps) {
        IpInfo info = locator.lookUp(ip);
        cout << "\nIP: " << ip << endl;
        cout << "  Provider: " << (info.provider.empty() ? "Unknown" : info.provider) << endl;
        cout << "  Region: " << (info.region.empty() ? "Unknown" : info.region) << endl;
        cout << "  Service: " << (info.service.empty() ? "Unknown" : info.service) << endl;
    }

    cout << "\n" << string(50, '=') << endl;
    return 0;
}
