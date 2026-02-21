#include "Ports.h"
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

static string Cmd(const string& command) {
    char buff[128];
    string out;

    FILE* pipe = popen(command.c_str(), "r");
    if (!pipe) return "Ошибка выполнения команды!";

    while (fgets(buff, sizeof(buff), pipe)!=nullptr) {out+=buff;}

    pclose(pipe);
    return out;
}

vector<Port> scanPortrs()
{
    string input = Cmd("ss -tunp4 state all | grep -E 'LISTEN|ESTAB'");
    vector<Port> ports;
    istringstream inputS(input);
    string line;

    while (getline(inputS, line)) {
        if (line.empty()) continue;

        istringstream ss(line);
        Port port;

        string skip, localAddress, remoteAddress, user;

        ss >> port.protocol >> port.status >> skip >> skip >> localAddress >> remoteAddress;

        auto pos = localAddress.find(':');
       if (localAddress.find('%')!=string::npos) {
            port.localIP = localAddress.substr(0, localAddress.find('%'));
            port.localPort = localAddress.substr(pos + 1);
        }
        else {
        port.localIP = localAddress.substr(0, pos);
        port.localPort = localAddress.substr(pos + 1);
        }

        pos = remoteAddress.find(':');
        port.remoteIP = remoteAddress.substr(0, pos);
        port.remotePort = remoteAddress.substr(pos + 1);


        std::getline(ss, user);

        port.name = "Требуются права суперпользователя.";
        port.pid = -1;

        if (user.find("users:")!= string::npos) {

            auto nameStart = user.find("\"");
            auto nameEnd = user.find("\"", nameStart + 1);

            if (nameStart != string::npos && nameEnd != string::npos) {
                port.name = user.substr(nameStart+1, nameEnd - nameStart-1);
            }

            auto pidStart = user.find("pid=");
            if (pidStart != string::npos) {
                auto pidEnd = user.find(",", pidStart);
                string pidStr = user.substr(pidStart+4, pidEnd - pidStart-4);
                port.pid = std::stoi(pidStr);
            }
        }
        ports.push_back(port);

        sort(ports.begin(), ports.end(), [](const Port& a, const Port& b) {
            return a.name < b.name;
        });
}
return ports;
}
