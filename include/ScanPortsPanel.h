#ifndef SCANPORTSPANEL_H
#define SCANPORTSPANEL_H
#include <wx/wx.h>
#include <wx/listctrl.h>

class ScanPortsPanel : public wxPanel
{
    public:
    ScanPortsPanel(wxWindow* parent);
    private:
        void BindEvent();
        void StartScan(wxCommandEvent& evt);
        void Export(wxCommandEvent& evt);
        void InsertListPort();
        void SizerList();
};
#endif // SCANPORTSPANEL_H
