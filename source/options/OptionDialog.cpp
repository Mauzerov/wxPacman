#include "OptionDialog.h"
#include <iostream>
//(*InternalHeaders(OptionDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//(*IdInit(OptionDialog)
const long OptionDialog::ID_BUTTONSAVE = wxNewId();
const long OptionDialog::ID_KEYCHOICE = wxNewId();
const long OptionDialog::ID_LANGCHOICE = wxNewId();
//*)

BEGIN_EVENT_TABLE(OptionDialog,wxDialog)
	//(*EventTable(OptionDialog)
	//*)
END_EVENT_TABLE()

OptionDialog::OptionDialog(wxWindow* parent, wxWindowID id, std::string movement, std::string language)
{
	//(*Initialize(OptionDialog)
	Create(parent, id, _("Options"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU, _T("id"));
	SetClientSize(wxSize(400,200));
	SetForegroundColour(wxColour(255,255,255));
	SetBackgroundColour(wxColour(0,0,0));
	wxFont thisFont(11,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Consolas"),wxFONTENCODING_DEFAULT);
	SetFont(thisFont);
	GamePausePanel = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(400,30), 0, _T("wxID_ANY"));
	GamePauseLabel = new wxStaticText(GamePausePanel, wxID_ANY, _("GAME PAUSED"), wxPoint(0,0), wxSize(400,50), wxALIGN_CENTRE, _T("wxID_ANY"));
	GamePauseLabel->SetForegroundColour(wxColour(243,156,18));
	GamePauseLabel->SetBackgroundColour(wxColour(16,16,16));
	wxFont GamePauseLabelFont(20,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Consolas"),wxFONTENCODING_DEFAULT);
	GamePauseLabel->SetFont(GamePauseLabelFont);
	GamePauseUnderLine = new wxStaticLine(this, wxID_ANY, wxPoint(0,30), wxSize(400,2), wxLI_HORIZONTAL, _T("wxID_ANY"));
	GamePauseUnderLine->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME));
	GamePauseUnderLine->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME));
	SaveOptionBtn = new wxButton(this, ID_BUTTONSAVE, _("Save Options"), wxPoint(100,175), wxSize(200,25), wxBORDER_NONE|wxTRANSPARENT_WINDOW, wxDefaultValidator, _T("ID_BUTTONSAVE"));
	SaveOptionBtn->SetForegroundColour(wxColour(255,255,255));
	SaveOptionBtn->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWFRAME));
	KeyBindsPanel = new wxPanel(this, wxID_ANY, wxPoint(0,40), wxSize(200,50), wxBORDER_SIMPLE, _T("wxID_ANY"));
	KeyBindsMoveChoice = new wxChoice(KeyBindsPanel, ID_KEYCHOICE, wxPoint(8,8), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_KEYCHOICE"));
	KeyBindsMoveChoice->Append(_("Arrows"));
	KeyBindsMoveChoice->Append(_("WSAD"));
	KeyBindsMoveLabel = new wxStaticText(KeyBindsPanel, wxID_ANY, _("Movement\nKeys"), wxPoint(120,4), wxSize(70,40), wxALIGN_CENTRE, _T("wxID_ANY"));
	KeyBindsMoveLabel->SetForegroundColour(wxColour(255,255,255));
	GameLangPanel = new wxPanel(this, wxID_ANY, wxPoint(200,40), wxSize(200,50), wxBORDER_SIMPLE, _T("wxID_ANY"));
	GameLangChoise = new wxChoice(GameLangPanel, ID_LANGCHOICE, wxPoint(8,8), wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LANGCHOICE"));
	GameLangChoise->Append(_("Polski"));
	GameLangChoise->Append(_("English"));
	GameLangLabel = new wxStaticText(GameLangPanel, wxID_ANY, _("Language"), wxPoint(120,12), wxSize(70,40), wxALIGN_CENTRE, _T("wxID_ANY"));
	GameLangLabel->SetForegroundColour(wxColour(255,255,255));
	SpaceShootLabel = new wxStaticText(this, wxID_ANY, _("Label"), wxPoint(10,100), wxSize(380,20), wxALIGN_CENTRE, _T("wxID_ANY"));
	wxFont SpaceShootLabelFont(12,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Consolas"),wxFONTENCODING_DEFAULT);
	SpaceShootLabel->SetFont(SpaceShootLabelFont);
	Center();

	Connect(ID_BUTTONSAVE,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&OptionDialog::OnSaveOptionBtnClick);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&OptionDialog::OnDialogClose);
	//*)


    ///TODO Options uising int indexes
    this->KeyBindsMoveChoice->Select(this->KeyBindsMoveChoice->FindString(movement)); // Set Current Move Option
    this->GameLangChoise->Select(this->GameLangChoise->FindString(language)); // Set Current Language Option

    this->GameLangLabel->SetLabel(lang::lang.at(language).at("language_pick")); // Translated Language
    this->KeyBindsMoveLabel->SetLabel(lang::lang.at(language).at("movement_pick")); // Translated Movement
    this->SaveOptionBtn->SetLabel(lang::lang.at(language).at("save_options")); // Translated Saving Options
    this->GamePauseLabel->SetLabel(lang::lang.at(language).at("game_paused")); // Translated Game Paused Label
    this->SpaceShootLabel->SetLabel(lang::lang.at(language).at("space_button")); // Translated Game Paused Label

	this->movement = movement;
	this->language = language;
}

OptionDialog::~OptionDialog( void )
{
	//(*Destroy(OptionDialog)
	//*)
}

void OptionDialog::OnDialogClose(wxCloseEvent& event)
{
    this->Destroy();
}

void OptionDialog::SaveOptions( void )
{
    this->movement = std::string(this->KeyBindsMoveChoice->GetStringSelection().mb_str()); // Changing Movement Method
    this->language = std::string(this->GameLangChoise->GetStringSelection().mb_str()); // Changing Language
}

void OptionDialog::OnSaveOptionBtnClick(wxCommandEvent& event)
{
    this->SaveOptions();
    this->Destroy();
}
