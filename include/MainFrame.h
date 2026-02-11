#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <wx/wx.h>
#include "ButtonMenu.h"
#include <map>
#include <vector>
class ButtonMenu;
class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    void CreateMenu();
    void CreateSections();
    void SetupSizers();
    void SwitchSection(int id);
    void MenuButtonStatus(int id);
    void MenuClick(wxCommandEvent& evt);
    void BindEvent();
    wxPanel* menu = nullptr;
    wxCheckBox* rootCheckBox;
    wxPanel* content= nullptr;
    std::map<int, wxPanel*> sections;
    wxPanel* currentSection= nullptr;
    std::vector<ButtonMenu*> menuButtons;

};

#endif // MAINFRAME_H

