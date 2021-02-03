#include "MyApp.h"

#include <wx/frame.h>

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    // The arguments is must-have for mingw make
    wxFrame *frame = new wxFrame(nullptr, wxID_ANY, "Hello, wxWidgets");
    SetTopWindow(frame);
    frame->Show(true);
    return true;
}
