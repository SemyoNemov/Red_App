#include "ButtonMenu.h"
#include "ButtonMenu.h"
#include <wx/tokenzr.h>
#include <wx/dcbuffer.h>

ButtonMenu::ButtonMenu(wxWindow* parent,
                       wxWindowID id,
                       const wxString& label)
    : wxPanel(parent, id),
      m_label(label)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    UpdateColors();

    Bind(wxEVT_PAINT,        &ButtonMenu::OnPaint,      this);
    Bind(wxEVT_SIZE,         &ButtonMenu::OnSize,       this);
    Bind(wxEVT_ENTER_WINDOW, &ButtonMenu::OnMouseEnter, this);
    Bind(wxEVT_LEAVE_WINDOW, &ButtonMenu::OnMouseLeave, this);
    Bind(wxEVT_LEFT_DOWN,    &ButtonMenu::OnClick,      this);
}

void ButtonMenu::SetActive(bool active)
{
    m_active = active;
    Refresh();
}

void ButtonMenu::UpdateColors()
{
    wxColour base = GetParent()->GetBackgroundColour();

    m_bg        = base;
    m_bgHover   = base.ChangeLightness(90);

    m_text       = wxColor(0, 0, 0);
    m_textHover  = wxColor(255, 0, 0);
    m_textActive = wxColor(0, 255, 0);
}

void ButtonMenu::OnMouseEnter(wxMouseEvent&)
{
    m_hovered = true;
    SetCursor(wxCursor(wxCURSOR_HAND));
    Refresh();
}

void ButtonMenu::OnMouseLeave(wxMouseEvent&)
{
    m_hovered = false;
    SetCursor(wxNullCursor);
    Refresh();
}

void ButtonMenu::OnClick(wxMouseEvent&)
{
    wxCommandEvent evt(wxEVT_BUTTON, GetId());
    evt.SetEventObject(this);
    ProcessWindowEvent(evt);
}

void ButtonMenu::OnSize(wxSizeEvent& evt)
{
    int w = evt.GetSize().GetWidth();
    RebuildLines(w);
    UpdateMinHeight(w);
    evt.Skip();
}

void ButtonMenu::RebuildLines(int width)
{
    m_lines.Clear();

    wxClientDC dc(this);
    dc.SetFont(GetFont());

    int availableWidth = width - 20;
    if (availableWidth <= 0)
        return;

    wxStringTokenizer tokenizer(m_label, " ");
    wxString line;

    while (tokenizer.HasMoreTokens())
    {
        wxString word = tokenizer.GetNextToken();
        wxString test = line.IsEmpty() ? word : line + " " + word;

        int w, h;
        dc.GetTextExtent(test, &w, &h);

        if (w > availableWidth)
        {
            if (!line.IsEmpty())
                m_lines.Add(line);
            line = word;
        }
        else
        {
            line = test;
        }
    }

    if (!line.IsEmpty())
        m_lines.Add(line);
}

void ButtonMenu::UpdateMinHeight(int)
{
    wxClientDC dc(this);
    dc.SetFont(GetFont());

    int height = m_lines.size() * dc.GetCharHeight() + 12;
    SetMinSize(wxSize(-1, height));
}

void ButtonMenu::OnPaint(wxPaintEvent&)
{
    wxAutoBufferedPaintDC dc(this);

    dc.SetBrush(wxBrush(m_hovered ? m_bgHover : m_bg));
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.DrawRectangle(GetClientRect());

    dc.SetFont(GetFont());
    dc.SetTextForeground(
        m_active  ? m_textActive :
        m_hovered ? m_textHover  :
                    m_text
    );

    wxRect textRect = GetClientRect().Deflate(10, 6);

    int y = textRect.GetY();
    int lineHeight = dc.GetCharHeight();

    for (const wxString& line : m_lines)
    {
        dc.DrawText(line, textRect.GetX(), y);
        y += lineHeight;
    }
}
