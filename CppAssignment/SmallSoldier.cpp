#include "SmallSoldier.h"

void SmallSoldier::update() {
	if (this->y < 200)this->move_down(4);
	else if (this->y < 400) {
		this->move_down(4);
		if (this->fx > 600)
			this->move_left(4);
		else
			this->move_right(4);
	}
	else {
		this->move_down(4);
	}

}

void SmallSoldier::draw()
{

	graphics::Brush br;
	graphics::setOrientation(180);
	br.outline_opacity = 0.0f;

	br.texture = this->get_path();
	graphics::drawRect(this->get_x(), this->get_y(), this->get_w(), this->get_h(), br);

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i]->draw();

	}


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

int SmallSoldier::getPoints() {
	return 100;
}




SmallSoldier::SmallSoldier(const class Game& mygame):Enemy(50,50,"assets\\soldiers\\SmallSoldier.png",mygame) {}