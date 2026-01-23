#include "NetworkInterface.h"
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
using namespace std;
namespace fs = std::filesystem;
vector<NetworkInterface> scanNetworkInterface()
{
    vector<NetworkInterface> interfaces;
    NetworkInterface interface;

    for(const auto& dir : fs::directory_iterator("/sys/class/net/")){
        if (!dir.is_directory()) continue;

        interface.name = dir.path().filename().string();
        ifstream mac_file(dir.path() / "address");
        if (mac_file) {getline(mac_file, interface.mac_address);}//запись mac адреса
        string stat_temp;
        if (ifstream status_file(dir.path() / "operstate");
        getline(status_file, stat_temp)) {
        interface.on = (stat_temp == "up") ? true : false;
        }
        ifstream index_file(dir.path() / "ifindex");
        if (index_file) {index_file>>interface.index;}
        fstream mtu_file(dir.path() / "mtu");
        if (mtu_file) {mtu_file>>interface.mtu;}
        fstream devtype(dir.path() / "uevent");
        if (devtype) {
            string x((std::istreambuf_iterator<char>(devtype)),
            std::istreambuf_iterator<char>());
            if (x.find("DEVTYPE=")!=string::npos){
                interface.type=x.substr(x.find("DEVTYPE=")+8, x.find('\n', x.find("DEVTYPE=")+8)-8);;
            }

        }
    }
}
int main()
{
    vector<NetworkInterface> scan=scanNetworkInterface();
    cout<<scan[0].type;
return 0;
}
