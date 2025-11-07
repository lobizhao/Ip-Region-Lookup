#include <iostream>
#include "src/IpLocator.h"
#include "src/JsonReader.h"

int main() {
    auto data = JsonReader::loadFromFiles({
        "data/ip-ranges.json",
        "data/cloud.json"
    });

    IpLocator locator(data);

    IpInfo info = locator.lookUp("34.80.1.1");
    return;
}
