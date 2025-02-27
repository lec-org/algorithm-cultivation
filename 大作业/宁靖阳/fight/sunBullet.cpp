#include "sunBullet.h"

void SunBullet::update(int time) {

	if (isValid) {

		velocity.y += gravity * time;

		position += velocity * time;
	}

	if (!isValid)
		animationExplode.update(time);
	else
		animationIdle.update(time);

	if (checkIsExceedScreen())
		isCanRemove = true;
}

void SunBullet::render() {
	if (isValid)
		animationIdle.render(position.x, position.y);
	else
		animationExplode.render(position.x + explodeRenderOffset.x, position.y + explodeRenderOffset.y);

	Bullet::render();
}

SunBullet::SunBullet() {

	size.x = 96, size.y = 96;

	damage = 20;

	animationIdle.setAtlas(&atlasSun);
	animationIdle.setInterval(50);

	animationExplode.setAtlas(&atlasSunExplode);
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

void SunBullet::onCollide() {

	Bullet::onCollide();

	Camera::getCamera().shake(5, 250);

	mciSendString(_T("play sunExplode from 0"), nullptr, 0, nullptr);
}

