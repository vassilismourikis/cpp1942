#include "Enemy.h"

class BigSoldier :public Enemy {
protected:
	int direction;
public:
	BigSoldier(const class Game& mygame);
	void update() override;
	void draw() override;
	int getPoints();
	Collider getCollider() const override;
	~BigSoldier();
};