#pragma once
#include "Game.h"
#include "Background.h"
#include "Player.h"
#include <vector>
#include <chrono>
#include <iostream>
#include "graphics.h"
#include "SmallSoldier.h"
#include "BigSoldier.h"
#include "Boss.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "Explosion.h"

class Game {
private:
	bool puSpawn,soundtrackPlaying;
	typedef enum { ON_MENU, PLAYABLE, NOT_PLAYABLE } status_t;
	bool bigSpawn;//for only one spawn when statement is %
	status_t status = ON_MENU;
	float lastSpawn;
	PowerUp* pu;
	int score;
	Background* background;
	std::vector<Enemy*> enemies;
	std::vector<Explosion*> explosions;
	Player* player;
public:
	void onCollision();
	void update();
	void draw();
	void init();
	Game();
	~Game();
};