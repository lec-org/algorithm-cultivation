#pragma once
#include "bullet.h"
#include "animation.h"
#include "camera.h"

extern Atlas atlasSun;
extern Atlas atlasSunExplode;

class SunBullet : public Bullet {
public:
	void update(int time) override;
	void render() override;
public:
	SunBullet();
public:
	void onCollide();

private:
	//�˶�
	const float gravity = 1e-3f;

	//��Ⱦ
	Animation animationIdle;				//Ĭ�϶���
	Animation animationExplode;				//��ը����
	Vector2 explodeRenderOffset;			//��ը������ƫ��
};
