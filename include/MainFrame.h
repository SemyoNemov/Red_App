#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <wx/wx.h>


class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    void CreateMenu();
    void CreateTest();
    void SetupSizers();
    void BindEvent();
    wxPanel* menu;
    wxPanel* test;
};

#endif // MAINFRAME_H

