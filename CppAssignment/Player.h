#pragma once
#include "Plain.h"
#include <vector>
#include "Bullet.h"

class Player :public Plain{
private:
	float height;
	float last_manuver_time;
	int lifes;	
public:
	void incrLifes();
	void decrLifes();
	std::string bullet;
	float fire_rate;
	bool on_manuver;
	std::vector<Bullet*> bullets;
	Player(float x, float y, float w, float h, std::string path, const class Game& mygame);
	void draw();
	void update() override;
	int getLifes();
	Collider getCollider() const override;
};