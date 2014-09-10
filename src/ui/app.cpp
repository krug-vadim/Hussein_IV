#include "app.h"

wxIMPLEMENT_APP(Hussein);

bool Hussein::OnInit()
{
	wxFrame *frame = new wxFrame(NULL, wxID_ANY, "Hussein // хуй пизда", wxPoint(50, 50), wxSize(450, 340));
	frame->Show( true );
	return true;
}