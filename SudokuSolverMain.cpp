/***************************************************************
 * Name:      SudokuSolverMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Timothy Sonnier (tisonnier2000@gmail.com)
 * Created:   2013-02-27
 * Copyright: Timothy Sonnier ()
 * License:
 **************************************************************/

#include "wx_pch.h"
#include "SudokuSolverMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(SudokuSolverFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(SudokuSolverFrame)
const long SudokuSolverFrame::ID_PANEL2 = wxNewId();
const long SudokuSolverFrame::ID_PANEL1 = wxNewId();
const long SudokuSolverFrame::idMenuQuit = wxNewId();
const long SudokuSolverFrame::idMenuAbout = wxNewId();
const long SudokuSolverFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(SudokuSolverFrame,wxFrame)
    //(*EventTable(SudokuSolverFrame)
    //*)
END_EVENT_TABLE()

SudokuSolverFrame::SudokuSolverFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(SudokuSolverFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    MainPanel = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    GameBoardPanel = new wxPanel(MainPanel, ID_PANEL2, wxDefaultPosition, wxSize(600,800), wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE, _T("ID_PANEL2"));
    BoxSizer2->Add(GameBoardPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    MainPanel->SetSizer(BoxSizer2);
    BoxSizer2->Fit(MainPanel);
    BoxSizer2->SetSizeHints(MainPanel);
    BoxSizer1->Add(MainPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizer1->Fit(this);
    BoxSizer1->SetSizeHints(this);

    GameBoardPanel->Connect(wxEVT_PAINT,(wxObjectEventFunction)&SudokuSolverFrame::OnGameBoardPanelPaint,0,this);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SudokuSolverFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SudokuSolverFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&SudokuSolverFrame::OnClose);
    //*)
}

SudokuSolverFrame::~SudokuSolverFrame()
{
    //(*Destroy(SudokuSolverFrame)
    //*)
}

void SudokuSolverFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void SudokuSolverFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void SudokuSolverFrame::OnClose(wxCloseEvent& event)
{
    GameBoardPanel->Destroy();
    MainPanel->Destroy();
	Destroy();

}

void SudokuSolverFrame::OnGameBoardPanelPaint(wxPaintEvent& event)
{
    int spSq = 0;
    int smallSide;
    wxPaintDC dc( GameBoardPanel );

    wxSize sz = GetClientSize();
    if (sz.x < sz.y)
        smallSide = sz.x;
    else
        smallSide = sz.y;

    spSq = smallSide / 9;
    smallSide -= 10;


    // Create a 16 point, serif font, that is not bold,
    //   not italic, and not underlined.
//    dc.SetPen(*wxRED_PEN );
//    wxFont BigFont(16,wxFONTFAMILY_ROMAN,wxNORMAL,wxNORMAL,false);
//    // Tell dc to use this font
//    dc.SetFont(BigFont);
//    // Write the title of our picture.
//    dc.DrawText(wxT("Red Square"), 60, 10);

    // Set the Brush and Pen to red
    dc.SetBrush( *wxWHITE_BRUSH );
    dc.SetPen(*wxBLACK_PEN );
    // Draw rectangle 40 pixels wide and 40 high
    // with upper left corner at 10 , 10.

    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            dc.DrawRectangle( 0 + spSq*i, 0 + spSq*j, spSq - 5, spSq - 5 );
        }

    wxColor Black(0,0,0);
    wxPen myBlackPen(Black,5,wxSOLID);
    dc.SetPen(myBlackPen);

    // Section Borders
    dc.DrawLine( 0, smallSide/3 - 2, smallSide, smallSide/3 - 2);
    dc.DrawLine( 0, smallSide*2/3 - 1, smallSide, smallSide*2/3 - 1);
    dc.DrawLine( smallSide/3 - 2, 0, smallSide/3 - 2, smallSide);
    dc.DrawLine( smallSide*2/3 - 1, 0, smallSide*2/3 - 1, smallSide);

    // Edge Borders
    dc.DrawLine( 0, 0, smallSide, 0);
    dc.DrawLine( 0, 0, 0, smallSide);
    dc.DrawLine( 0, smallSide, smallSide, smallSide);
    dc.DrawLine( smallSide, 0, smallSide, smallSide);
}
