/***************************************************************
 * Name:      PacmanMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2021-02-03
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef PACMANMAIN_H
#define PACMANMAIN_H

#include "other/Codes.h"

#include <wx/timer.h>
#include <wx/statbmp.h>
#include <wx/dialog.h>
//(*Headers(PacmanFrame)
#include <wx/bmpbuttn.h>
#include <wx/frame.h>
#include <wx/panel.h>
#include <wx/stattext.h>
//*)
#include "OptionDialog.h"
#include "object/Entity.h"
#include "object/Points.h"
#include "object/Bullet.h"

#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

class PacmanFrame: public wxFrame
{
    public:
        PacmanFrame(wxWindow* parent,wxWindowID id = -1); // Constructor
        virtual ~PacmanFrame( void ); // Destructor
        void OnTimer(wxTimerEvent& event); // Main Timer Function
        void OnBulletTimer(wxTimerEvent& evt); // Bullet Timer Function

        static int LiczKropki( void ); // Amount Of Dots On Current Map For Another Level Handler
    protected:
        static const long BULLET_TIMER_ID;
        static const long MAIN_TIMER_ID;
        static const unsigned short MAX_LEVEL;

    private:
        wxTimer *main_timer; // Timer Declaration
        wxTimer *bullet_timer; // Timer Declaration
        //(*Handlers(PacmanFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnLewyBTNClick(wxCommandEvent& event);
        void OnprawyBTNClick(wxCommandEvent& event);
        void OnKeyDown(wxKeyEvent& event);
        void OnActivate(wxActivateEvent& event);
        void OnButtonHelpClick(wxCommandEvent& event);
        void OnChangeSettingBtnClick(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        //*)
        void OnExitBtnClick(wxCommandEvent& evt);
        void OnAgainBtnClick(wxCommandEvent& evt);

        //(*Identifiers(PacmanFrame)
        static const long ChangeSettingID;
        //*)
        static const long CLOSE_GAME_ID;
        static const long AGAIN_BTN_ID;

        //(*Declarations(PacmanFrame)
        wxBitmapButton* ChangeSettingBtn;
        wxPanel* BottomPanel;
        wxPanel* UpperPanel;
        wxStaticText* HighScore;
        wxStaticText* PlayerHighScore;
        wxStaticText* PlayerScore;
        wxStaticText* Score;
        wxStaticText* TextAuthor;
        wxStaticText* TextCurrentKropek;
        wxStaticText* TextInfo1;
        wxStaticText* TextInfo2;
        wxStaticText* TextMaxKropek;
        wxStaticText* TextTimeLeft;
        wxStaticText* TimeLeftTime;
        //*)
        wxButton * AgainButton;
        wxButton * ExitButton;
        wxStaticText * EndScreenLabel;

        std::string movement = "Arrows"; // Global Movement Method
        std::string language = "Polski"; // Global App Language

        unsigned short levelName = 0;
        wxPanel* MainMapPanel; // Main panel For Map
        wxPanel* EndScreenPanel; // End Screen Panel
        OptionDialog * OptionDialogDialog; // Option Menu

        void OpenNewMap(std::fstream& file); // Open Map From File To int & Bitmap Array
        bool ChangeMap( void );
        void LiczPunkty(int punkty); // Check if Player Stands On Point => Do Point Stuff
        void OptionDialogCreate( void ); // Create Option Menu

        void ChangeLanguage( void ); // Changes Every Setted Label To Chosen Language
        void DestroyBullet( void ); // Changes Every Setted Label To Chosen Language

        wxStaticBitmap *test_point; // Test Point
        DECLARE_EVENT_TABLE() // Event Table

        Player player; // Player Declaration
        Ghost ghost[4]; // Ghosts Declaration
        Bullet *bullet; // Bullet Declaration

        bool GamePausedSwith = true; // Animated Game Pause Label
};

#endif // PACMANMAIN_H
