#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H
#include <vector>
#include <string>
struct NetworkInterface
{
    int index;
    std::string name;
    std::string type;
    std::string mac_address;
    bool on;
    std::string ip;
};
std::vector<NetworkInterface> scanNetworkInterface();

#endif
