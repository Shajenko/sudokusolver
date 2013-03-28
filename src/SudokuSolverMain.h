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
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include "GameBoard.h"
#include "DebugPanel.h"

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
        void OnButtonNumClick(wxCommandEvent& event);
        void OnGameBoardPanelKeyUp(wxKeyEvent& event);
        void OnDifficultySelected(wxCommandEvent& event);
        //*)

        //(*Identifiers(SudokuSolverFrame)
        static const long ID_PANEL2;
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
        static const long idEasy;
        static const long idMedium;
        static const long idHard;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(SudokuSolverFrame)
        wxPanel* ControlPanel;
        wxButton* Button4;
        wxMenuItem* MenuNewPuzzle;
        wxButton* ButtonNote;
        wxMenu* Menu3;
        wxButton* Button1;
        wxButton* ButtonSet;
        wxMenuItem* MenuItemEasy;
        wxButton* ButtonClear;
        wxMenuItem* MenuItemHard;
        wxButton* Button2;
        wxButton* Button6;
        wxButton* Button5;
        wxButton* Button3;
        wxButton* Button7;
        wxStatusBar* StatusBar1;
        wxButton* Button9;
        wxPanel* MainPanel;
        wxMenuItem* MenuItemMedium;
        wxPanel* GameBoardPanel;
        wxButton* Button8;
        //*)

        GameBoard * mMainGB;
        GameBoard * mGuessGB;
        unsigned int numSelect;
        unsigned int row, col;
        Controls ctrlSelect;
        Difficulty diff;
        wxButton * numButtons[9];


        DECLARE_EVENT_TABLE()
};

#endif // SUDOKUSOLVERMAIN_H
