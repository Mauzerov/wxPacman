/***************************************************************
 * Name:      entity.h
 * Purpose:   Extends Entity Class
 * Author:     ()
 * Created:   2021-02-10
 * Copyright:  ()
 * License:
 **************************************************************/

#include "object/Entity.h"

extern int MapaZPliku[25][50];

const double Entity::SPEED_BUFF = 1.3f;
const double Entity::SLOW_BUFF = 0.9f;

wxStaticBitmap *Entity::getImage() {
    return this->Image; // Get Image => return wxStaticBitmap
};
void Entity::setImage(wxStaticBitmap *img) {
	this->Image = img; // Set Image => sets Image for entity
};

int Entity::x() {
    return (int)(this->X); // Return rounded x
};

int Entity::y() {
    return (int)(this->Y); // Return rounded y
};

void Entity::setVelocity(double vel) {
	this->v = vel;
};

double Entity::getVelocity( void ) {
	return this->v; // Return base Speed
};

char Entity::getDirection( void ) {
	return this->direction; // Return Direcrtion
};

void Entity::setDirection(char ddirection)
{
	this->direction = ddirection; // Sets Direction
};

void Entity::position_generator( void ) // Random Positionm Generator
{
	while (true) {
		this->X = float(rand() % 50); // New Random X
		this->Y = float(rand() % 25); // New Random Y

		if (::MapaZPliku[int(this->Y)][int(this->X)] != 177) break;
	}
	this->last_x = this->x(); // Set New Position
    this->last_y = this->y(); //
};

bool Entity::startCollide(Entity other) // Make Sure Ghost isn't in same row or column
{
	return (this->x() == other.x() || this->y() == other.y());
};

std::pair<bool,char> Entity::isInRange(Entity & player) // Ghost AI Fragment
{
	std::pair<bool,char> range;

	range.first = false;

	int my_x = this->x(), my_y = this->y();
	int end_x = player.x(), end_y = player.y();

	/** TODO curved direction return
	*
	*   if mx - end_x <= 3 and my -1  == end_y
	*   if mx - end_x <= 3 and my +1  == end_y
	*
	*   if my - end_y <= 3 and mx -1  == end_x
	*   if my - end_y <= 3 and mx +1  == end_x
    **/

	if (abs(my_x - end_x) <= 4 && my_y == end_y) {
		range.first = true;
		range.second = (my_x < end_x) ? 'd' : 'a';
	}
	if (abs(my_y - end_y) <= 4 && my_x == end_x) {
		range.first = true;
		range.second = (my_y < end_y) ? 's' : 'w';
	}
	return range;

};

void Entity::DoMove( void )
{
}
