#include "NetworkInterfacePanel.h"
#include "MyFonts.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include "NetworkInterface.h"

NetworkInterfacePanel::NetworkInterfacePanel(wxWindow* parent) : wxPanel(parent)
{
    SetBackgroundColour(wxColour(255, 255, 255));

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
    listInterfaces->SetColumnWidth(0, 45);
    listInterfaces->SetColumnWidth(1, 150);
    listInterfaces->SetColumnWidth(2, 100);
    listInterfaces->SetColumnWidth(3, 150);
    listInterfaces->SetColumnWidth(4, 150);

    int totalWidth = listInterfaces->GetClientSize().GetWidth();
    int usedWidth = 0;
    for (int i = 0; i < 5; ++i) {
        usedWidth += listInterfaces->GetColumnWidth(i);
    }
    int lastColumnWidth = totalWidth - usedWidth - 20;
    if (lastColumnWidth < 80) {
        lastColumnWidth = 80;
    }
    listInterfaces->SetColumnWidth(5, lastColumnWidth);

}

