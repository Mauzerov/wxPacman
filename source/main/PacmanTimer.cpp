/***************************************************************
 * Name:      PacmanTimer.cpp
 * Purpose:   Handles Timer
 * Author:     ()
 * Created:   2021-02-25
 * Copyright:  ()
 * License:
 **************************************************************/

#include "PacmanMain.h"

extern bool gameOn;
extern long long timeInMSeconds;
extern long long timeInSecondsLeft;
extern int iloscKropek;
extern unsigned int pixelSizeBit;
extern Punkt TablicaPunktow[Punkt::MAX_PUNKTOW];

/// Compact Check If Entity (Player) or Bullet Collides With Point
inline bool operator==(Entity& entity, Punkt & point) {
    return entity.x() == point.x && entity.y() == point.y;
}
inline bool operator==(Entity& bullet, Entity & ghost) {
    return bullet.x() == ghost.x() && bullet.y() == ghost.y();
}

/// Class Function
void PacmanFrame::LiczPunkty(int punkty) { // Check if Player Stands On Point => Do Point Stuff
    for (int i = 0; i < punkty; i++) {
        // Check If Position Is Same
        if (player == TablicaPunktow[i]) {
            switch (TablicaPunktow[i].Wartosc) {
            case Punkt::SPEED_BUFF: // Check if Point is Speed
                // TODO Speed
                player.setSpeedBuffer();
                break;
            case Punkt::SLOW_BUFF: // Check if Point is Slow
                // TODO Slow
                player.setSlowBuffer();
                break;
            default: // Default Value is Score
                this->player.addScore(TablicaPunktow[i].Wartosc);
                break;
            }
            // Prevents Crash After Some Time
            delete TablicaPunktow[i].Image;

            // New Point & Image for it
            TablicaPunktow[i] = Punkt::Nastepny_Punkt( this->MainMapPanel );
            break; // Speed Up. End Loop If Finds
        }
    }
}

void PacmanFrame::OnTimer(wxTimerEvent & event)
{
    if (gameOn == true){
        // Subtracting Time For Completion
        timeInMSeconds+= event.GetInterval();
        if (timeInMSeconds % 1000 != timeInMSeconds) {
            timeInSecondsLeft -= timeInMSeconds / 1000;
            timeInMSeconds %= 1000;
            this->TimeLeftTime->SetLabel(_(wxString::Format("%lld:%s%lld", timeInSecondsLeft / 60, (timeInSecondsLeft % 60 / 10)?"":"0", timeInSecondsLeft % 60)));
        }
        // End Game When Hits Zero
        if (timeInSecondsLeft < 0)
        {
            main_timer->Stop();
            bullet_timer->Stop();
            this->Close();
        }
    /// else
        { // Entity Movement
            this->player.Move(); // Moving Player

            // Ghosts
            for (int i = 0; i < 4; i++) {
                if (player == ghost[i]) // Ghosts Kill Player When On Same Spot
                {
                    main_timer->Stop();
                    bullet_timer->Stop();
                    Close();
                }
                this->ghost[i].Move(player); // Moving Ghost
                if (player == ghost[i]) // Ghosts Kill Player When On Same Spot
                {
                    main_timer->Stop();
                    bullet_timer->Stop();
                    Close();
                }
                this->ghost[i].Image->Refresh(); // Put Ghost On Top
            }
            // End Ghosts
            this->player.Image->Refresh(); // Put Player On Top
        }
        // New Dots Amount
        this->TextCurrentKropek->SetLabel( _(wxString::Format("%d",iloscKropek)) );
        this->TextCurrentKropek->Refresh();
        if (iloscKropek == 0) {             // Open New Map When No Dots To Collect
            if (ChangeMap() == true) {      // If Can Open New Game Stops Timer

            } else { // Else End Screen
                this->MainMapPanel->Hide();

                this->EndScreenPanel->Show();
                this->EndScreenPanel->Refresh();
                this->EndScreenPanel->Update();
            }
            ::gameOn ^= true;               // Toggle Variable Used In Events & Timer
            this->main_timer->Stop();       // Toggle Timer
        }
        // Point Checker
        std::cout << this->player.Y << " " << this->player.X << " " << iloscKropek << std::endl;
        {
            this->LiczPunkty(Punkt::MAX_PUNKTOW); // Check if Player Stands On Point => Do Point Stuff
            this->PlayerScore->SetLabel( _(wxString::Format("%llu", this->player.getScore())) ); // New Player Score
        }

        // Ghost Movement
    }
    else { // Game Paused
        GamePausedSwith ^= true;
        this->TextAuthor->SetForegroundColour( (GamePausedSwith != true)? wxColour(243, 156, 18) : wxColour(230, 126, 34) ); // Toggle Between Colors
        this->TextAuthor->Refresh(); // Update Colors
    }
}

void PacmanFrame::OnBulletTimer(wxTimerEvent & evt)
{
    std::cout << "bullet timer\n";
    if (this->bullet->TimerCount++ <= Bullet::TRAVEL_DISTANCE) {
        if(this->bullet->Move()) { // Check If Move Function End Correctly
            for (int i = 0; i < 4; i++) { // Check If Bullet Collides With Ghost
                if (*bullet == ghost[i]) {
                    // New Random Ghost Position (kill)
                    do {
                        this->ghost[i].position_generator( ); // Random Position Generator
                    } while ( player.startCollide( ghost[i] ) ); // Ghosts Cannot Span on same axes as player
                    // Set Right Position
                    this->ghost[i].Image->SetPosition( wxPoint(ghost[i].x() << pixelSizeBit, ghost[i].y() << pixelSizeBit) );

                    this->DestroyBullet(); // Hits Entity
                    break; // Bullet Can't Kill More Then One Ghost At Once
                }
            }
        } else { // Destroy Bullet & Stop Bullet ovement Timer
            this->DestroyBullet(); // Hits Wall
        }
    } else { // Destroy Bullet & Stop Bullet Movement Timer
        this->DestroyBullet(); // Lost Velocity (Real Life)
    }
}
