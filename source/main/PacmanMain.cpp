/***************************************************************
 * Name:      PacmanMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2021-01-20
 * Copyright:  ()
 * License:
 **************************************************************/
#include <iostream>
#include "PacmanMain.h"
#include <wx/msgdlg.h>

//#include "codes.h"

//(*InternalHeaders(PacmanFrame)
#include <wx/bitmap.h>
#include <wx/font.h>
#include <wx/image.h>
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

extern Punkt TablicaPunktow[Punkt::MAX_PUNKTOW];

wxSize defaultSize = wxSize(16, 16); // Default Bitmap Size
bool gameOn = false;    // Switch Used To Chose Correct Timer
int MapaZPliku[25][50]; // int Map 2d Array
int pixelSize = 16;     // Default Image Pixel Size
unsigned int pixelSizeBit = 4;     // Default Image Pixel Size

const long long TOTALTIME = 900l;           // Max Time For Level Completion
long long timeInSecondsLeft = TOTALTIME;    // Begin Timer
long long timeInMSeconds = 0l;              //
short iloscKropek; // Dots Amount

wxStaticBitmap * MyMapaPac[25][50]; // Bitmap Pacman Map

//(*IdInit(PacmanFrame)
const long PacmanFrame::ChangeSettingID = wxNewId();
//*)
const long PacmanFrame::BULLET_TIMER_ID = wxNewId();
const long PacmanFrame::MAIN_TIMER_ID = wxNewId();
const long PacmanFrame::AGAIN_BTN_ID = wxNewId();
const long PacmanFrame::CLOSE_GAME_ID = wxNewId();

const unsigned short PacmanFrame::MAX_LEVEL = 2;    // Level Amount

BEGIN_EVENT_TABLE(PacmanFrame,wxFrame)
    //(*EventTable(PacmanFrame)
       EVT_KEY_DOWN(PacmanFrame::OnKeyDown)
       EVT_ACTIVATE(PacmanFrame::OnActivate)
    //*)
       EVT_TIMER( MAIN_TIMER_ID, PacmanFrame::OnTimer )         // Main Timer Event
       EVT_TIMER( BULLET_TIMER_ID, PacmanFrame::OnBulletTimer ) // Bullet Timer Event
END_EVENT_TABLE()

bool IsWall (int y, int x) {
    return MapaZPliku[y][x] == 177;
    }

PacmanFrame::PacmanFrame(wxWindow* parent, wxWindowID id)
{
    srand( time(nullptr) ); // Random Randomiser
    std::fstream file;      // Main File Handler Declarartion

    //(*Initialize(PacmanFrame)
    Create(parent, wxID_ANY, _("Pacman"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxMINIMIZE_BOX|wxBORDER_SIMPLE|wxWANTS_CHARS|wxCLIP_CHILDREN, _T("wxID_ANY"));
    SetClientSize(wxSize(800,454));
    SetFocus();
    SetForegroundColour(wxColour(0,0,0));
    SetBackgroundColour(wxColour(0,0,0));
    wxFont thisFont(12,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Consolas"),wxFONTENCODING_DEFAULT);
    SetFont(thisFont);
    BottomPanel = new wxPanel(this, wxID_ANY, wxPoint(0,418), wxSize(800,36), 0, _T("wxID_ANY"));
    BottomPanel->SetForegroundColour(wxColour(255,255,255));
    BottomPanel->SetBackgroundColour(wxColour(0,0,0));
    Score = new wxStaticText(BottomPanel, wxID_ANY, _("Score:"), wxPoint(0,0), wxSize(120,16), 0, _T("wxID_ANY"));
    PlayerScore = new wxStaticText(BottomPanel, wxID_ANY, _("0"), wxPoint(120,0), wxSize(280,16), 0, _T("wxID_ANY"));
    HighScore = new wxStaticText(BottomPanel, wxID_ANY, _("High Score:"), wxPoint(0,16), wxSize(120,20), 0, _T("wxID_ANY"));
    PlayerHighScore = new wxStaticText(BottomPanel, wxID_ANY, _("0"), wxPoint(120,16), wxSize(280,20), 0, _T("wxID_ANY"));
    TextInfo1 = new wxStaticText(BottomPanel, wxID_ANY, _("Press \'Enter\' To Release"), wxPoint(550,0), wxSize(250,16), wxALIGN_CENTRE, _T("wxID_ANY"));
    TextInfo2 = new wxStaticText(BottomPanel, wxID_ANY, _("Use Arrows To Move"), wxPoint(550,16), wxSize(250,16), wxALIGN_CENTRE, _T("wxID_ANY"));
    TextAuthor = new wxStaticText(BottomPanel, wxID_ANY, _("GAME PAUSED"), wxPoint(400,0), wxSize(150,36), wxALIGN_CENTRE, _T("wxID_ANY"));
    TextAuthor->SetForegroundColour(wxColour(120,120,120));
    UpperPanel = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(800,18), 0, _T("wxID_ANY"));
    UpperPanel->SetForegroundColour(wxColour(255,255,255));
    UpperPanel->SetBackgroundColour(wxColour(0,0,0));
    TextTimeLeft = new wxStaticText(UpperPanel, wxID_ANY, _("Time Left:"), wxPoint(20,0), wxSize(100,18), 0, _T("wxID_ANY"));
    TimeLeftTime = new wxStaticText(UpperPanel, wxID_ANY, _("0"), wxPoint(120,0), wxSize(120,18), 0, _T("wxID_ANY"));
    TextMaxKropek = new wxStaticText(UpperPanel, wxID_ANY, _("/ 0"), wxPoint(720,0), wxSize(50,18), 0, _T("wxID_ANY"));
    TextCurrentKropek = new wxStaticText(UpperPanel, wxID_ANY, _("0"), wxPoint(660,0), wxSize(50,18), wxALIGN_RIGHT, _T("wxID_ANY"));
    ChangeSettingBtn = new wxBitmapButton(UpperPanel, ChangeSettingID, wxBitmap(wxImage(_T("PacmanImages\\Icon\\settings_mark.png"))), wxPoint(0,0), wxSize(20,20), wxBU_AUTODRAW|wxTRANSPARENT_WINDOW, wxDefaultValidator, _T("ChangeSettingID"));
    ChangeSettingBtn->SetBitmapDisabled(wxBitmap(wxImage(_T("PacmanImages\\Icon\\settings_mark.png"))));
    ChangeSettingBtn->SetBitmapSelected(wxBitmap(wxImage(_T("PacmanImages\\Icon\\settings_mark.png"))));
    ChangeSettingBtn->SetBitmapFocus(wxBitmap(wxImage(_T("PacmanImages\\Icon\\settings_mark.png"))));
    Center();

    Connect(ChangeSettingID,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PacmanFrame::OnChangeSettingBtnClick);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&PacmanFrame::OnClose);
    //*)
    MainMapPanel = new wxPanel(this, wxID_ANY, wxPoint(0,18), wxSize(800,400), 0);
    MainMapPanel->Hide();

    // End Screen Panel
    EndScreenPanel = new wxPanel(this, wxID_ANY, wxPoint(0,18), wxSize(800,400),0);
    EndScreenPanel->SetBackgroundColour(wxColour(0,0,0));       // Change Background Color
    EndScreenPanel->SetForegroundColour(wxColour(255,255,255)); // Change Text Color
    EndScreenPanel->Hide();

    wxFont EndScreenFont(28,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Consolas"),wxFONTENCODING_DEFAULT); // Create Global Panel Font
    EndScreenPanel->SetFont(EndScreenFont);
    wxFont EndScreenButton(14,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Consolas"),wxFONTENCODING_DEFAULT); // Create Button Font

    // End Screen Panel Elements
    ExitButton = new wxButton(EndScreenPanel, CLOSE_GAME_ID,
                            wxString(lang::lang.at(this->language).at("close_button")), wxPoint(150, 200), wxSize(100,50), 0);
    ExitButton->SetFont(EndScreenButton);
    AgainButton = new wxButton(EndScreenPanel, AGAIN_BTN_ID,
                            wxString(lang::lang.at(this->language).at("again_button")),wxPoint(800-150-100,200), wxSize(100,50), 0);
    AgainButton->SetFont(EndScreenButton);
    EndScreenLabel = new wxStaticText(EndScreenPanel, wxID_ANY,
                            wxString(lang::lang.at(this->language).at("end_text")), wxPoint(100, 100), wxSize(600,100), wxALIGN_CENTRE);

    Connect(CLOSE_GAME_ID,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PacmanFrame::OnExitBtnClick ); // Connect Events To Buttons
    Connect(AGAIN_BTN_ID, wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PacmanFrame::OnAgainBtnClick); // Connect Events To Buttons
    // File handler

    this->ChangeMap(); // Generate Everything => Map, Ghosts, Player, Points

    this->main_timer = new wxTimer( this, MAIN_TIMER_ID );      // Main Timer Delaration
    this->bullet_timer = new wxTimer( this, BULLET_TIMER_ID );  // Bullet Timer Delaration

    // TODO HighScore -> FileHandler ( JSON Possibility )
    file.open("scoreboard.txt"); // Opening Highscore From File
    unsigned long long int score = 0;
    file >> score; file.close();

    this->PlayerHighScore->SetLabel( _(wxString::Format("%llu",score)) ); // Setting Highscore Label To Highscore
                                                                                              // if file is not empty else '0'
    // End File Handler

    // Showing Everything & Other Stuff
    this->MainMapPanel->Show();     // Showing Main Map Panel
    this->player.Image->Refresh();  // Player On top of window

    this->ChangeLanguage();         // Changing Every Setted Label To Chosen Language
    this->main_timer->Start(500);   // Game Is Paused By Default -> Animated Pause Menu

    file.close();
}

PacmanFrame::~PacmanFrame( void )
{
    UpperPanel  ->Hide(); // Hiding Score Panel
    BottomPanel ->Hide(); // Hiding Info Panel
    MainMapPanel->Hide(); // Hinding Main Map Panel

    /// Score Saving \TODO(Transfer to \JSON format)
    // Reading Current Highscore
    std::fstream file; file.open("scoreboard.txt", std::ios::in);
        unsigned long long int highScore = 0; file >> highScore;
        file.close(); // Closing Current File

    // Overiding Current Highscore with new if higher
    file.open("scoreboard.txt", std::ios::out);
        std::cout << highScore << " " << this->player.getScore() << std::endl;
        file.clear();   // Clear Current File
        file << this->player.getScore() * (highScore <= this->player.getScore()) // Branchless High Score Change
            + highScore * (highScore > this->player.getScore());
    file.close(); // Close Current File

    this->main_timer->Stop();
    this->bullet_timer->Stop();

    delete main_timer;      //
    delete bullet_timer;    // No Error In Console After Closing
    delete MainMapPanel;    // No Error In Console After Closing

    //(*Destroy(PacmanFrame)
    //*)

    Destroy();
}

int PacmanFrame::LiczKropki( void ) // Amount Of Dots On Current Map For Another Level Handler
{
    #ifdef PACMAN_DEBUG
    return 32; //std::min(32,std::abs(iloscKropek-520));
    #else
    return iloscKropek;
    #endif
}

void PacmanFrame::ChangeLanguage( void ) // Changes Every Setted Label To Chosen Language
{
    // Using std::map To Get Text In Different Languages
    this->TextInfo1->SetLabel( wxString(lang::lang.at(this->language).at("info_text_start")) ); // Button To Start Label
    this->TextTimeLeft->SetLabel( wxString(lang::lang.at(this->language).at("time_left")) ); // Time Left Label
    this->TextInfo2->SetLabel( wxString(lang::lang.at(this->language).at(
                                (movement == "Arrows")? "info_text_move_arrow": "info_text_move_wsad")) ); // Movement Method Label

    this->Score->SetLabel( wxString(lang::lang.at(this->language).at("score")) );          // Score Label
    this->HighScore->SetLabel( wxString(lang::lang.at(this->language).at("high_score")) ); // Highscore Label
    this->TextAuthor->SetLabel( wxString(lang::lang.at(language).at("game_paused")) );     // Game Paused Label

    this->ExitButton->SetLabel( wxString(lang::lang.at(language).at("close_button")) );  // Close Button Label
    this->AgainButton->SetLabel( wxString(lang::lang.at(language).at("again_button")) ); // Again Button Label
    this->EndScreenLabel->SetLabel( wxString(lang::lang.at(language).at("end_text")) );  // Victory Label
}

void PacmanFrame::OpenNewMap(std::fstream& file) // Open Map From File To int & Bitmap Array
{
    // File Handler
    if (!file.good()) this->Close();
    int mapa_x, mapa_y; // Map Size Declaration
    file >> mapa_y >> mapa_x; // Reading Map Size

    for (int y = 0; y< mapa_y; y++)
        for (int x = 0; x< mapa_x; x++)
            file >> MapaZPliku[y][x]; // Reading Map

    file.close();
    // End File Handler

    ::iloscKropek = 0;
    { // Bitmap Current Map
        for (int y = 0; y < mapa_y; y++){ //
            for (int x = 0; x < mapa_x; x++){
                // Wall Or Coin
                if (::MapaZPliku[y][x] == 177){
                    // Wall Image
        ::MyMapaPac[y][x] = new wxStaticBitmap(MainMapPanel, wxID_ANY, wxBitmap("PacmanImages\\Wall2.bmp",wxBITMAP_TYPE_BMP),
                                               wxPoint(x << pixelSizeBit, y << pixelSizeBit), defaultSize, 0);

                } else if (::MapaZPliku[y][x] == 32){
                    // Coin Image ( Next Level Handler )
        ::MyMapaPac[y][x] = new wxStaticBitmap(MainMapPanel, wxID_ANY, wxBitmap("PacmanImages\\Coin2.bmp",wxBITMAP_TYPE_BMP),
                                               wxPoint(x << pixelSizeBit, y << pixelSizeBit), defaultSize, 0);

                }
                (::MyMapaPac[y][x])->SetBackgroundColour(wxColour(0,0,0)); // Black Background For Image

                // Amount Of Dots On Current Map For Another Level Handler
                ::iloscKropek += (MapaZPliku[y][x] == 32);                          // Add 1 If Current Element Is Empty
                ::MapaZPliku[y][x] = int('.') * (::MapaZPliku[y][x] == 32)          // Branchless Change Map Element
                                 + ::MapaZPliku[y][x] * (::MapaZPliku[y][x] != 32); // Change Map Element To Dot

            }
        }
    }

    ::iloscKropek = LiczKropki(); // Chnage Amount Of Dots On Current Map

    Punkt::GeneratorPunktow(this->MainMapPanel, Punkt::MAX_PUNKTOW); // Create Point In Random Positions

    /// Timer Reset                  ///
    ::timeInSecondsLeft = TOTALTIME; ///
    ::timeInMSeconds = 0l;           ///
}

bool PacmanFrame::ChangeMap( void )
{
    this->levelName++; // Change Level Name
    if (this->levelName > PacmanFrame::MAX_LEVEL) {
        return false; // Return False When Map Limit Reached
    }

    { // Check if Exist Another Level
        MainMapPanel->Hide(); // Hide Paneld Holding Map
        // Delete Existing Map Image
        for (int i = 0; i < 25; i++)
            for (int j = 0; j < 50; j++) delete ::MyMapaPac[i][j];
        // Delete Points Images
        for (unsigned int i = 0; i < Punkt::MAX_PUNKTOW; i++) delete ::TablicaPunktow[i].Image;

        std::fstream file; // Opening Map
        file.open(std::string(wxString::Format("mapa_%d.txt", this->levelName).mb_str()),std::ios::in);
        this->OpenNewMap( file ); // Creating Map From Bitmap Fragments Represented By Integers In .txt File

        file.close();
        // Changing Text Labels
        this->TimeLeftTime->SetLabel(_(wxString::Format("%lld:%s%lld", timeInSecondsLeft / 60, (timeInSecondsLeft % 60 / 10)?"":"0", timeInSecondsLeft % 60)));

        this->TextMaxKropek->SetLabel( _(wxString::Format("/ %d", iloscKropek)) );  // Dots Amount On Current Level
        this->TextCurrentKropek->SetLabel( _(wxString::Format("%d", iloscKropek)) ); // Dots To Collect Til Next Level

        // Player Declaration
        /// Random Player Position
        this->player.position_generator();
        this->player.setDirection('d');
        this->player.setVelocity(0.75f);
        this->player.resetTimer();

        delete this->player.Image;
        this->player.setImage(new wxStaticBitmap( //
            MainMapPanel, wxID_ANY, wxBitmap( "PacmanImages\\Player\\pacman_close_right.bmp", wxBITMAP_TYPE_BMP ),  // Player Image
            wxPoint( player.x() << pixelSizeBit, player.y() << pixelSizeBit ), defaultSize, 0));                    // Player Position

        /// Random Positions For Ghosts
        for (int i = 0; i < 4; i++) {
            // Random Ghost Position
            do {
                this->ghost[i].position_generator();
            } while (player.startCollide( ghost[i] ));
            this->ghost[i].setVelocity(0.75f);
            // Delete Current Image
            delete this->ghost[i].Image;
            // New Ghost Image
            this->ghost[i].setImage(new wxStaticBitmap(MainMapPanel, wxID_ANY, //
                        wxBitmap( wxString::Format("PacmanImages\\Ghost%d.bmp",i+1),wxBITMAP_TYPE_BMP ),            // Ghost Image
                        wxPoint( ghost[i].x() << pixelSizeBit, ghost[i].y() << pixelSizeBit ), defaultSize, 0));    // Ghost Position
            this->ghost[i].Image->Refresh();
        }

    }
    this->TextAuthor->SetLabel( _(lang::lang.at(language).at("game_paused")) ); // Game Paused Label
    MainMapPanel->Show(); // Show Panel Holding Map
    return true; // Return True When Nothing Goes Wrong

}

void PacmanFrame::DestroyBullet( void ) // Destroys Bullet -> Called From Timer
{
    delete this->bullet;        // Deletes Bullot From Map
    this->bullet = nullptr;     /// used In if Statement In \Events
    this->bullet_timer->Stop(); // Stops Bullet Movement
}

void PacmanFrame::OptionDialogCreate( void ) // Create Option Menu
{
    this->OptionDialogDialog = new OptionDialog(this, wxID_ANY, this->movement, this->language); // Create new Option Menu
}
