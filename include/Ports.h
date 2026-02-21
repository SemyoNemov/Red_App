#ifndef PORTS_H
#define PORTS_H
#include <vector>
#include <string>
struct Port
{
    std::string protocol=" ";
    std::string status=" ";
    std::string localIP=" ";
    std::string localPort=" ";
    std::string remoteIP=" ";
    std::string remotePort=" ";
    std::string name=" ";
    int pid=-1;
};
std::vector<Port> scanPortrs();
#endif // PORTS_H
