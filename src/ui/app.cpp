#include "app.h"

#include <wx/dataview.h>

#include "treemodel.h"

wxIMPLEMENT_APP(Hussein);

bool Hussein::OnInit()
{
	wxDataViewCtrl *view = new wxDataViewCtrl( NULL
	                                         , wxID_ANY
	                                         , wxPoint(50, 50)
	                                         , wxSize(450, 340));

	Tree<int> root(2);

	Tree<int> dwa(69);

	for(int i =0; i<8;i++)
		dwa = dwa.append( Tree<int>(i) );

	dwa = dwa.remove(3);

	for(int j = 0; j<8; j++)
	{
		root = root.append( dwa );
	}

	auto testModel = new TreeModel<int>(root);
	view->AssociateModel(testModel);

	view->Show(true);
	return true;
}