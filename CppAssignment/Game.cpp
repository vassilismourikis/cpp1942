#include "Game.h"



void Game::update()
{
    if (status == ON_MENU) {
        if (!soundtrackPlaying) {
            graphics::playMusic("assets\\sounds\\Soundtrack.ogg", 0.5f, true);
            soundtrackPlaying = true;
        }
        if (graphics::getKeyState(graphics::SCANCODE_RETURN) && !player) {
            soundtrackPlaying = false;
            graphics::stopMusic();
            player = new Player(600, 500, 60, 40, "assets\\player.png", *this);
            status = PLAYABLE;
            graphics::playMusic("assets\\sounds\\wind.wav", 0.3f, true);
        }
    }
    background->update();

    if(status== PLAYABLE){


        if(player) player->update();

        //enemies managment------------------------------------------------------------------------------------------------
        //enemies spawn------------------------------------------------------------------------------------------------
        
        if (score<2000 && graphics::getGlobalTime() - lastSpawn>1000.0f) {
            //std::cout << graphics::getGlobalTime() - lastSpawn << std::endl;
            enemies.push_back(new SmallSoldier(*this));
            lastSpawn = graphics::getGlobalTime();
        }
        else if (score < 3000 && graphics::getGlobalTime() - lastSpawn>1000.0f) {
            //std::cout<<"INNNNNNNNNNNNNNNN";
            enemies.push_back(new BigSoldier(*this));
            lastSpawn = graphics::getGlobalTime();
        }
        else if ((score % 5000 == 0 || score % 5100 == 0) && score != 0 && bigSpawn) {
            enemies.push_back(new Boss(*this));
            lastSpawn = graphics::getGlobalTime();
            bigSpawn = false;
        }
        else if (graphics::getGlobalTime() - lastSpawn > 1000.0f) {
            enemies.push_back(new SmallSoldier(*this));
            lastSpawn = graphics::getGlobalTime();
            enemies.push_back(new BigSoldier(*this));
            lastSpawn = graphics::getGlobalTime();
        }
        
        //enemies spawn------------------------------------------------------------------------------------------------

        for (int i = 0; i < enemies.size(); i++) {
            if (enemies[i]->get_y() < 595) {
                enemies[i]->update();
            }
            else {
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
            }
        }
        //enemies managment------------------------------------------------------------------------------------------------

        //PowerUp managment---------------------------------------------------------------------------
        if (score % 600 == 0 && score != 0 && !pu && puSpawn) {
            this->pu = new PowerUp(rand() % 800 + 200.0f, 0, 35, 35, "assets\\pow.png", *this);
            puSpawn = false;
        }
        if (pu) {
            if (pu->get_y() > 595) {
                delete pu;
                pu = nullptr;
            }
            else pu->update();
        }
        //PowerUp managment---------------------------------------------------------------------------


        onCollision();
    }
    else if (status == NOT_PLAYABLE) {
        if (!soundtrackPlaying) {
            graphics::playMusic("assets\\sounds\\Soundtrack.ogg", 0.5f, true);
            soundtrackPlaying = true;
        }
        if (graphics::getKeyState(graphics::SCANCODE_RETURN) && !player) {
            //REDEFINE------------------------------------------
            for (auto p : enemies)
            {
                delete p;
            }
            enemies.clear();
            for (auto p : explosions)
            {
                delete p;
            }
            explosions.clear();
            for (auto p : Enemy::bullets)
            {
                delete p;
            }
            Enemy::bullets.clear();
            explosions.clear();
            soundtrackPlaying = false;
            lastSpawn = 0;
            delete player;
            puSpawn = true;
            score = 0;
            bigSpawn = true;
            delete pu;
            //REDEFINE------------------------------------------
            graphics::stopMusic();
            player = new Player(600, 500, 60, 40, "assets\\player.png", *this);
            status = PLAYABLE;
            graphics::playMusic("assets\\sounds\\wind.wav", 0.5f, true);
        }
    }

}

void Game::draw()
{
    background->draw();

    graphics::Brush br;
    graphics::resetPose();
    br.outline_opacity = 0.0f;


    if (status == PLAYABLE) {
        if (player) player->draw();
        
        for (int i = 0; i < enemies.size(); i++) {
            enemies[i]->draw();
        }

        for (int i = 0; i < explosions.size(); i++) {
            explosions[i]->draw();
        }

        if (pu) pu->draw();

        for (int i = 0; i < Enemy::bullets.size(); i++) {
            Enemy::bullets[i]->draw();

        }
        //ENEMY BULLETS----------------------------------------(not to stay still when the enemy is destroyed)
        for (int i = 0; i < Enemy::bullets.size(); i++) {
            if (Enemy::bullets[i]->get_y() <590) {
                Enemy::bullets[i]->move_down(2);
            }
            else {
                delete Enemy::bullets[i];
                Enemy::bullets.erase(Enemy::bullets.begin() + i);//erasing bullets that exits the window
            }
        }
        //ENEMY BULLETS----------------------------------------
        //UI SECTION-----------------------------------------------------------------------
        graphics::resetPose();
        drawText(0, 50, 50, "Score: ", br);
        drawText(160, 50, 50, std::to_string(score), br);


        drawText(1000, 50, 50, "fps: ", br);
        drawText(1100, 50, 50, std::to_string(1000 / graphics::getDeltaTime()), br);//fps


        if (graphics::getGlobalTime() > 3000) {
            drawText(0, 100, 30, "Lifes: ", br);
            drawText(100, 100, 30, std::to_string(player->getLifes()), br);
        }
        //UI SECTION-----------------------------------------------------------------------
    }
    else if(status==ON_MENU){
        br.fill_color[0] = 0.0f;
        br.fill_color[1] = 0.0f;
        br.fill_color[2] = 0.0f;
        drawText(350, 300, 40, "PRESS ENTER TO START", br);
        drawText(500, 350, 40, "THE GAME", br);

    }
    else {//WHEN PLAYER IS DESTROYED
        br.fill_color[0] = 0.0f;
        br.fill_color[1] = 0.0f;
        br.fill_color[2] = 0.0f;
        drawText(500, 300, 40, "GAMEOVER", br);
        drawText(350, 350, 40, "PRESS ENTER TO RESTART", br);
        drawText(500, 400, 40, "SCORE: "+ std::to_string(score), br);

        return;
    }


}

void Game::onCollision() {
    Collider col1, col2;
    float dx, dy;
    //PLAYER-ENEMIES
    if (player) {
        col1 = player->getCollider();
        for (int i = 0; i < enemies.size(); i++) {
            col2 = enemies[i]->getCollider();
            dx = col1.x - col2.x;
            dy = col1.y - col2.y;
            if (sqrt(dx * dx + dy * dy) < col1.radius + col2.radius && player->getLifes()==0) {//ON COLLISION
                delete player;
                player = nullptr;
                status = NOT_PLAYABLE;
            }
            else if (sqrt(dx * dx + dy * dy) < col1.radius + col2.radius && player->getLifes() != 0) {
                graphics::playSound("assets\\sounds\\explosions\\Small.wav", 1.0f, false);
                explosions.push_back(new Explosion(enemies[i]->get_x(), enemies[i]->get_y(), 35, 35, "assets\\explosion\\Small.png"));
                score += enemies[i]->getPoints();
                delete enemies[i];
                enemies.erase(enemies.begin() + i);
                player->decrLifes();
                
            }

        }

        

    }

    //PLAYER-ENEMIES


    //PLAYER-BULETS
    if (player) {
        col1 = player->getCollider();
        for (int i = 0; i < Enemy::bullets.size(); i++) {
            col2 = Enemy::bullets[i]->getCollider();
            dx = col1.x - col2.x;
            dy = col1.y - col2.y;
            if (sqrt(dx * dx + dy * dy) < col1.radius + col2.radius && player->getLifes() == 0) {//ON COLLISION
                delete player;
                player = nullptr;
                status = NOT_PLAYABLE;
            }
            else if (sqrt(dx * dx + dy * dy) < col1.radius + col2.radius && player->getLifes() != 0) {
                graphics::playSound("assets\\sounds\\explosions\\Small.wav", 1.0f, false);
                delete Enemy::bullets[i];
                Enemy::bullets.erase(Enemy::bullets.begin() + i);
                player->decrLifes();
            }
        }

        

    }
    //PLAYER-BULLETS


    //BULLETS-ENEMIES
    if (player) {
    for (int j = 0; j < player->bullets.size(); j++) {
        col1 = player->bullets[j]->getCollider();
        for (int i = 0; i < enemies.size(); i++) {
            col2 = enemies[i]->getCollider();
            dx = col1.x - col2.x;
            dy = col1.y - col2.y;
            if (sqrt(dx * dx + dy * dy) < col1.radius + col2.radius) {//ON COLLISION   
                if (typeid(*enemies[i]) == typeid(Boss)) {
                    
                    if ((enemies[i]->getHp()  == 10 && player->bullet.compare("assets\\bullets\\OneBullet.png") == 0)|| (enemies[i]->getHp() <= 40 && player->bullet.compare("assets\\bullets\\OneBullet.png") != 0)) {
                        score += enemies[i]->getPoints();//SCORE INCREASMENT IT DEPENTS ON THE ENEMY
                        puSpawn = true; //FOR NOT SPAWNING PU ALL THE TIME
                        bigSpawn = true;
                        graphics::playSound("assets\\sounds\\explosions\\Boss.wav", 1.0f, false);
                        explosions.push_back(new Explosion(enemies[i]->get_x(), enemies[i]->get_y(), 50, 50, "assets\\explosion\\Boss.png"));
                        delete enemies[i];
                        enemies.erase(enemies.begin() + i);
                        delete player->bullets[j];
                        player->bullets.erase(player->bullets.begin() + j);
                    }
                    else {
                        if(player->bullet.compare("assets\\bullets\\OneBullet.png")==0){
                            enemies[i]->decrHp(10);
                            delete player->bullets[j];
                            player->bullets.erase(player->bullets.begin() + j);
                        }
                        else {

                            enemies[i]->decrHp(40);
                            delete player->bullets[j];
                            player->bullets.erase(player->bullets.begin() + j);
                        }
                        
                    }
                }
                else{

                    score += enemies[i]->getPoints();//SCORE INCREASMENT IT DEPENTS ON THE ENEMY
                    puSpawn = true; //FOR NOT SPAWNING PU ALL THE TIME
                    if(enemies[i]->getPoints()>=200) bigSpawn = true;                 
                    graphics::playSound("assets\\sounds\\explosions\\Small.wav", 1.0f, false);
                    explosions.push_back(new Explosion(enemies[i]->get_x(), enemies[i]->get_y(), 35, 35, "assets\\explosion\\Small.png"));
                    delete enemies[i];
                    enemies.erase(enemies.begin() + i);
                    delete player->bullets[j];
                    player->bullets.erase(player->bullets.begin() + j);
                }
            }
            
            
            
        }
    }

        
    }

    //BULLETS-ENEMIES

    //POWERUPS - PLAYER

    if (player && pu) {
        col1 = player->getCollider();
        col2 = pu->getCollider();
        dx = col1.x - col2.x;
        dy = col1.y - col2.y;
        if (sqrt(dx * dx + dy * dy) < col1.radius + col2.radius) {//ON COLLISION
            //HERE WHAT DOES THE PU DOES
            if (pu->getPower() == 0 && player->fire_rate>100.0) {
                graphics::playSound("assets\\sounds\\powerups\\fireRate.wav", 1.0f, false);
                player->fire_rate -= 50.0f;
            }
            else if (pu->getPower() == 1 ) {
                graphics::playSound("assets\\sounds\\powerups\\Bullet.wav", 1.0f, false);
                player->bullet = "assets\\bullets\\FourBullets.png";
            }
            else if (pu->getPower() == 2) {
                graphics::playSound("assets\\sounds\\powerups\\Manuver.wav", 1.0f, false);
                player->incrLifes();
            }
            else {
                graphics::playSound("assets\\sounds\\powerups\\Bad.wav", 1.0f, false);
                player->bullet = "assets\\bullets\\OneBullet.png"; //POWERUP MAY BE BAD ITS A RISK
            }
            delete pu;
            pu = nullptr;              
        }
            
    }
    //POWERUPS - PLAYER

    for (int i = 0; i < explosions.size(); i++) {
        if (graphics::getGlobalTime() - explosions[i]->getCrTime() > 100.0f) {
            delete explosions[i];
            explosions.erase(explosions.begin() + i);
        }
    }
        

}

void Game::init()
{
    graphics::setFont("assets\\orange juice 2.0.ttf");
}

Game::Game()
{
    soundtrackPlaying = false;
    srand(time(NULL));//initializing random seed
    lastSpawn = 0;
    player = nullptr;
    puSpawn = true;
    score = 0;
    bigSpawn = true;
    pu = nullptr;
    background = new Background(800, 5200, "assets\\Background.png");
}

Game::~Game()
{
    delete pu;
    delete player;
    delete background;
    for (auto p : enemies)
    {
        delete p;
    }
    enemies.clear();
    for (auto p : explosions)
    {
        delete p;
    }
    explosions.clear();
    for (auto p : Enemy::bullets)
    {
        delete p;
    }
    Enemy::bullets.clear();
}
