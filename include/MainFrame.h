#ifndef MAINFRAME_H
#define MAINFRAME_H
#include <wx/wx.h>


class MainFrame : public wxFrame
{
public:
    MainFrame(const wxString& title);

private:
    wxPanel* panel;
};

#endif // MAINFRAME_H

