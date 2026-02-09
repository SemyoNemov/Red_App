#ifndef MYFONTS_H
#define MYFONTS_H
#include <wx/wx.h>
#include <wx/font.h>

namespace MF
{
    wxFont GetDefaultFont(int sizeDelta = 0);
    wxFont GetBoldFont(int sizeDelta = 0);
    wxFont GetLargeFont(int sizeDelta = 0);
    wxFont GetTitleFont();
    wxFont GetStaticTextFont(int sizeDelta = 0);
}

#endif // MYFONTS_H
