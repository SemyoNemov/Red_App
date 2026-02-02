#include "App.h" //точка входа для MainFrame
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
MainFrame* mainFrame = new MainFrame("RED app");
mainFrame-> Center();
mainFrame-> Show();

return true;

}
