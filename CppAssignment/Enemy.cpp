#include "Enemy.h"

std::vector<Bullet*> Enemy::bullets;

Enemy::Enemy(float w, float h, std::string path, const class Game& mygame) :Plain(mygame)
{
	//Rand for enemies
	this->x = rand() % 800 + 200;
	this->y = 0;
	this->fx = this->x;
	this->fy = this->y;
	this->w = w;
	this->h = h;
	this->asset_path = path;
	this->lastBulletTime = 0.0;
	hp = 100;
	
}

Enemy::~Enemy() {
	
}

int Enemy::getHp() {
	return hp;
}

void Enemy::decrHp(float i){}

Collider Enemy::getCollider() const {
	Collider col;
	col.x = x;
	col.y = y;
	col.radius = (h * 0.45);

	return col;
}





