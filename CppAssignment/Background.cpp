#include "Background.h"
#include "graphics.h"

Background::Background(float w, float h, std::string a) {
	this->h = h;
	this->w = w;
	this->x = w;
	this->y = this->h / 2 * (-1) + 600; //600 is window's height. It must start at this y because the 0th pixel of png must be on the top down of the window
	this->asset_path = a;
	
}

Background::~Background() {}


void Background::update() {
	if (this->y == h/2) {
		this->y = this->h/2*(-1)+600; //resseting background height to play in repeat
		return;
	}
	this->y+=1;
}

void Background::draw() {
	graphics::Brush br;

	br.outline_opacity = 0.0f;

	br.texture = this->get_path();
	graphics::drawRect(600, this->get_y(), this->get_w(), this->get_h(), br);
}

std::string Background::get_path() {
	return this->asset_path;
}


float Background::get_x() {
	return this->x;
}


float Background::get_y() {
	return this->y;
}

float Background::get_w() {
	return this->w;
}


float Background::get_h() {
	return this->h;
}