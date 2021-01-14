#include <iostream>

class Explosion {
private:
	float x, y, h, w, creationTime;
	std::string path;
public:
	Explosion(int x, int y, int w, int h, std::string path);
	void draw();
	float getCrTime();
};