/***************************************************************
 * Name:      PacmanApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2021-02-03
 * Copyright:  ()
 * License:
 **************************************************************/

#include "PacmanApp.h"

#if 0
//(*AppHeaders
#include "PacmanMain.h"
#include <wx/image.h>
//*)
#endif // 0

#include "PacmanMain.h"
#include <wx/image.h>

IMPLEMENT_APP(PacmanApp);

bool PacmanApp::OnInit()
{
    #if 0
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	PacmanFrame* Frame = new PacmanFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    #endif // 0

    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	PacmanFrame* Frame = new PacmanFrame(0);
    	Frame->Show();
    	Frame->SetIcon(wxICON(aaaa));
    	SetTopWindow(Frame);
    }

    return wxsOK;

}
