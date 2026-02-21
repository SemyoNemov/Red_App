#include "SettingsPanel.h"
#include "MyFonts.h"
#include <wx/wx.h>

SettingsPanel::SettingsPanel(wxWindow* parent) : wxPanel(parent)
{
    SetBackgroundColour(wxColour(250, 250, 250));
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* text = new wxStaticText(this, wxID_ANY, wxT("Настройки.\n(в разработке)"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    text->SetFont(MF::GetTitleFont());
    panelSizer->Add(text, wxSizerFlags().Center().Border(wxTOP, 200));

    this-> SetSizer(panelSizer);
}
