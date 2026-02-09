#include "MainFrame.h"
#include "NetworkInterface.h"
#include "ButtonMenu.h"
#include "Ids.h"
#include <wx/wx.h>
#include "MainMenuPanel.h"
#include "NetworkInterfacePanel.h"
#include <vector>
#include <string>
#include <map>


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    SetMinSize(wxSize(1000, 600));

    CreateMenu();
    CreateSections();
    SetupSizers();
    BindEvent();
}

void MainFrame::CreateMenu()
{
    menu = new wxPanel(this, wxID_ANY);
    menu->SetBackgroundColour(wxColour(255, 255, 255));

    wxBoxSizer* menuSizer = new wxBoxSizer(wxVERTICAL);

    menuSizer ->AddSpacer(10);
    ButtonMenu* btnMainMenu = new ButtonMenu(menu, ID_MAIN, wxT("Главное меню"));
    ButtonMenu* btnNetInterface = new ButtonMenu(menu, ID_NET, wxT("Сетевые интерфейсы"));
    menuButtons = {btnMainMenu, btnNetInterface};

    for (auto* btn : menuButtons) {menuSizer->Add(btn, 0, wxEXPAND);}
    menu-> SetSizer(menuSizer);
    btnMainMenu->SetActive(1);
}
void MainFrame::CreateSections()
{
    content = new wxPanel(this, wxID_ANY);
    wxBoxSizer* contentSizer = new wxBoxSizer(wxVERTICAL);
    content->SetSizer(contentSizer);

    sections[ID_MAIN] = new MainMenuPanel(content);
    sections[ID_NET] = new NetworkInterfacePanel(content);

    for (auto& [id, panel] : sections)
    {
        contentSizer->Add(panel, 1, wxEXPAND);
        panel->Hide();
    }

    SwitchSection(ID_MAIN);

}

void MainFrame::SetupSizers()
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    mainSizer->Add(menu, 1, wxEXPAND | wxALL, 0);

    wxPanel* separator = new wxPanel(this, wxID_ANY);
    separator->SetMinSize(wxSize(1, -1));
    separator->SetBackgroundColour(wxColour(100, 100, 100));
    mainSizer->Add(separator, 0, wxEXPAND | wxTOP | wxBOTTOM, 0);

    mainSizer->Add(content, 4, wxEXPAND | wxALL, 0);

    SetSizer(mainSizer);
    menu->SetMinSize(wxSize(250, -1));
    Layout();
}

void MainFrame::SwitchSection(int id)
{
    if (currentSection) {currentSection->Hide();}

    auto it = sections.find(id);
    if (it==sections.end()) {return;}

    currentSection = it->second;
    currentSection -> Show();

    content->Layout();
}
void MainFrame::MenuClick(wxCommandEvent& evt)
{
    int id = evt.GetId();
    SwitchSection(id);
    MenuButtonStatus(id);
}

void MainFrame::MenuButtonStatus(int id)
{
       for (auto* btn : menuButtons) {btn->SetActive(btn->GetId() == id);}
}

void MainFrame::BindEvent()
{
   for (auto* btn : menuButtons) {btn->Bind(wxEVT_BUTTON, &MainFrame::MenuClick, this);}
}
