/***************************************************************
 * Name:      SudokuSolverMain.h
 * Purpose:   Defines Application Frame
 * Author:    Timothy Sonnier (tisonnier2000@gmail.com)
 * Created:   2013-02-27
 * Copyright: Timothy Sonnier ()
 * License:
 **************************************************************/

#ifndef SUDOKUSOLVERMAIN_H
#define SUDOKUSOLVERMAIN_H

//(*Headers(SudokuSolverFrame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include "GameBoard.h"

class SudokuSolverFrame: public wxFrame
{
    public:

        SudokuSolverFrame(wxWindow* parent,wxWindowID id = -1);
        void CopyToGuessBoard();
        virtual ~SudokuSolverFrame();
        void DrawBoardBackground(wxPaintDC &dc);
        void DrawBoardNumbers(wxPaintDC &dc);

    private:

        //(*Handlers(SudokuSolverFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnGameBoardPanelPaint(wxPaintEvent& event);
        void OnGameBoardPanelLeftUp(wxMouseEvent& event);
        void OnMenuNewPuzzleSelected(wxCommandEvent& event);
        void OnButtonSolveClick(wxCommandEvent& event);
        void OnButtonRemoveClick(wxCommandEvent& event);
        void OnButtonRevealClick(wxCommandEvent& event);
        void OnButtonSolvableClick(wxCommandEvent& event);
        //*)

        //(*Identifiers(SudokuSolverFrame)
        static const long ID_PANEL2;
        static const long ID_BUTTONREMOVE;
        static const long ID_BUTTONREVEAL;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_TEXTCTRLROW;
        static const long ID_TEXTCTRLCOL;
        static const long ID_BUTTON3;
        static const long ID_BUTTONSOLVABLE;
        static const long ID_PANELDEBUG;
        static const long ID_PANEL1;
        static const long idNewPuzzle;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(SudokuSolverFrame)
        wxPanel* DebugPanel;
        wxMenuItem* MenuNewPuzzle;
        wxButton* ButtonRemove;
        wxStaticText* StaticText2;
        wxStaticText* StaticText1;
        wxTextCtrl* TextCtrlRow;
        wxButton* ButtonSolvable;
        wxButton* ButtonReveal;
        wxTextCtrl* TextCtrlCol;
        wxStatusBar* StatusBar1;
        wxPanel* MainPanel;
        wxButton* ButtonSolve;
        wxPanel* GameBoardPanel;
        //*)

        GameBoard * mMainGB;
        GameBoard * mGuessGB;

        DECLARE_EVENT_TABLE()
};

#endif // SUDOKUSOLVERMAIN_H
