#include "MainMenuPanel.h"
#include "MyFonts.h"
#include <wx/wx.h>

MainMenuPanel::MainMenuPanel(wxWindow* parent) : wxPanel(parent)
{
    SetBackgroundColour(wxColour(200, 200, 200));
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* text = new wxStaticText(this, wxID_ANY, wxT("Главное меню.\n(в разработке)"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE_HORIZONTAL);
    text->SetFont(MF::GetTitleFont());
    panelSizer->Add(text, wxSizerFlags().Center().Border(wxALL, 200));

    this-> SetSizer(panelSizer);
}


void MainMenuPanel::BindEvent()
{

}

