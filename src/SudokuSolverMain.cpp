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
#include "GameSquare.h"
#include "GameBoard.h"
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
const long SudokuSolverFrame::ID_BUTTONREMOVE = wxNewId();
const long SudokuSolverFrame::ID_BUTTONREVEAL = wxNewId();
const long SudokuSolverFrame::ID_STATICTEXT1 = wxNewId();
const long SudokuSolverFrame::ID_STATICTEXT2 = wxNewId();
const long SudokuSolverFrame::ID_TEXTCTRLROW = wxNewId();
const long SudokuSolverFrame::ID_TEXTCTRLCOL = wxNewId();
const long SudokuSolverFrame::ID_BUTTON3 = wxNewId();
const long SudokuSolverFrame::ID_BUTTONSOLVABLE = wxNewId();
const long SudokuSolverFrame::ID_BUTTONSTRIPEASY = wxNewId();
const long SudokuSolverFrame::ID_PANELDEBUG = wxNewId();
const long SudokuSolverFrame::ID_BUTTON1 = wxNewId();
const long SudokuSolverFrame::ID_BUTTON2 = wxNewId();
const long SudokuSolverFrame::ID_BUTTON4 = wxNewId();
const long SudokuSolverFrame::ID_BUTTON5 = wxNewId();
const long SudokuSolverFrame::ID_BUTTON6 = wxNewId();
const long SudokuSolverFrame::ID_BUTTON7 = wxNewId();
const long SudokuSolverFrame::ID_BUTTON8 = wxNewId();
const long SudokuSolverFrame::ID_BUTTON9 = wxNewId();
const long SudokuSolverFrame::ID_BUTTON10 = wxNewId();
const long SudokuSolverFrame::ID_BUTTON11 = wxNewId();
const long SudokuSolverFrame::ID_BUTTON12 = wxNewId();
const long SudokuSolverFrame::ID_BUTTON13 = wxNewId();
const long SudokuSolverFrame::ID_PANELCONTROL = wxNewId();
const long SudokuSolverFrame::ID_PANEL1 = wxNewId();
const long SudokuSolverFrame::idNewPuzzle = wxNewId();
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
    mMainGB = new GameBoard();
    mGuessGB = new GameBoard();
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            mGuessGB->ClearPossibles(i,j);
    row = 9;
    col = 9;

    //(*Initialize(SudokuSolverFrame)
    wxBoxSizer* BoxSizer4;
    wxBoxSizer* BoxSizer5;
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxBoxSizer* BoxSizer2;
    wxMenu* Menu1;
    wxGridSizer* GridSizer1;
    wxBoxSizer* BoxSizer1;
    wxMenuBar* MenuBar1;
    wxBoxSizer* BoxSizer3;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE|wxFULL_REPAINT_ON_RESIZE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
    MainPanel = new wxPanel(this, ID_PANEL1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    BoxSizer2 = new wxBoxSizer(wxVERTICAL);
    GameBoardPanel = new wxPanel(MainPanel, ID_PANEL2, wxDefaultPosition, wxSize(600,800), wxTAB_TRAVERSAL|wxFULL_REPAINT_ON_RESIZE, _T("ID_PANEL2"));
    BoxSizer2->Add(GameBoardPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DebugPanel = new wxPanel(MainPanel, ID_PANELDEBUG, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANELDEBUG"));
    GridSizer1 = new wxGridSizer(0, 2, 0, 0);
    ButtonRemove = new wxButton(DebugPanel, ID_BUTTONREMOVE, _("Remove Square"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONREMOVE"));
    GridSizer1->Add(ButtonRemove, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonReveal = new wxButton(DebugPanel, ID_BUTTONREVEAL, _("Reveal Square"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONREVEAL"));
    GridSizer1->Add(ButtonReveal, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText1 = new wxStaticText(DebugPanel, ID_STATICTEXT1, _("Row"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    GridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticText2 = new wxStaticText(DebugPanel, ID_STATICTEXT2, _("Column"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    GridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlRow = new wxTextCtrl(DebugPanel, ID_TEXTCTRLROW, _("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRLROW"));
    TextCtrlRow->SetMaxLength(1);
    GridSizer1->Add(TextCtrlRow, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlCol = new wxTextCtrl(DebugPanel, ID_TEXTCTRLCOL, _("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRLCOL"));
    TextCtrlCol->SetMaxLength(1);
    GridSizer1->Add(TextCtrlCol, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSolve = new wxButton(DebugPanel, ID_BUTTON3, _("Solve"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    GridSizer1->Add(ButtonSolve, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonSolvable = new wxButton(DebugPanel, ID_BUTTONSOLVABLE, _("Solvable\?"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONSOLVABLE"));
    GridSizer1->Add(ButtonSolvable, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonStripEasy = new wxButton(DebugPanel, ID_BUTTONSTRIPEASY, _("Strip Layer (Easy)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONSTRIPEASY"));
    GridSizer1->Add(ButtonStripEasy, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DebugPanel->SetSizer(GridSizer1);
    GridSizer1->Fit(DebugPanel);
    GridSizer1->SetSizeHints(DebugPanel);
    BoxSizer2->Add(DebugPanel, 0, wxALL|wxALIGN_LEFT|wxALIGN_TOP, 0);
    ControlPanel = new wxPanel(MainPanel, ID_PANELCONTROL, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANELCONTROL"));
    BoxSizer3 = new wxBoxSizer(wxVERTICAL);
    BoxSizer4 = new wxBoxSizer(wxHORIZONTAL);
    Button1 = new wxButton(ControlPanel, ID_BUTTON1, _("1"), wxDefaultPosition, wxSize(35,25), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer4->Add(Button1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button2 = new wxButton(ControlPanel, ID_BUTTON2, _("2"), wxDefaultPosition, wxSize(35,25), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer4->Add(Button2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button3 = new wxButton(ControlPanel, ID_BUTTON4, _("3"), wxDefaultPosition, wxSize(35,25), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    BoxSizer4->Add(Button3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button4 = new wxButton(ControlPanel, ID_BUTTON5, _("4"), wxDefaultPosition, wxSize(35,25), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    BoxSizer4->Add(Button4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button5 = new wxButton(ControlPanel, ID_BUTTON6, _("5"), wxDefaultPosition, wxSize(35,25), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    BoxSizer4->Add(Button5, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button6 = new wxButton(ControlPanel, ID_BUTTON7, _("6"), wxDefaultPosition, wxSize(35,25), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    BoxSizer4->Add(Button6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button7 = new wxButton(ControlPanel, ID_BUTTON8, _("7"), wxDefaultPosition, wxSize(35,25), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    BoxSizer4->Add(Button7, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button8 = new wxButton(ControlPanel, ID_BUTTON9, _("8"), wxDefaultPosition, wxSize(35,25), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    BoxSizer4->Add(Button8, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    Button9 = new wxButton(ControlPanel, ID_BUTTON10, _("9"), wxDefaultPosition, wxSize(35,25), 0, wxDefaultValidator, _T("ID_BUTTON10"));
    Button9->SetMinSize(wxSize(30,25));
    Button9->SetMaxSize(wxSize(30,25));
    BoxSizer4->Add(Button9, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(BoxSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer5 = new wxBoxSizer(wxHORIZONTAL);
    ButtonSet = new wxButton(ControlPanel, ID_BUTTON11, _("Set"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON11"));
    BoxSizer5->Add(ButtonSet, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonNote = new wxButton(ControlPanel, ID_BUTTON12, _("Note"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON12"));
    BoxSizer5->Add(ButtonNote, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ButtonClear = new wxButton(ControlPanel, ID_BUTTON13, _("Clear"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON13"));
    BoxSizer5->Add(ButtonClear, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3->Add(BoxSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ControlPanel->SetSizer(BoxSizer3);
    BoxSizer3->Fit(ControlPanel);
    BoxSizer3->SetSizeHints(ControlPanel);
    BoxSizer2->Add(ControlPanel, 0, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    MainPanel->SetSizer(BoxSizer2);
    BoxSizer2->Fit(MainPanel);
    BoxSizer2->SetSizeHints(MainPanel);
    BoxSizer1->Add(MainPanel, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    SetSizer(BoxSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuNewPuzzle = new wxMenuItem(Menu1, idNewPuzzle, _("New Puzzle"), _("Create a new puzzle"), wxITEM_NORMAL);
    Menu1->Append(MenuNewPuzzle);
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
    GameBoardPanel->Connect(wxEVT_KEY_UP,(wxObjectEventFunction)&SudokuSolverFrame::OnGameBoardPanelKeyUp,0,this);
    GameBoardPanel->Connect(wxEVT_LEFT_UP,(wxObjectEventFunction)&SudokuSolverFrame::OnGameBoardPanelLeftUp,0,this);
    Connect(ID_BUTTONREMOVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonRemoveClick);
    Connect(ID_BUTTONREVEAL,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonRevealClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonSolveClick);
    Connect(ID_BUTTONSOLVABLE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonSolvableClick);
    Connect(ID_BUTTONSTRIPEASY,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonStripEasyClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonNumClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonNumClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonNumClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonNumClick);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonNumClick);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonNumClick);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonNumClick);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonNumClick);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonNumClick);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonSetClick);
    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&SudokuSolverFrame::OnButtonNoteClick);
    Connect(idNewPuzzle,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SudokuSolverFrame::OnMenuNewPuzzleSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SudokuSolverFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&SudokuSolverFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&SudokuSolverFrame::OnClose);
    //*)

    numButtons[0] = Button1;
    numButtons[1] = Button2;
    numButtons[2] = Button3;
    numButtons[3] = Button4;
    numButtons[4] = Button5;
    numButtons[5] = Button6;
    numButtons[6] = Button7;
    numButtons[7] = Button8;
    numButtons[8] = Button9;

}

void SudokuSolverFrame::CopyToGuessBoard()
{
    mGuessGB->Copy(*mMainGB);
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
    wxPaintDC dc( GameBoardPanel );

	DrawBoardBackground(dc);
	DrawBoardNumbers(dc);
}

void SudokuSolverFrame::DrawBoardBackground(wxPaintDC &dc)
{
	unsigned int spSq = 0;
    unsigned int smallSide;
    unsigned int i,j;

    wxColour LGray;
    wxBrush LGrayBr;

    LGray.Set(210,210,210);
    LGrayBr.SetColour(LGray);

    wxSize sz = GameBoardPanel->GetClientSize();
    if (sz.x < sz.y)
        smallSide = sz.x;
    else
        smallSide = sz.y;

    spSq = smallSide / 9;
    smallSide -= 10;

        // Set the Brush and Pen to red
    dc.SetBrush( LGrayBr );
    dc.SetPen(*wxBLACK_PEN );
    // Draw rectangle 40 pixels wide and 40 high
    // with upper left corner at 10 , 10.

    for(i=0;i<9;i++)
        for(j=0;j<9;j++)
        {
            if(i == col && j == row)
                dc.SetBrush(*wxBLUE_BRUSH);
            else
                dc.SetBrush(LGrayBr);
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

void SudokuSolverFrame::DrawBoardNumbers(wxPaintDC &dc)
{
	unsigned int spSq = 0;
    unsigned int smallSide;
    unsigned int i,j,k, pVal;
    wxString debugString;
    wxString pString;
    wxColour redC, greenC, blackC;

    redC.Set(200,0,0);
    greenC.Set(0,200,0);
    blackC.Set(0,0,0);

    wxSize sz = GameBoardPanel->GetClientSize();
    if (sz.x < sz.y)
        smallSide = sz.x;
    else
        smallSide = sz.y;

    spSq = smallSide / 9;
    smallSide -= 10;

        // Create a 16 point, serif font, that is not bold,
    //   not italic, and not underlined.
    dc.SetPen(*wxBLACK_PEN );
    wxFont BigFont(spSq/2,wxFONTFAMILY_ROMAN,wxNORMAL,wxNORMAL,false);
    wxFont SmallFont(spSq/8,wxFONTFAMILY_ROMAN,wxNORMAL,wxNORMAL,false);

    // Tell dc to use this font
    dc.SetFont(BigFont);

    for(i=0;i < 9;i++)
    {
        for(j=0;j<9;j++)
        {
            if (mGuessGB->GetVal(i, j) != 0) // Show if there's a value
            {
                dc.SetFont(BigFont);
                debugString.clear();
                debugString << _("i = ") << i << _(" j = ") << j;
                debugString << _("\nVal = ") << mGuessGB->GetVal(i, j);
                //wxMessageBox(debugString);

                pVal = 0;
                pVal = mGuessGB->GetVal(i, j);
                if(mGuessGB->GetShown(i, j))
                    dc.SetTextForeground(blackC);
                else if(mGuessGB->GetVal(i, j) == mMainGB->GetVal(i, j))
                    dc.SetTextForeground(greenC);
                else
                    dc.SetTextForeground(redC);


                pString.clear();
                pString << pVal;
                dc.DrawText(pString, 6 * spSq / 20 + ((j) * spSq), spSq / 6 + ((i) * spSq));
            }
            else // Draw all possibles
            {
                for(k=1;k<=9;k++)
                {
                    dc.SetFont(SmallFont);
                    pString.clear();
                    pString << k;
                    if(mGuessGB->GetPossibles(i, j, k))
                    switch (k)
                    {
                        case 1:
                            dc.DrawText(pString, 6 * spSq / 20 + ((j) * spSq) - 13, spSq / 6 + ((i) * spSq) - 7);
                            break;
                        case 2:
                            dc.DrawText(pString, 6 * spSq / 20 + ((j) * spSq) + 10, spSq / 6 + ((i) * spSq) - 7);
                            break;
                        case 3:
                            dc.DrawText(pString, 6 * spSq / 20 + ((j) * spSq) + 32, spSq / 6 + ((i) * spSq) - 7);
                            break;
                        case 4:
                            dc.DrawText(pString, 6 * spSq / 20 + ((j) * spSq) - 13, spSq / 6 + ((i) * spSq)+14);
                            break;
                        case 5:
                            dc.DrawText(pString, 6 * spSq / 20 + ((j) * spSq) + 10, spSq / 6 + ((i) * spSq)+14);
                            break;
                        case 6:
                            dc.DrawText(pString, 6 * spSq / 20 + ((j) * spSq) + 32, spSq / 6 + ((i) * spSq)+14);
                            break;
                        case 7:
                            dc.DrawText(pString, 6 * spSq / 20 + ((j) * spSq) - 13, spSq / 6 + ((i) * spSq)+35);
                            break;
                        case 8:
                            dc.DrawText(pString, 6 * spSq / 20 + ((j) * spSq) + 10, spSq / 6 + ((i) * spSq)+35);
                            break;
                        case 9:
                            dc.DrawText(pString, 6 * spSq / 20 + ((j) * spSq) + 32, spSq / 6 + ((i) * spSq)+35);
                            break;
                        default:
                            break;
                    }

                }
            }
        }
    }

}

void SudokuSolverFrame::OnGameBoardPanelLeftUp(wxMouseEvent& event)
{
	long xpos, ypos;
	unsigned int row, col;
	wxString pString;
	unsigned int spSq = 0;
    unsigned int smallSide;

    event.GetPosition(&xpos, &ypos);

    wxSize sz = GameBoardPanel->GetClientSize();
    if (sz.x < sz.y)
        smallSide = sz.x;
    else
        smallSide = sz.y;

    spSq = smallSide / 9;
    row = ypos / spSq;
    col = xpos / spSq;

	event.GetPosition(&xpos, &ypos);
	/*pString << _("Row ") << row << _(" Col ") << col;
	wxMessageBox(pString);*/

	SetRow(row);
	SetCol(col);


	Refresh();
}

void SudokuSolverFrame::OnMenuNewPuzzleSelected(wxCommandEvent& event)
{
	unsigned int i,j;

	mMainGB->Binit();
	mMainGB->GenBoard(0,0);
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            mMainGB->SetShown(i, j, true);
        }
    }
	CopyToGuessBoard();
	Refresh();
	mGuessGB->RemoveSquares();
    Refresh();
    for(i=0;i<9;i++)
    {
        for(j=0;j<9;j++)
        {
            mGuessGB->ClearPossibles(i,j);
        }
    }
}

void SudokuSolverFrame::OnButtonSolveClick(wxCommandEvent& event)
{
    mGuessGB->Solve();
    Refresh();
}

void SudokuSolverFrame::OnButtonRemoveClick(wxCommandEvent& event)
{
    long row, col;
    wxString txtCtrlVal;

    txtCtrlVal = TextCtrlRow->GetValue();
    txtCtrlVal.ToLong(&row);
    txtCtrlVal = TextCtrlCol->GetValue();
    txtCtrlVal.ToLong(&col);
    mGuessGB->SetSquare(0, row, col);
    Refresh();
}

void SudokuSolverFrame::OnButtonRevealClick(wxCommandEvent& event)
{
    long row, col;
    unsigned int val;
    wxString txtCtrlVal;

    txtCtrlVal = TextCtrlRow->GetValue();
    txtCtrlVal.ToLong(&row);
    txtCtrlVal = TextCtrlCol->GetValue();
    txtCtrlVal.ToLong(&col);
    val = mMainGB->GetVal(row, col);
    mGuessGB->SetVal(row, col, val);
    Refresh();
}

void SudokuSolverFrame::OnButtonSolvableClick(wxCommandEvent& event)
{
    if(mGuessGB->Solvable())
        wxMessageBox(_("Solvable!"));
    else
        wxMessageBox(_("Not Solvable!"));
}



void SudokuSolverFrame::OnButtonStripEasyClick(wxCommandEvent& event)
{
    bool removeSq;

    removeSq = mGuessGB->RemoveLayerEasy();
    if(removeSq)
        wxMessageBox(_("Removed a layer"));
    else
        wxMessageBox(_("Did not remove a layer"));
    Refresh();
}


void SudokuSolverFrame::OnButtonSetClick(wxCommandEvent& event)
{
    ButtonSet->SetBackgroundColour(*wxBLUE);
    ButtonSet->SetForegroundColour(*wxWHITE);
    ButtonNote->SetBackgroundColour(wxNullColour);
    ButtonNote->SetForegroundColour(*wxBLACK);
    ButtonClear->SetBackgroundColour(wxNullColour);
    ButtonClear->SetForegroundColour(*wxBLACK);

    ctrlSelect = SET;
}

void SudokuSolverFrame::OnButtonNoteClick(wxCommandEvent& event)
{
    wxColour colorDef;

    colorDef.Set(240,240,240);

    ButtonSet->SetBackgroundColour(wxNullColour);
    ButtonNote->SetBackgroundColour(*wxBLUE);
    ButtonSet->SetForegroundColour(*wxBLACK);
    ButtonNote->SetForegroundColour(*wxWHITE);
    ButtonClear->SetBackgroundColour(wxNullColour);
    ButtonSet->SetForegroundColour(*wxBLACK);

    ctrlSelect = NOTE;
}

void SudokuSolverFrame::OnButtonNumClick(wxCommandEvent& event)
{
    unsigned int i;
    wxString defaultStr;

    defaultStr.clear();
    for(i=0;i<9;i++)
        if(numButtons[i]->GetId() == event.GetId())
        {
            if(ctrlSelect==SET)
            {
                if(row<9&&row>=0&&col<9&&col>=0&&!mGuessGB->GetShown(row, col))
                {
                    mGuessGB->SetVal(row, col, i+1);
                    // todo - remove possibles from other squares
                }



            }
            else if (ctrlSelect==NOTE)
            {
                if(mGuessGB->GetPossibles(row, col, i+1))
                    mGuessGB->RemovePossibles(row, col, i+1);
                else
                    mGuessGB->SetPossibles(row, col, i+1);
            }
        }
    Refresh();
}

void SudokuSolverFrame::OnGameBoardPanelKeyUp(wxKeyEvent& event)
{
    unsigned int keyUp;
    wxString debugStr;

    keyUp = event.GetKeyCode();

    if(keyUp >= 48 && keyUp <=57)
    {
        if(!mGuessGB->GetShown(row, col))
        {
            mGuessGB->SetVal(row, col, keyUp-48);
            Refresh();
        }
    }
    else if(keyUp >= 324 && keyUp <=333)
    {
        if(!mGuessGB->GetShown(row, col))
        {
            mGuessGB->SetVal(row, col, keyUp-324);
            Refresh();
        }
    }
}
