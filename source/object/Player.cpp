/***************************************************************
 * Name:      player.h
 * Purpose:   Extends Player Class
 * Author:     ()
 * Created:   2021-02-10
 * Copyright:  ()
 * License:
 **************************************************************/

#include "object/Entity.h"

#ifndef MUR
#define MUR 177
#endif

extern int MapaZPliku[25][50];
extern wxStaticBitmap * MyMapaPac[25][50];
extern unsigned int pixelSizeBit;
extern const long long TOTALTIME;
extern long long timeInSecondsLeft;
extern int iloscKropek;

Player::Player(wxStaticBitmap *img) // Constructor
{
    this->Image = img;
}

void Player::changeState( void ) // Change Current Animation State
{
    this->state ^= true;
}

/// Get \ Set Values
float Player::getSpeedBuffer( void )
{
    return this->speedBuff;
}

void Player::setSpeedBuffer( void )
{
    this->speedBuff = Player::SPEED_BUFF;
    this->speedtimer = 300;
}

float Player::getSlowBuffer( void )
{
    return this->slowBuff;
}

void Player::setSlowBuffer( void )
{
    this->slowBuff = Player::SLOW_BUFF;
    this->slowtimer = 150;
}
void Player::resetTimer( void )
{
    this->slowtimer = 0;
    this->speedtimer = 0;
}


/// End Get \ Set Values
void Player::check_buffs( void )
{
    // Speed Timer - Buff
    this->speedtimer-= (speedtimer > 0);
    this->speedBuff = (this->speedtimer <= 0) + Player::SPEED_BUFF * (this->speedtimer > 0);
    // Slow Timer - Buff
    this->slowtimer-= (slowtimer > 0);
    this->slowBuff = (this->slowtimer <= 0) + Player::SLOW_BUFF * (this->slowtimer > 0);

}

void Player::setScore(unsigned long long int s) // Set Score Function
{
    this->Score = s;
}

void Player::addScore(unsigned long long int s) // Add Score Function
{
    this->Score += s;
}

unsigned long long int Player::getScore( void ) // Get Score Function
{
    return this->Score;
}

void Player::setPosition(std::pair<float,float> pos) // Set Position Function
{
    this->X = pos.first;
    this->Y = pos.second;
}

void Player::Move( void ) // Main Move Function
{
        this->check_buffs(); // Buffs Timer
        this->changeState(); // Animation

        // Animation State
        std::string states[2] = {
            "close", "open"
        };
        // Moving In Correct Direcition
        switch ( this->direction ){

            case 's': // Move Down
                if (MapaZPliku[(int)Y + 1][(int)X]!= MUR){
                    this-> Y+=v * speedBuff * slowBuff; // Change position
                    // Change Image (Animation)
                    this->Image->SetBitmap(wxBitmap(wxString::Format("PacmanImages\\Player\\pacman_%s_down.bmp", states[this->state]), wxBITMAP_TYPE_BMP));
                }
                break;

            case 'w': // Move Up
                if (MapaZPliku[(int)Y - 1][(int)X]!= MUR){
                    this-> Y-=v * speedBuff * slowBuff; // Change position
                    // Change Image (Animation)
                    this->Image->SetBitmap(wxBitmap(wxString::Format("PacmanImages\\Player\\pacman_%s_up.bmp", states[this->state]), wxBITMAP_TYPE_BMP));
                }
                break;

            case 'a': // Move Left
                if (MapaZPliku[(int)Y][(int)X- 1]!= MUR){
                    this-> X-=v * speedBuff * slowBuff; // Change position
                    // Change Image (Animation)
                    this->Image->SetBitmap(wxBitmap(wxString::Format("PacmanImages\\Player\\pacman_%s_left.bmp", states[this->state]), wxBITMAP_TYPE_BMP));
                }
                break;

            case 'd': // Move Right
                if (MapaZPliku[(int)Y][(int)X+ 1]!= MUR){
                    this-> X += v * speedBuff * slowBuff; // Change position
                    // Change Image (Animation)
                    this->Image->SetBitmap(wxBitmap(wxString::Format("PacmanImages\\Player\\pacman_%s_right.bmp", states[this->state]), wxBITMAP_TYPE_BMP));
                }
                break;
        };
        std::cout << v * speedBuff * slowBuff << std::endl;

        if (last_x == x() && last_y == y()) {

        } else {
            // Moving Player To New Spot & Changing Last Tile to Empty Square
            wxPoint tmp = this->Image->GetPosition();
            tmp.x = this->x() << pixelSizeBit;
            tmp.y = this->y() << pixelSizeBit;

            this->Image->SetPosition(tmp);
            if (MapaZPliku[ last_y ][ last_x ] == int('.')) iloscKropek--;

            MapaZPliku[ last_y ][ last_x ] = 32;
            MyMapaPac [ last_y ][ last_x ] -> SetBitmap(wxBitmap("PacmanImages\\Empty.bmp",wxBITMAP_TYPE_BMP));
            this->Image->Refresh();
            // End Moving Player Image

            //TODO more stuff
            tmp = MyMapaPac[this->y()][this->x()]->GetPosition();

            last_x = x(); last_y = y();
        }
}

