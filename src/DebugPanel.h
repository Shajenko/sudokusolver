#ifndef DEBUGPANEL_H
#define DEBUGPANEL_H

#ifndef WX_PRECOMP
	//(*HeadersPCH(DebugPanel)
	#include <wx/sizer.h>
	#include <wx/stattext.h>
	#include <wx/textctrl.h>
	#include <wx/panel.h>
	#include <wx/button.h>
	//*)
#endif
//(*Headers(DebugPanel)
//*)

class DebugPanel: public wxPanel
{
	public:

		DebugPanel(wxWindow* parent,wxWindowID id=wxID_ANY,const wxPoint& pos=wxDefaultPosition,const wxSize& size=wxDefaultSize);
		virtual ~DebugPanel();

		//(*Declarations(DebugPanel)
		wxButton* ButtonRemove;
		wxStaticText* StaticText2;
		wxStaticText* StaticText1;
		wxTextCtrl* TextCtrlRow;
		wxButton* ButtonSolvable;
		wxButton* ButtonReveal;
		wxTextCtrl* TextCtrlCol;
		wxButton* ButtonStripEasy;
		wxButton* ButtonSolve;
		//*)

	protected:

		//(*Identifiers(DebugPanel)
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		static const long ID_STATICTEXT1;
		static const long ID_STATICTEXT2;
		static const long ID_TEXTCTRL1;
		static const long ID_TEXTCTRL2;
		static const long ID_BUTTON3;
		static const long ID_BUTTON4;
		static const long ID_BUTTON5;
		//*)

	private:

		//(*Handlers(DebugPanel)
		//*)

		DECLARE_EVENT_TABLE()
};

#endif
