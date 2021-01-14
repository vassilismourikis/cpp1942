#pragma once
#include <string> 
#include "graphics.h"
#include "util.h"
//#define DEBUG_COL 


class Collidable {
public:
	virtual Collider getCollider() const=0;
};

class Object {
protected:
	float x, y, w, h;
	std::string asset_path;
	const class Game& game;
public:
	Object(const class  Game & mygame);
	void draw();
	virtual void update()=0;
	void move_left(int speed);
	void move_right(int speed);
	void move_up(int speed);
	void move_down(int speed);
	std::string get_path();
	float get_x();
	float get_y();
	float get_w();
	float get_h();
};