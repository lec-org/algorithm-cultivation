#include "peaBullet.h"


PeaBullet::PeaBullet() {

	size.x = 64, size.y = 64;

	damage = 10;

	animationBreak.setAtlas(&atlasPeaBreak);
	animationBreak.setInterval(100);
	animationBreak.setIsLoop(false);
	animationBreak.setCallback([&] {
		isCanRemove = true;
		});

}

//��д���෽������������Ҫִ�и����߼�
void PeaBullet::onCollide() {

	Bullet::onCollide();
	//�����������

	switch (rand() % 3) {
	case 0:
		mciSendString(_T("play peaBreak1 from 0"), nullptr, 0, nullptr);
		break;
	case 1:
		mciSendString(_T("play peaBreak1 from 0"), nullptr, 0, nullptr);
		break;
	case 2:
		mciSendString(_T("play peaBreak1 from 2"), nullptr, 0, nullptr);
		break;
	default:
		break;
	}

}

void PeaBullet::update(int time) {

	position += velocity * time;

	if (!isValid)
		animationBreak.update(time);

	if (checkIsExceedScreen())
		isCanRemove = true;

}

void PeaBullet::render() {

	if (isValid)
		putImageAlpha(position.x, position.y, &imgPea);
	else
		animationBreak.render(position.x, position.y);

	Bullet::render();
}

