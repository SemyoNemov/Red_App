#include "App.h" //точка входа для MainFrame
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit() {
MainFrame* mainFrame = new MainFrame("Test");
mainFrame-> SetClientSize(800,600);
mainFrame-> Center();
mainFrame-> Show();
return true;

}
