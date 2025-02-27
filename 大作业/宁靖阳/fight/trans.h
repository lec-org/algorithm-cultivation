#pragma once
#include "bullet.h"
#include "animation.h"
#include "util.h"

extern IMAGE imgtrans;
extern Atlas atlastransBreak;

class transBullet :public Bullet {
public:
	transBullet();

public:

	//��ײ
	void onCollide() override;			//������ײ

public:
	void update(int time) override;
	void render() override;


private:
	//��Ⱦ
	Animation animationBreak;			// ���鶯��

};

