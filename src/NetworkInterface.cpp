#include "NetworkInterface.h"
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;
string Cmd(const string& command) {
    char buff[128];
    string out;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) return "Ошибка выполнения команды!";

    while (fgets(buff, sizeof(buff), pipe)!=nullptr) {out+=buff;}

    pclose(pipe);
    return out;
}

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

        string type = Cmd("nmcli -t -f  DEVICE,TYPE dev | grep -i \"^"+interface.name+"\"");
        interface.type= type.substr(type.find(":")+1);

        string ip =Cmd("ip -4 -br a s "+interface.name);
        interface.ip=ip.substr((ip.rfind("   "))+3);

        interfaces.push_back(interface);
    }
    return interfaces;
}
