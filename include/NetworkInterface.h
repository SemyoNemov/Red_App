#ifndef NETWORKINTERFACE_H
#define NETWORKINTERFACE_H
#include <vector>
#include <string>
struct NetworkInterface
{
    int index=000;
    std::string name="Unknown name";
    std::string type="Unknown type";
    std::string mac_address="No mac address";
    bool on=0;
    std::string ip=" ";
};
std::vector<NetworkInterface> scanNetworkInterface();
#endif
