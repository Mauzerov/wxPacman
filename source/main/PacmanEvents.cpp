/***************************************************************
 * Name:      PacmanEvents.cpp
 * Purpose:   Handles Events
 * Author:     ()
 * Created:   2021-02-25
 * Copyright:  ()
 * License:
 **************************************************************/

#include "PacmanMain.h"

extern bool gameOn;

void PacmanFrame::OnKeyDown(wxKeyEvent& event){

    int pressedKeyCode = event.GetKeyCode();
    std::cout << "Key Code Pressed: "<< pressedKeyCode << std::endl;

    if (pressedKeyCode == key::codes_misc.at("esc")) { /// Pause Game Option
        gameOn ^= true; // Toggle

        if (gameOn == false) {
            this->main_timer->Stop(); // Stop Interval ( OnTimer function )

            this->TextInfo1->SetLabel( _(lang::lang.at(language).at("info_text_start")) );
            this->TextAuthor->SetLabel( _(lang::lang.at(language).at("game_paused")) ); // Game Paused Label
            this->TextAuthor->SetForegroundColour(wxColour(243, 156, 18)); // Game Paused Font Color
            this->main_timer->Start(500); // Start Animated Game Pause Label
            this->bullet_timer->Stop(); // Start Animated Game Pause Label
        }
        else {
            this->main_timer->Stop(); // Stop Animated Game Pause Label
            this->main_timer->Start(400); // Start Interval ( OnTimer function )
            if (this->bullet != nullptr) {
                std::cout << "goes here";
                this->bullet_timer->Start(main_timer->GetInterval() / Bullet::SPEED); // Start Interval ( OnTimer function )
                std::cout << " end here\n";
            }

            this->SetTitle("Pacman");
            this->TextInfo1->SetLabel( _(lang::lang.at(language).at("info_text_stop")) ); // Change Language of Button to pause Game
            this->TextAuthor->SetLabel( _(wxString::Format("%s:\nMateusz Mazurek", lang::lang.at(language).at("author"))) ); // Author Label
            this->TextAuthor->SetForegroundColour(wxColour(120, 120, 120)); // Author Font Color

        }
    }
    /// Bullet Movement & Colisions
    if (pressedKeyCode == key::codes_misc.at("space") && gameOn) {
        if (bullet_timer->IsRunning()) {
        }
        else {
            bullet = new Bullet(MainMapPanel, player.x(), player.y(), player.getDirection());
            bullet_timer->Start(main_timer->GetInterval() / Bullet::SPEED);
        }
    }

    /// Player Movement
    if (pressedKeyCode == key::codes_move.at(this->movement).at("down") && gameOn) { // Down
        this->player.setDirection('s'); // Change Player Direction
    }
    if (pressedKeyCode == key::codes_move.at(this->movement).at("up") && gameOn) { // Up
        this->player.setDirection('w'); // Change Player Direction
    }
    if (pressedKeyCode == key::codes_move.at(this->movement).at("right") && gameOn) { // Right
        this->player.setDirection('d'); // Change Player Direction
    }
    if (pressedKeyCode == key::codes_move.at(this->movement).at("left") && gameOn) { // Left
        this->player.setDirection('a'); // Change Player Direction
    }

    /// System Settings
    /// Exit On `Enter` when \DEBUG on
    #ifndef PACMAN_DEBUG
        if (false)
    #endif
    if (pressedKeyCode == key::codes_misc.at("enter") && gameOn == false) {
        this->Close(); // Close Game On Pressed Button
    }
}
///
///         OTHER FUNCTIONS
///

void PacmanFrame::OnChangeSettingBtnClick(wxCommandEvent& event)
{
    if (gameOn == false)
    {

        this->OptionDialogCreate();             // Create Option Menu
        this->OptionDialogDialog->ShowModal();  // Show Option Dialog
        this->movement = this->OptionDialogDialog->movement; // Change Global Language Variable
        this->language = this->OptionDialogDialog->language; // Change Global Language Variable

        this->ChangeLanguage(); // Changes Every Setted Label To Chosen Language

    }
    this->SetFocus();
}
void PacmanFrame::OnExitBtnClick(wxCommandEvent& evt) {
    this->Close();
}

void PacmanFrame::OnAgainBtnClick(wxCommandEvent& evt) {
    this->levelName = 0;
    this->EndScreenPanel->Hide();
    this->ChangeMap();
    this->SetFocus();
}

void PacmanFrame::OnButtonHelpClick(wxCommandEvent& event)
{
    this->SetFocus();
}

// Set Focun On App When Clicked Away & Back
void PacmanFrame::OnActivate(wxActivateEvent& event) {
    if (event.GetActive() == true){
        this->SetFocus();
    }
}

void PacmanFrame::OnClose(wxCloseEvent& event)
{
    this->main_timer->Stop();   // No Error In Console After Closing
    this->bullet_timer->Stop(); // No Error In Console After Closing

    Destroy();
}

void PacmanFrame::OnAbout(wxCommandEvent& event)
{
}
