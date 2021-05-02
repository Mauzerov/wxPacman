#include "object/Entity.h"
#include <iostream>

extern int pixelSizeBit;
bool IsWall(int y, int x);

Ghost::Ghost(wxStaticBitmap * image)
{
    this->Image = image;
}

std::pair <bool, char> Ghost::NextDirection(char current_direction, Entity& player)
{
    std::pair <bool, char> close = isInRange( player );

    if (close.first == true) { return close; }

    switch ( current_direction ) {
        case 'a':
            if (!::IsWall(this->y(), this->x()-1)) {
                return {close.first, current_direction};
            }
            break;
        case 'd':
            if (!::IsWall(this->y(), this->x()+1)) {
                return {close.first, current_direction};
            }
            break;
        case 's':
            if (!::IsWall(this->y()+1, this->x())) {
                return {close.first, current_direction};
            }
            break;
        case 'w':
            if (!::IsWall(this->y()-1, this->x())) {
                return {close.first, current_direction};
            }
            break;
    }

    char possible_directions[3];
    int directions = 0;

    if (!::IsWall(this->y(), this->x()-1) && (current_direction != 'a' || !(rand() & 0b11))) {
        possible_directions[directions++] = 'a';
    }
    if (!::IsWall(this->y(), this->x()+1) && (current_direction != 'd' || !(rand() & 0b11))) {
        possible_directions[directions++] = 'd';
    }
    if (!::IsWall(this->y()+1, this->x()) && (current_direction != 's' || !(rand() & 0b11))) {
        possible_directions[directions++] = 's';
    }
    if (!::IsWall(this->y()-1, this->x()) && (current_direction != 'w' || !(rand() & 0b11))) {
        possible_directions[directions++] = 'w';
    }

    if (directions != 0)
        return {close.first, possible_directions[ rand() % directions]};
    return {close.first, current_direction};
}

void Ghost::ChangeDirection( void )
{
    bool change = rand() & 1;
    if (change == true) {
        char possible_directions[4];
        int directions = 0;

        if (!::IsWall(this->y(), this->x()-1)) {
            possible_directions[directions++] = 'a';
        }
        if (!::IsWall(this->y(), this->x()+1)) {
            possible_directions[directions++] = 'd';
        }
        if (!::IsWall(this->y()+1, this->x())) {
            possible_directions[directions++] = 's';
        }
        if (!::IsWall(this->y()-1, this->x())) {
            possible_directions[directions++] = 'w';
        }

        direction = possible_directions[ rand() % directions];
    }
}
bool Ghost::IsIntersection( void ) // Possibility to change direction on intersection
{
    int directions = 0;
    if (!::IsWall(this->y(), this->x()-1)) directions++;
    if (!::IsWall(this->y(), this->x()+1)) directions++;
    if (!::IsWall(this->y()+1, this->x())) directions++;
    if (!::IsWall(this->y()-1, this->x())) directions++;

    return directions > 2;
}

void Ghost::Move(Entity & player)
{
        if (this->direction == 'n') return;
        std::pair <bool, char> close = NextDirection(this->direction, player);
        this->direction = close.second;

        if (this->IsIntersection() && close.first == false)
        {
            this->ChangeDirection(); // Random New Possible Direction
        }
        // Porusznie sie w odpowiednim kierunku

        switch (this->direction){
            case 's': // Down
                    this->Y += this->v * (!::IsWall(this->y()+1, this->x())); // Moving by Velocity If Not Wall
                break;

            case 'w': // Up
                    this->Y -= this->v * (!::IsWall(this->y()-1, this->x())); // Moving by Velocity If Not Wall
                break;

            case 'a': // Left
                    this->X -= this->v * (!::IsWall(this->y(), this->x()-1));// Moving by Velocity If Not Wall
                break;

            case 'd': // Right
                    this->X += this->v * (!::IsWall(this->y(), this->x()+1)); // Moving by Velocity If Not Wall
                break;
        };
        this->Image->SetPosition(wxPoint(this->x() << ::pixelSizeBit, this->y() << ::pixelSizeBit)); // Update Position
        this->Image->Refresh(); // Overide On Top
    }
