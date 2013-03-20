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

enum Controls { SET, NOTE, CLEAR};

class SudokuSolverFrame: public wxFrame
{
    public:

        SudokuSolverFrame(wxWindow* parent,wxWindowID id = -1);
        void CopyToGuessBoard();
        virtual ~SudokuSolverFrame();
        void DrawBoardBackground(wxPaintDC &dc);
        void DrawBoardNumbers(wxPaintDC &dc);
        void SetRow(unsigned int val) { row = val;}
        void SetCol(unsigned int val) { col = val;}
        void SetNumSelect(unsigned int val) {numSelect = val;}
        unsigned int GetRow() { return row;}
        unsigned int GetCol() { return col;}
        unsigned int GetNumSelect() {return numSelect;}

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
        void OnButtonStripEasyClick(wxCommandEvent& event);
        void OnButtonSetClick(wxCommandEvent& event);
        void OnButtonNoteClick(wxCommandEvent& event);
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
        static const long ID_BUTTONSTRIPEASY;
        static const long ID_PANELDEBUG;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_BUTTON6;
        static const long ID_BUTTON7;
        static const long ID_BUTTON8;
        static const long ID_BUTTON9;
        static const long ID_BUTTON10;
        static const long ID_BUTTON11;
        static const long ID_BUTTON12;
        static const long ID_BUTTON13;
        static const long ID_PANELCONTROL;
        static const long ID_PANEL1;
        static const long idNewPuzzle;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(SudokuSolverFrame)
        wxPanel* DebugPanel;
        wxPanel* ControlPanel;
        wxButton* Button4;
        wxMenuItem* MenuNewPuzzle;
        wxButton* ButtonRemove;
        wxButton* ButtonNote;
        wxStaticText* StaticText2;
        wxButton* Button1;
        wxButton* ButtonSet;
        wxStaticText* StaticText1;
        wxButton* ButtonClear;
        wxTextCtrl* TextCtrlRow;
        wxButton* Button2;
        wxButton* Button6;
        wxButton* Button5;
        wxButton* ButtonSolvable;
        wxButton* ButtonReveal;
        wxButton* Button3;
        wxTextCtrl* TextCtrlCol;
        wxButton* Button7;
        wxButton* ButtonStripEasy;
        wxStatusBar* StatusBar1;
        wxButton* Button9;
        wxPanel* MainPanel;
        wxButton* ButtonSolve;
        wxPanel* GameBoardPanel;
        wxButton* Button8;
        //*)

        GameBoard * mMainGB;
        GameBoard * mGuessGB;
        unsigned int numSelect;
        unsigned int row, col;
        Controls ctrlSelect;

        DECLARE_EVENT_TABLE()
};

#endif // SUDOKUSOLVERMAIN_H
