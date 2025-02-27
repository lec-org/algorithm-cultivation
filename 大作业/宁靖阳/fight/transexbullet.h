#pragma once
#include "bullet.h"
#include "animation.h"
#include "camera.h"

extern Atlas atlastransEx;
extern Atlas atlastransExExplode;

class transEx : public Bullet {
public:
	void update(int time) override;
	void render() override;
public:
	transEx();
public:
	//��ײ
	void onCollide();
	bool checkCollision(const Vector2& position, const Vector2& size) override;
private:

	//��Ⱦ
	Animation animationIdle;				//Ĭ�϶���
	Animation animationExplode;				//��ը����
	Vector2 explodeRenderOffset;			//��ը������ƫ��
};
