#include "Object.h"
#include "Game.h"


void Object::move_left(int speed) {
	if (this->x > 202)this->x -= speed*graphics::getDeltaTime() / 10;
}
void Object::move_right(int speed) {
	if (this->x < 998)this->x += speed * graphics::getDeltaTime() / 10;
}
void Object::move_up(int speed) {
	if (this->y > 2)this->y -= speed * graphics::getDeltaTime() / 10;
}
void Object::move_down(int speed) {
	if (this->y < 598)this->y += speed * graphics::getDeltaTime()/10;
}

std::string Object::get_path() {
	return this->asset_path;
}
float Object::get_x() {
	return this->x;
}
float Object::get_y() {
	return this->y;
}
float Object::get_w() {
	return this->w;
}
float Object::get_h() {
	return this->h;
}

Object::Object(const class  Game& mygame) :game(mygame) {}