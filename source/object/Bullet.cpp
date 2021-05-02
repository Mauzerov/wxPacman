/***************************************************************
 * Name:      Bullet.cp
 * Purpose:   Extends Bullet Class
 * Author:     ()
 * Created:   2021-03-17
 * Copyright:  ()
 * License:
 **************************************************************/
#include "object/Bullet.h"

extern unsigned int pixelSizeBit;
extern wxSize defaultSize;
extern Punkt TablicaPunktow[Punkt::MAX_PUNKTOW];
bool IsWall (int y, int x);

const unsigned int Bullet::SPEED = 14; // Static Speed
const unsigned short Bullet::TRAVEL_DISTANCE = 12; // Static Max Travel Distance

Bullet::Bullet(wxPanel* panel, int xx, int yy, char ddirection)
{
    this->TimerCount = 0; // Bullet Distance

    this->direction = ddirection;
    if (direction == 's' || direction == 'w')   bulletDirection = "Vertical";
    else                            bulletDirection = "Horizontal";

    this->X = (float)xx; // Class Global Position
    this->Y = (float)yy; // Class Global Position

    // Position & Other Stuff
    this->Image = new wxStaticBitmap( panel, wxID_ANY, wxNullBitmap, wxPoint(xx << pixelSizeBit, yy << pixelSizeBit), defaultSize, 0 );
    // Image
    this->Image->SetBitmap( wxBitmap(wxString::Format("PacmanImages\\Guns\\Bullet%s%d.bmp", bulletDirection, (!Punkt::Collide(xx,yy))+1), wxBITMAP_TYPE_BMP) );
}

Bullet::~Bullet( void )
{
    delete this->Image;
}

bool Bullet::Move( void ) // Movement Function
{
    switch (direction) { // Change Position Based By Current Direction
    case 'w':
        Y -= 1; break;
    case 's':
        Y += 1; break;
    case 'a':
        X -= 1; break;
    case 'd':
        X += 1; break;
    }
    if (!IsWall(Y, X)) {
        this->Image->SetPosition(wxPoint(x() << pixelSizeBit, y() << pixelSizeBit)); // New Position
        this->Image->SetBitmap(wxBitmap(wxString::Format("PacmanImages\\Guns\\Bullet%s%d.bmp", bulletDirection, (!Punkt::Collide(x(),y()))+1), wxBITMAP_TYPE_BMP));
        this->Image->Refresh(); // Overide On Top
    }
    else {
        return false; // Destroy Bullet When hit Wall
    }
    return true; // Return (true)
}
