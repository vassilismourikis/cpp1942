#include "Boss.h"
//	TODO: LIFE
Boss::Boss(const class Game& mygame) :Enemy(200, 200, "assets\\bosses\\Boss.png", mygame) {
	this->y = 570;
	direction = 0;
}

int Boss::getPoints() {
	return 800;
}

Collider Boss::getCollider() const {
	Collider col;
	col.x = x;
	col.y = y;
	col.radius = (h * 0.3);
	return col;
}


int Boss :: getHp() {
	return hp;
}

void Boss::decrHp(float i) {
	hp -= i;
}

void Boss::update() {
	if (this->y > 100) {
		this->y--;
	}
	else {
		if (x >= 950) direction=0;
		if(x<=250) direction=1;

		if (direction == 0)x--;
		else x++;
	}

	//FIRE----------------------------------------------------------
	if ((graphics::getGlobalTime() - lastBulletTime) > 1500.0f) {
		//std::cout << (graphics::getGlobalTime() - lastBulletTime) << std::endl;
		bullets.push_back(new Bullet(this->x, this->y, "assets\\bullets\\EnemyBullet.png", game));
		lastBulletTime = graphics::getGlobalTime(); //new time to the static variable
	}


}

void Boss::draw()
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