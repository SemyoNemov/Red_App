#include "NetworkInterface.h"
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
std::vector<NetworkInterface> scanNetworkInterface()
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
    }
}
