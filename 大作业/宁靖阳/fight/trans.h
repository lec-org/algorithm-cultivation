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

	//Åö×²
	void onCollide() override;			//´¦ÀíÅö×²

public:
	void update(int time) override;
	void render() override;


private:
	//äÖÈ¾
	Animation animationBreak;			// ÆÆËé¶¯»­

};

