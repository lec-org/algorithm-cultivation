#include "particle.h"

void Particle::setPosition(const Vector2& position) {
	this->position = position;
}

void Particle::setAtlas(Atlas* atlas) {
	this->atlas = atlas;
}

void Particle::setLifeSpan(int lifeSpan) {
	this->lifeSpan = lifeSpan;
}

bool Particle::checkIsValid() const {
	return isValid;
}

void Particle::update(int deltaT) {

	timer += deltaT;

	if (timer >= lifeSpan) {

		timer = 0;
		index++;

		//粒子在播完动画后消失
		if (index == atlas->getSize()) {

			index = atlas->getSize() - 1;

			isValid = false;

		}
	}
}

void Particle::render() const {

	putImageAlpha(position.x, position.y, atlas->getImage(index));
}

