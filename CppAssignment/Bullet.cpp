#include "Bullet.h"


float Bullet::last_bullet_time =0;

Bullet::Bullet(float x, float y, std::string path, const class Game& mygame) :Object(mygame) {
	this->x = x;
	this->y = y;
	this->asset_path = path;
	if (asset_path.compare("assets\\bullets\\FourBullets.png")==0) {
		this->w = 45.0;
		this->h = 45.0;
	}
	else {
		this->w = 35.0;
		this->h = 35.0;
	}
	
	
}

Collider Bullet::getCollider() const {
	Collider col;
	col.x = x;
	col.y = y;
	if (this->w==45.0) {
		col.radius = (h * 0.4);
	}
	else col.radius = (h * 0.2);
	

	return col;
}

void Bullet::draw(){

	graphics::Brush br;

    br.outline_opacity = 0.0f;

	br.texture = this->get_path();
	graphics::drawRect(this->get_x(), this->get_y(), this->get_w(), this->get_h(), br);


#ifdef DEBUG_COL


	//DRAW COLLIDER
	br.texture = "";
	br.fill_color[0] = 0.5f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.gradient = false;
	br.fill_opacity = 0.3;
	Collider col = getCollider();
	graphics::drawDisk(col.x, col.y, col.radius, br);
	//----------------------



#endif 
}
void Bullet::update(){
	this->move_up(4);
}