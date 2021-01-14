#include "Explosion.h"
#include "graphics.h"

Explosion::Explosion(int x, int y, int w, int h, std::string path){
	this->x = x;
	this->y = y;
    this->w = w;
    this->h = h;
	this->path = path;
	this->creationTime = graphics::getGlobalTime();
}


void Explosion::draw() {
    graphics::Brush br;
    
    graphics::setOrientation(0);

    br.outline_opacity = 0.0f;

    br.texture = this->path;
    graphics::drawRect(this->x, this->y, this->w, this->h, br);
}

float Explosion::getCrTime() {
    return creationTime;
}