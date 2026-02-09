#ifndef MAINMENUPANEL_H
#define MAINMENUPANEL_H
#include <wx/wx.h>

class MainMenuPanel : public wxPanel
{
    public:
    MainMenuPanel(wxWindow* parent);
    private:
        void BindEvent();
};

#endif // MAINMENUPANEL_H
