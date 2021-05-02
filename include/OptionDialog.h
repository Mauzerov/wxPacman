#ifndef OPTIONDIALOG_H
#define OPTIONDIALOG_H

#include "other/Codes.h"
#include <string>
//(*Headers(OptionDialog)
#include <wx/button.h>
#include <wx/choice.h>
#include <wx/dialog.h>
#include <wx/panel.h>
#include <wx/statline.h>
#include <wx/stattext.h>
//*)

class OptionDialog: public wxDialog
{
	public:
		OptionDialog(wxWindow* parent, wxWindowID id, std::string movement, std::string language);
		virtual ~OptionDialog( void );

        std::string movement; // Selected Option
        std::string language; // Selected Option
		//(*Declarations(OptionDialog)
		wxButton* SaveOptionBtn;
		wxChoice* GameLangChoise;
		wxChoice* KeyBindsMoveChoice;
		wxPanel* GameLangPanel;
		wxPanel* GamePausePanel;
		wxPanel* KeyBindsPanel;
		wxStaticLine* GamePauseUnderLine;
		wxStaticText* GameLangLabel;
		wxStaticText* GamePauseLabel;
		wxStaticText* KeyBindsMoveLabel;
		wxStaticText* SpaceShootLabel;
		//*)

	protected:

		//(*Identifiers(OptionDialog)
		static const long ID_BUTTONSAVE;
		static const long ID_KEYCHOICE;
		static const long ID_LANGCHOICE;
		//*)

	private:

		//(*Handlers(OptionDialog)
		void OnDialogClose(wxCloseEvent& event);
		void OnSaveOptionBtnClick(wxCommandEvent& event);
		//*)

		void SaveOptions( void );

		DECLARE_EVENT_TABLE()
};

#endif
