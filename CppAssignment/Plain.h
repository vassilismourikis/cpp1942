#pragma once
#include "Object.h"
class Plain:public Object, public Collidable {
public:
	Plain(const class Game& mygame);
	~Plain();
	void draw();
	virtual void update() = 0;
};