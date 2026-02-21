#include "ScanPortsPanel.h"
#include "Ports.h"
#include "MyFonts.h"
#include <wx/wx.h>
#include <wx/listctrl.h>

ScanPortsPanel::ScanPortsPanel(wxWindow* parent) : wxPanel(parent)
{
    SetBackgroundColour(wxColour(250, 250, 250));
    wxBoxSizer* panelSizer = new wxBoxSizer(wxVERTICAL);
    wxStaticText* titleText = new wxStaticText(this, wxID_ANY, wxT("Сканер открытых портов"));
    wxStaticText* descriptionText = new wxStaticText(this, wxID_ANY, wxT("Раздел показывает активные сетевые соединения и открытые порты: протокол, статус, локальные и удалённые адреса с портами, PID и имя процесса. Для некоторых портов информация доступна только в режиме суперпользователя"));
    startScan = new wxButton(this, wxID_ANY, wxT("Начать сканирование"));
    btnExport = new wxButton(this, wxID_ANY, wxT("Экспортировать в файл"));
    startScan->SetFont(MF::GetBoldFont(2));
    btnExport->SetFont(MF::GetDefaultFont());
    listInterfaces = new wxListCtrl(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL|wxBORDER_THEME);
    listInterfaces ->InsertColumn(0, "Protocol");
    listInterfaces ->InsertColumn(1, "Status");
    listInterfaces ->InsertColumn(2, "Local IP");
    listInterfaces ->InsertColumn(3, "Local port");
    listInterfaces ->InsertColumn(4, "Remote IP");
    listInterfaces ->InsertColumn(5, "Remote port");
    listInterfaces ->InsertColumn(6, "PID");
    listInterfaces ->InsertColumn(7, "Process name");

    titleText->SetFont(MF::GetTitleFont());
    descriptionText->SetFont(MF::GetStaticTextFont());

    panelSizer->Add(titleText);
    panelSizer->AddSpacer(10);
    panelSizer->Add(descriptionText);
    descriptionText->Wrap(650);
    panelSizer->AddSpacer(50);
    panelSizer->Add(startScan);
    panelSizer->AddSpacer(10);
    panelSizer->Add(listInterfaces, 1, wxEXPAND);
    panelSizer->AddSpacer(10);
    panelSizer->Add(btnExport, 0, wxALIGN_RIGHT);
    wxGridSizer* outerSizer = new wxGridSizer(1);
    outerSizer->Add(panelSizer, wxSizerFlags().Border(wxALL, 15).Expand());
    this-> SetSizer(outerSizer);
    SizerList();
    BindEvent();
}

void ScanPortsPanel::BindEvent()
{
    startScan->Bind(wxEVT_BUTTON, &ScanPortsPanel::StartScan, this);
    btnExport->Bind(wxEVT_BUTTON, &ScanPortsPanel::Export, this);
}

void ScanPortsPanel::StartScan(wxCommandEvent& evt)
{
    std::vector<Port> scan = scanPortrs();
    InsertListPort(scan);
    return;
}

void ScanPortsPanel::Export(wxCommandEvent& evt)
{

}

void ScanPortsPanel::InsertListPort(const std::vector<Port>& ports)
{
    listInterfaces->DeleteAllItems();
    for (const auto& port : ports)
    {
    int row = listInterfaces->InsertItem(listInterfaces->GetItemCount(),
    wxString::FromUTF8(port.protocol));
    listInterfaces->SetItem(row, 1, wxString::FromUTF8(port.status));
    listInterfaces->SetItem(row, 2, wxString::FromUTF8(port.localIP));
    listInterfaces->SetItem(row, 3, wxString::FromUTF8(port.localPort));
    listInterfaces->SetItem(row, 4, wxString::FromUTF8(port.remoteIP));
    listInterfaces->SetItem(row, 5, wxString::FromUTF8(port.remotePort));
    listInterfaces->SetItem(row, 6, wxString::Format(wxT("%d"), port.pid));
    listInterfaces->SetItem(row, 7, wxString::FromUTF8(port.name));
    }
    SizerList();
}

void ScanPortsPanel::SizerList()
{
    int colCount = 8;
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
