#ifndef NETWORKINTERFACEPANEL_H
#define NETWORKINTERFACEPANEL_H
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include "NetworkInterface.h"

class NetworkInterfacePanel : public wxPanel
{
    public:
    NetworkInterfacePanel(wxWindow* parent);
    private:
        wxListCtrl* listInterfaces;
        wxButton* startScan;
        wxButton* btnExport;
        void BindEvent();
        void StartScan(wxCommandEvent& evt);
        void Export(wxCommandEvent& evt);
        void InsertListInterface(const std::vector<NetworkInterface>& interfaces);
        void SizerList();
};

#endif // NETWORKINTERFACEPANEL_H
