#include "Player.h"


	Player::Player(float x, float y, float w, float h, std::string path, const class Game& mygame) :Plain(mygame) {
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
        this->last_manuver_time =0.0f;
        this->on_manuver = false;
        this->height = 1.0f;
		this->asset_path = path;
        this->lifes = 3;
        this->fire_rate = 400.0;
        this->bullet = "assets\\bullets\\OneBullet.png";
	}


    void Player::incrLifes() {
        this->lifes++;
    }

    void Player::decrLifes() {
        this->lifes--;
    }

    int Player::getLifes() {
        return lifes;
    }

    Collider Player::getCollider() const {
        Collider col;
        col.x = x;
        col.y = y;
        col.radius = (h * 0.6);

        return col;
    }

	void Player::draw() {

        graphics::Brush br;
        graphics::setScale(height, height);
        br.outline_opacity = 0.0f;

        br.texture = this->get_path();
        graphics::drawRect(this->get_x(), this->get_y(), this->get_w(), this->get_h(), br);

        graphics::resetPose();

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

	void Player::update() {

        //graphics::MouseState mouse;
        //graphics::getMouseState(mouse);
        /*
        if (mouse.button_left_released)
        {
            graphics::playSound("assets\\hit1.wav", 1.0f, false);
        }
        */
        if (graphics::getKeyState(graphics::SCANCODE_UP)) {
            this->move_up(3);
        }
        if (graphics::getKeyState(graphics::SCANCODE_DOWN)) {
            this->move_down(3);
        }
        if (graphics::getKeyState(graphics::SCANCODE_RIGHT)) {
            this->move_right(3);
        }
        if (graphics::getKeyState(graphics::SCANCODE_LEFT)) {
            this->move_left(3);
        }
        
        if (graphics::getKeyState(graphics::SCANCODE_X)) {
            //FIRE
            //checking time difference to launch the next bullet because file goes like one single stripe
            if ((graphics::getGlobalTime() - Bullet::last_bullet_time) > fire_rate) {
                graphics::playSound("assets\\sounds\\playerFire.wav", 0.1f, false);
                std::cout << (graphics::getGlobalTime() - Bullet::last_bullet_time) << std::endl;
                bullets.push_back(new Bullet(this->x,this->y, bullet,game));
                Bullet::last_bullet_time = graphics::getGlobalTime(); //new time to the static variable
            }
        }
        //checking for bullet exits the screen
        for (int i = 0; i < bullets.size(); i++) {
            if (bullets[i]->get_y() > 3) {
                bullets[i]->move_up(4);
            }
            else {
                delete bullets[i];
                bullets.erase(bullets.begin() + i);//erasing bullets that exits the window
            }
        }

	}