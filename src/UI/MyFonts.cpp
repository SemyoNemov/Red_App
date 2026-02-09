#include "MyFonts.h"

namespace MF
{
    static wxFont GetBaseSystemFont()
    {
        return wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    }

    wxFont GetDefaultFont(int sizeDelta)
    {
        wxFont font = GetBaseSystemFont();
        if (sizeDelta != 0)
        {
            font.SetPointSize(font.GetPointSize() + sizeDelta);
        }
        return font;
    }

    wxFont GetBoldFont(int sizeDelta)
    {
        wxFont font = GetDefaultFont(sizeDelta);
        font.MakeBold();
        return font;
    }

    wxFont GetLargeFont(int sizeDelta)
    {
        return GetDefaultFont(4 + sizeDelta);
    }

    wxFont GetTitleFont()
    {
        wxFont font = GetDefaultFont(10);
        font.MakeBold();
        return font;
    }

    wxFont GetStaticTextFont(int sizeDelta)
    {
        return GetDefaultFont(2 + sizeDelta);
    }

}
