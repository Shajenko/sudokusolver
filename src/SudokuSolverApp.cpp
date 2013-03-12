/***************************************************************
 * Name:      SudokuSolverApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Timothy Sonnier (tisonnier2000@gmail.com)
 * Created:   2013-02-27
 * Copyright: Timothy Sonnier ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "SudokuSolverApp.h"

//(*AppHeaders
#include "SudokuSolverMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(SudokuSolverApp);

bool SudokuSolverApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    SudokuSolverFrame* Frame = new SudokuSolverFrame(0);
    Frame->Show();
    SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
