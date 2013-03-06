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
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

#include "GameBoard.h"

class SudokuSolverFrame: public wxFrame
{
    public:

        SudokuSolverFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~SudokuSolverFrame();

    private:

        //(*Handlers(SudokuSolverFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnGameBoardPanelPaint(wxPaintEvent& event);
        void OnGameBoardPanelLeftUp(wxMouseEvent& event);
        //*)

        //(*Identifiers(SudokuSolverFrame)
        static const long ID_PANEL2;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(SudokuSolverFrame)
        wxStatusBar* StatusBar1;
        wxPanel* MainPanel;
        wxPanel* GameBoardPanel;
        //*)

        GameBoard * mGB;

        DECLARE_EVENT_TABLE()
};

#endif // SUDOKUSOLVERMAIN_H
