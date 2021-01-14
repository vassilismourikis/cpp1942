#pragma once
#include "Plain.h"
#include "Bullet.h"


class Enemy :public Plain{
protected:
	float fx, fy,hp;
public:
	float lastBulletTime;
	static std::vector<Bullet*> bullets;
	Enemy(float w, float h, std::string path, const class Game& mygame);
	virtual void draw()=0;
	virtual void update() =0;
	virtual int getPoints() = 0;
	virtual int getHp();
	virtual void decrHp(float i);
	Collider getCollider() const override;
	~Enemy();
};