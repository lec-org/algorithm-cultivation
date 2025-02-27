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
	//运动
	const float gravity = 1e-3f;

	//渲染
	Animation animationIdle;				//默认动画
	Animation animationExplode;				//爆炸动画
	Vector2 explodeRenderOffset;			//爆炸动画的偏移
};
