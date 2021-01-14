#include "Enemy.h"

class Boss :public Enemy {
private:
	int direction;
public:
	Boss(const class Game& mygame);
	void update() override;
	void draw()override;
	int getPoints();
	int getHp() override;
	void decrHp(float i) override;
	Collider getCollider() const override;
};