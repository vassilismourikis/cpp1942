#include "PowerUp.h"
#include <time.h>

PowerUp::PowerUp(float x, float y, float w, float h, std::string path, const class Game& mygame) :Object(mygame)
{
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->asset_path = path;
	
}

Collider PowerUp::getCollider() const {
	Collider col;
	col.x = x;
	col.y = y;
	col.radius = (h * 0.45);

	return col;
}

void PowerUp::draw() {

	graphics::Brush br;

	br.outline_opacity = 0.0f;

	br.texture = this->get_path();
	graphics::drawRect(this->get_x(), this->get_y(), this->get_w(), this->get_h(), br);


#ifdef DEBUG_COL //MUST BE DEFINED IN OBJECT.H


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
void PowerUp::update() {
	this->move_down(2);
}

int PowerUp::getPower() {
	return rand() % 4;//0-3
}