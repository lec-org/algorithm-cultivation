#pragma once
#include "bullet.h"
#include "animation.h"
#include "util.h"

extern IMAGE imgPea;
extern Atlas atlasPeaBreak;

class PeaBullet :public Bullet {
public:
	PeaBullet();

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

