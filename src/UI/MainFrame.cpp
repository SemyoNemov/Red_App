#include "MainFrame.h"
#include "NetworkInterface.h"
#include <ButtonMenu.h>
#include <wx/wx.h>
#include <vector>
#include <string>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
    SetMinSize(wxSize(1000, 600));

    CreateMenu();
    CreateTest();
    SetupSizers();
    BindEvent();
}

void MainFrame::CreateMenu()
{
    menu = new wxPanel(this, wxID_ANY);
    menu->SetBackgroundColour(wxColour(255, 255, 255));

    wxBoxSizer* menuSizer = new wxBoxSizer(wxVERTICAL);

    menuSizer ->AddSpacer(10);
    ButtonMenu* btnMainMenu = new ButtonMenu(menu, wxID_ANY, wxT("Главное меню"));
    ButtonMenu* btnNetInterface = new ButtonMenu(menu, wxID_ANY, wxT("Сетевые интерфейсы"));
    ButtonMenu* btn2 = new ButtonMenu(menu, wxID_ANY, wxT("Раздел 2"));
    ButtonMenu* btn3 = new ButtonMenu(menu, wxID_ANY, wxT("Раздел 3"));

    menuSizer ->Add(btnMainMenu, 0, wxEXPAND);
    menuSizer ->Add(btnNetInterface, 0, wxEXPAND);
    menuSizer ->Add(btn2, 0, wxEXPAND);
    menuSizer ->Add(btn3, 0, wxEXPAND);
    menu-> SetSizer(menuSizer);
    btn2->SetActive(1); //Тест активного раздела
}
void MainFrame::CreateTest()
{
    test = new wxPanel(this, wxID_ANY);
    test -> SetBackgroundColour(wxColour(0, 153, 0));

    wxBoxSizer* testSizer = new wxBoxSizer(wxVERTICAL);

    test-> SetSizer(testSizer);
}

void MainFrame::SetupSizers()
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    mainSizer->Add(menu, 1, wxEXPAND | wxALL, 0);

    wxPanel* separator = new wxPanel(this, wxID_ANY);
    separator->SetMinSize(wxSize(1, -1));
    separator->SetBackgroundColour(wxColour(100, 100, 100));
    mainSizer->Add(separator, 0, wxEXPAND | wxTOP | wxBOTTOM, 0);

    mainSizer->Add(test, 4, wxEXPAND | wxALL, 0);

    SetSizer(mainSizer);
    menu->SetMinSize(wxSize(250, -1));
}

void MainFrame::BindEvent()
{

}
