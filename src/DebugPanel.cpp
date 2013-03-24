#include "wx_pch.h"
#include "DebugPanel.h"

#ifndef WX_PRECOMP
	//(*InternalHeadersPCH(DebugPanel)
	#include <wx/intl.h>
	#include <wx/string.h>
	//*)
#endif
//(*InternalHeaders(DebugPanel)
//*)

//(*IdInit(DebugPanel)
const long DebugPanel::ID_BUTTON1 = wxNewId();
const long DebugPanel::ID_BUTTON2 = wxNewId();
const long DebugPanel::ID_STATICTEXT1 = wxNewId();
const long DebugPanel::ID_STATICTEXT2 = wxNewId();
const long DebugPanel::ID_TEXTCTRL1 = wxNewId();
const long DebugPanel::ID_TEXTCTRL2 = wxNewId();
const long DebugPanel::ID_BUTTON3 = wxNewId();
const long DebugPanel::ID_BUTTON4 = wxNewId();
const long DebugPanel::ID_BUTTON5 = wxNewId();
//*)

BEGIN_EVENT_TABLE(DebugPanel,wxPanel)
	//(*EventTable(DebugPanel)
	//*)
END_EVENT_TABLE()

DebugPanel::DebugPanel(wxWindow* parent,wxWindowID id,const wxPoint& pos,const wxSize& size)
{
	//(*Initialize(DebugPanel)
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, id, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL, _T("id"));
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	ButtonRemove = new wxButton(this, ID_BUTTON1, _("Remove Square"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	FlexGridSizer1->Add(ButtonRemove, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonReveal = new wxButton(this, ID_BUTTON2, _("Reveal Square"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	FlexGridSizer1->Add(ButtonReveal, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Row"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	FlexGridSizer1->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Label"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
	FlexGridSizer1->Add(StaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlRow = new wxTextCtrl(this, ID_TEXTCTRL1, _("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrlRow->SetMaxLength(1);
	FlexGridSizer1->Add(TextCtrlRow, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrlCol = new wxTextCtrl(this, ID_TEXTCTRL2, _("1"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
	TextCtrlCol->SetMaxLength(1);
	FlexGridSizer1->Add(TextCtrlCol, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonSolve = new wxButton(this, ID_BUTTON3, _("Solve"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer1->Add(ButtonSolve, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonSolvable = new wxButton(this, ID_BUTTON4, _("Solvable\?"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
	FlexGridSizer1->Add(ButtonSolvable, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonStripEasy = new wxButton(this, ID_BUTTON5, _("Strip Layer (Easy)"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON5"));
	FlexGridSizer1->Add(ButtonStripEasy, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	//*)
}

DebugPanel::~DebugPanel()
{
	//(*Destroy(DebugPanel)
	//*)
}

