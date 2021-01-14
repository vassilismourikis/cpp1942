#include "BigSoldier.h"

BigSoldier::BigSoldier(const class Game& mygame) :Enemy(100, 100, "assets\\soldiers\\BigSoldier.png", mygame) {
    direction = 0;
}

BigSoldier::~BigSoldier() {
    
}

int BigSoldier::getPoints() {
	return 200;
}

Collider BigSoldier::getCollider() const {
    Collider col;
    col.x = x;
    col.y = y;
    col.radius = (h * 0.2);
    return col;
}


void BigSoldier::update() {

    if (y > 550) {
        fx = x;
        direction = 1;
    }
    if (y < 100) {
        fx = x;
        direction = 0;
    }
    if (direction==0) {
        this->move_down(3);
        if (this->fx > 600)
            this->move_left(3);
        else
            this->move_right(3);
    }
    else {
        this->move_up(4);
        if (this->fx > 600)
            this->move_left(3);
        else
            this->move_right(3);
    }

    
    
    //FIRE----------------------------------------------------------
    if ((graphics::getGlobalTime() - lastBulletTime) > 1500.0f) {
        //std::cout << (graphics::getGlobalTime() - lastBulletTime) << std::endl;
        bullets.push_back(new Bullet(this->x, this->y, "assets\\bullets\\EnemyBullet.png", game));
        lastBulletTime = graphics::getGlobalTime(); //new time to the static variable
    }

    
    
    
    

}



void BigSoldier::draw()
{

    graphics::Brush br;
    if(direction==0)graphics::setOrientation(180);
    else graphics::setOrientation(0);
    
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
