// ButtonMenu.h
#ifndef BUTTONMENU_H
#define BUTTONMENU_H
#include <wx/wx.h>

class ButtonMenu : public wxPanel
{
public:
    ButtonMenu(wxWindow* parent,
               wxWindowID id,
               const wxString& label);

    void SetActive(bool active);

private:
    void UpdateColors();
    void RebuildLines(int width);
    void UpdateMinHeight(int width);

    void OnPaint(wxPaintEvent&);
    void OnSize(wxSizeEvent&);
    void OnMouseEnter(wxMouseEvent&);
    void OnMouseLeave(wxMouseEvent&);
    void OnClick(wxMouseEvent&);

private:
    wxString m_label;
    wxArrayString m_lines;

    bool m_hovered = false;
    bool m_active  = false;

    wxColour m_bg;
    wxColour m_bgHover;

    wxColour m_text;
    wxColour m_textHover;
    wxColour m_textActive;
};
#endif // BUTTONMENU_H
