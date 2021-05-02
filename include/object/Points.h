/***************************************************************
 * Name:      Points.h
 * Purpose:   Defines Punkt Class
 * Author:     ()
 * Created:   2021-03-17
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef PACMAN_POINTS_H
#define PACMAN_POINTS_H

#include <wx/statbmp.h>
#include <wx/panel.h>

#ifndef MAP_X
#define MAP_X 50
#define MAP_Y 25
#endif

class Punkt{

    public: static const unsigned int MAX_PUNKTOW = 50;

    public: static const unsigned int SPEED_BUFF = 6;
    public: static const unsigned int SLOW_BUFF = SPEED_BUFF - 1;
    public: static const unsigned int MAX_BUFF_VALUE = SPEED_BUFF;
    /** INFORMATION
    *   Wartosc 6 = speed buff
    *   Wartosc 5 = slow buff
    *   Wartosc 1-4 = 1-4 punky do wyniku
    **/

    protected: void change_znak(int val, bool isEmpty); // Change Image


    public: int x = 0, y = 0; // Default Postion
    public: unsigned int Wartosc = 1; // Default Value

    public: wxStaticBitmap *Image; // Point Image
    // Constructor
    public: Punkt(int px, int py, unsigned int w, wxPanel * panel);
    public: Punkt( void ){}; // Constructor For Creating Arrays
    // End Constuctors


    public: static void GeneratorPunktow(wxPanel * panel, unsigned int punky=Punkt::MAX_PUNKTOW); // Create Point In Random Positions
    public: static Punkt Nastepny_Punkt(wxPanel * panel); // Create Next Point In Random Positions
    public: static void WypiszPunkty( void ); // Override All Points => Refresh()
    public: static bool Collide(int y, int x); // Check If Point Collides With Dot Or No
};

#endif //PACMAN_POINTS_H
