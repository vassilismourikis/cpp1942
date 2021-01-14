#pragma once
#include "Object.h"
#include <ctime>
#include <chrono>
#include <vector>
#include <iostream>
#include "graphics.h"

class Bullet :public Object, public Collidable {
public:
	static float last_bullet_time;
	Bullet(float x, float y, std::string path, const class Game& mygame);
	void draw();
	void update() override;
	Collider getCollider() const override;
};