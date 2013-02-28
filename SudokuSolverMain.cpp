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
#include <wx/settings.h>
#include <wx/font.h>
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
const long SudokuSolverFrame::ID_TEXTCTRL1 = wxNewId();
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
    wxMenu* Menu1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxStaticBoxSizer* StaticBoxSizer1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    Panel1 = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxSize(359,330), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    StaticBoxSizer1 = new wxStaticBoxSizer(wxHORIZONTAL, Panel1, _("Label"));
    TextCtrl1 = new wxTextCtrl(Panel1, ID_TEXTCTRL1, _("9"), wxDefaultPosition, wxSize(21,21), wxTE_NO_VSCROLL|wxTE_DONTWRAP, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl1->SetForegroundColour(wxColour(0,0,0));
    TextCtrl1->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_SCROLLBAR));
    wxFont TextCtrl1Font(10,wxSWISS,wxFONTSTYLE_NORMAL,wxNORMAL,false,_T("@Adobe Myungjo Std M"),wxFONTENCODING_DEFAULT);
    TextCtrl1->SetFont(TextCtrl1Font);
    StaticBoxSizer1->Add(TextCtrl1, 0, wxALL|wxSHAPED|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Panel1->SetSizer(StaticBoxSizer1);
    SetSizer(StaticBoxSizer1);
    Layout();
    BoxSizer1->Add(Panel1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
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

    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&SudokuSolverFrame::OnTextCtrl1Text);
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
}

void SudokuSolverFrame::OnTextCtrl1Text(wxCommandEvent& event)
{
}
