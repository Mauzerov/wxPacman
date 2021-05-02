/***************************************************************
 * Name:      Bullet.h
 * Purpose:   Defines Bullet Class
 * Author:     ()
 * Created:   2021-03-17
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef PACMAN_BULLET_H
#define PACMAN_BULLET_H

#include "Points.h"
#include "Entity.h"

#include <wx/statbmp.h>
#include <wx/panel.h>
#include <string>

class Bullet : public Entity{

    public: static const unsigned int SPEED; // Static Speed
    public: static const unsigned short TRAVEL_DISTANCE; // Static Speed
    public: unsigned short TimerCount; // Static Speed

    public: Bullet(wxPanel* panel, int xx, int yy, char ddirection); // Constructor
    public: virtual ~Bullet( void );  // Destructor


    private: std::string bulletDirection; // Horizonta / Vertical For Image Rendering

    public: bool Move( void ); // Movement Function
};

#endif // PACMAN_BULLET_H
