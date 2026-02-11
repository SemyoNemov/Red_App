#include "ScanPortsPanel.h"
#include "MyFonts.h"
#include <wx/wx.h>
#include <wx/listctrl.h>

ScanPortsPanel::ScanPortsPanel(wxWindow* parent) : wxPanel(parent)
{
    SetBackgroundColour(wxColour(200, 200, 200));
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* text = new wxStaticText(this, wxID_ANY, wxT("Сканер открытых портов.\n(в разработке)"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    text->SetFont(MF::GetTitleFont());
    panelSizer->Add(text, wxSizerFlags().Center().Border(wxTOP, 200));

    this-> SetSizer(panelSizer);
}

void ScanPortsPanel::BindEvent()
{

}

void ScanPortsPanel::StartScan(wxCommandEvent& evt)
{

}

void ScanPortsPanel::Export(wxCommandEvent& evt)
{

}

void ScanPortsPanel::InsertListPort()
{

}

void SizerList()
{

}
