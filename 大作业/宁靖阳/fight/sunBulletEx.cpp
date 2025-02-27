#include "sunBulletEx.h"

void SunBulletEx::update(int time) {

	if (isValid)
		position += velocity * time;


	if (!isValid)
		animationExplode.update(time);
	else
		animationIdle.update(time);

	if (checkIsExceedScreen())
		isCanRemove = true;
}

void SunBulletEx::render() {

	if (isValid)
		animationIdle.render(position.x, position.y);
	else
		animationExplode.render(position.x + explodeRenderOffset.x, position.y + explodeRenderOffset.y);

	Bullet::render();
}

SunBulletEx::SunBulletEx() {

	size.x = 288, size.y = 288;

	damage = 20;

	animationIdle.setAtlas(&atlasSunEx);
	animationIdle.setInterval(50);

	animationExplode.setAtlas(&atlasSunExExplode);
	animationExplode.setInterval(50);
	animationExplode.setIsLoop(false);
	animationExplode.setCallback([&] {
		isCanRemove = true;
		});

	auto frameIdle = animationIdle.getFrame();
	auto frameExplode = animationExplode.getFrame();

	//±¬Õ¨¶¯»­Æ«ÒÆ
	explodeRenderOffset.x = (frameIdle->getwidth() - frameExplode->getwidth()) / 2.0;
	explodeRenderOffset.y = (frameIdle->getheight() - frameExplode->getheight()) / 2.0;
}

void SunBulletEx::onCollide() {

	Bullet::onCollide();

	Camera::getCamera().shake(20, 350);

	mciSendString(_T("play sunExplodeEx from 0"), nullptr, 0, nullptr);
}

bool SunBulletEx::checkCollision(const Vector2& position, const Vector2& size) {

	auto xLeft = this->position.x;
	auto xRight = this->position.x + this->size.x;

	auto yTop = this->position.y;
	auto yDown = this->position.y + this->size.y;

	bool isCollideX = max(xRight, position.x + size.x) - min(xLeft, position.x) <= this->size.x + size.x;
	bool isCollideY = max(yDown, position.y + size.y) - min(yTop, position.y) <= this->size.y + size.y;

	return isCollideX && isCollideY;
}

