#pragma once
#include "Object.h"
class PowerUp :public Object, public Collidable {
public:
	PowerUp(float x, float y, float w, float h, std::string path, const class Game& mygame);
	void draw();
	void update() override;
	Collider getCollider() const override;
	int getPower();
};