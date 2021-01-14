#include "Enemy.h"

class SmallSoldier :public Enemy {
public:
	SmallSoldier(const class Game& mygame);
	void update() override;
	void draw()override;
	int getPoints();
};

