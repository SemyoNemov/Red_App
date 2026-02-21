#ifndef SCANPORTSPANEL_H
#define SCANPORTSPANEL_H
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <Ports.h>

class ScanPortsPanel : public wxPanel
{
    public:
    ScanPortsPanel(wxWindow* parent);
    private:
        wxListCtrl* listInterfaces;
        wxButton* startScan;
        wxButton* btnExport;
        void BindEvent();
        void StartScan(wxCommandEvent& evt);
        void Export(wxCommandEvent& evt);
        void InsertListPort(const std::vector<Port>& ports);
        void SizerList();
};
#endif // SCANPORTSPANEL_H
