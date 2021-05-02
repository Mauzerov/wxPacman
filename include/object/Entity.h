/***************************************************************
 * Name:      entity.h
 * Purpose:   Defines Every Entity Class
 * Author:     ()
 * Created:   2021-02-10
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef PACMAN_ENTITY_H
#define PACMAN_ENTITY_H

#include <iostream>
#include <wx/statbmp.h>

#ifndef MUR
#define MUR 177
#endif // MUR

/// Entity Class
class Entity{

    protected: void DoMove();

    public: static const double SPEED_BUFF;
    public: static const double SLOW_BUFF;

    public: double speedBuff = 1.f, slowBuff = 1.f; // Velocity
    public: double v = 1.0f;

    public: wxStaticBitmap *Image;
    public: float X = 2.f, Y = 1.f; // Position
    public: char direction = 'd'; // Movement Direction
    public: int last_x;
    public: int last_y;

    // Movement Methods
    public: int x( void );
    public: int y( void );

    void setVelocity(double vel);
    double getVelocity( void );

    public: char getDirection( void );
    public: void setDirection(char ddirection);
    // End Movement Methods

    // Cosmetics Methods
    public: void setImage(wxStaticBitmap* img);
    public: wxStaticBitmap *getImage( void );
    // End Cosmetics Methods

    // Position Checker / Generator

    // Generator pozycji bytu
    public: void position_generator( void );
    public: bool notCollide(Entity o); //Entity o = Other Object
            // Returns if root entity collides with other Entity

    public: bool startCollide(Entity o); // Make Sure Ghost isn't in same row or column
    // End Position Checker / Generator

    // Ghost AI Fragment
    public: std::pair<bool,char> isInRange(Entity& player);

};
// End Entity Class -> Base Class For Gosts and Player

/// Ghost Class
class Ghost: public Entity{


    /// TODO :> better ai
    private: void ChangeDirection( void );
    // end changeDirection
    // Ai & Stuff
    private: std::pair <bool, char> NextDirection(char current, Entity& player);
    private: bool IsIntersection( void );

    // Constuctor
    public: Ghost(){};
    public: Ghost(wxStaticBitmap * image);
    // end Constructor

    // Ghost Move
    public: void Move(Entity & player);
};

/// Player Class
class Player: public Entity{

    private: unsigned long long int Score = 0; // Player Score Variable

    // Used For Animated Movement of Player
    private: bool state = false; // Animated Moveing Switch
    private: void changeState(); // Change Current State

    // Constructor
    public: Player(){} // Empty Constructor

    public: Player(wxStaticBitmap *img);
    // End Constructor

    /// buffs
        // speed
        public: int speedtimer = 0; // timer
        public: float getSpeedBuffer( void );
        public: void setSpeedBuffer( void );
        // slowness
        public: int slowtimer = 0; // timer
        public: float getSlowBuffer( void );
        public: void setSlowBuffer( void );

        // stopniowe usuwanie buffa function
        public: void check_buffs( void ); // change timer
        public: void resetTimer( void );
    /// end buffs

    // Player Movement
    public: void Move(); // Main Move Function

    public: void setScore(unsigned long long int s); // Set Score Function
    public: void addScore(unsigned long long int s); // Add Score Function
    public: unsigned long long int getScore( void ); // Get Score Function

    public: void setPosition(std::pair<float,float> pos); // Set Position Function
};

#endif //PACMAN_ENTITY_H

