#include "NetworkInterfacePanel.h"
#include "MyFonts.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include "NetworkInterface.h"

NetworkInterfacePanel::NetworkInterfacePanel(wxWindow* parent) : wxPanel(parent)
{
    SetBackgroundColour(wxColour(250, 250, 250));

    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* titleText = new wxStaticText(this, wxID_ANY, wxT("Сканер сетевых интерфейсов"));
    wxStaticText* descriptionText = new wxStaticText(this, wxID_ANY, wxT("Показывает список всех сетевых интерфейсов системы (Ethernet, Wi-Fi, виртуальные), их состояние, IP-адреса и другие ключевые параметры."));
    startScan = new wxButton(this, wxID_ANY, wxT("Начать сканирование"));
    btnExport = new wxButton(this, wxID_ANY, wxT("Экспортировать в файл"));
    startScan->SetFont(MF::GetBoldFont(2));
    btnExport->SetFont(MF::GetDefaultFont());
    listInterfaces = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxBORDER_THEME);
    listInterfaces ->InsertColumn(0, "ID");
    listInterfaces ->InsertColumn(1, "Interface");
    listInterfaces ->InsertColumn(2, "Type");
    listInterfaces ->InsertColumn(3, "IP Address");
    listInterfaces ->InsertColumn(4, "MAC");
    listInterfaces ->InsertColumn(5, "Status");

    titleText->SetFont(MF::GetTitleFont());
    descriptionText->SetFont(MF::GetStaticTextFont());

    panelSizer->Add(titleText);
    panelSizer->AddSpacer(10);
    panelSizer->Add(descriptionText);
    descriptionText->Wrap(500);
    panelSizer->AddSpacer(50);
    panelSizer->Add(startScan);
    panelSizer->AddSpacer(10);
    panelSizer->Add(listInterfaces,1 , wxEXPAND);
    panelSizer->AddSpacer(10);
    panelSizer->Add(btnExport, 0, wxALIGN_RIGHT);
    wxGridSizer* outerSizer = new wxGridSizer(1);
    outerSizer->Add(panelSizer, wxSizerFlags().Border(wxALL, 15).Expand());
    this-> SetSizer(outerSizer);
    SizerList();
    BindEvent();
}

void NetworkInterfacePanel::BindEvent()
{
    startScan->Bind(wxEVT_BUTTON, &NetworkInterfacePanel::StartScan, this);
    btnExport->Bind(wxEVT_BUTTON, &NetworkInterfacePanel::Export, this);
}
  void NetworkInterfacePanel::StartScan(wxCommandEvent& evt)
{
    std::vector<NetworkInterface> scan = scanNetworkInterface();
    InsertListInterface(scan);
    return;
}
void NetworkInterfacePanel::Export(wxCommandEvent& evt)
{

}

void NetworkInterfacePanel::InsertListInterface(const std::vector<NetworkInterface>& interfaces)
{
    listInterfaces->DeleteAllItems();
        for (const auto& iface : interfaces)
        {
        long row = listInterfaces->InsertItem(listInterfaces->GetItemCount(),
        wxString::Format("%d", iface.index));
        listInterfaces->SetItem(row, 1, wxString::FromUTF8(iface.name));
        listInterfaces->SetItem(row, 2, wxString::FromUTF8(iface.type));
        listInterfaces->SetItem(row, 3, wxString::FromUTF8(iface.ip));
        listInterfaces->SetItem(row, 4, wxString::FromUTF8(iface.mac_address));
        listInterfaces->SetItem(row, 5, iface.on ? wxT("Up") : wxT("Down"));
        }
    SizerList();
}
void NetworkInterfacePanel::SizerList()
{
    int colCount = 6;
    for (int col = 0; col < colCount; ++col)
    {
        listInterfaces->SetColumnWidth(col, wxLIST_AUTOSIZE);
        int contentWidth = listInterfaces->GetColumnWidth(col);

        listInterfaces->SetColumnWidth(col, wxLIST_AUTOSIZE_USEHEADER);
        int headerWidth = listInterfaces->GetColumnWidth(col);

        listInterfaces->SetColumnWidth(col, wxMax(contentWidth, headerWidth));
    }
    listInterfaces->Refresh();
    listInterfaces->Update();
}

