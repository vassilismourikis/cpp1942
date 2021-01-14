#pragma once
#include <string>

class Background {
private:
	float x, y, w, h;
	std::string asset_path;
public:
	Background(float w, float h, std::string a);
	~Background();
	//Moves backround's photo down giving the feeling ov movement to the player
	void update();
	void draw();
	std::string get_path();
	float get_x();
	float get_y();
	float get_w();
	float get_h();

};