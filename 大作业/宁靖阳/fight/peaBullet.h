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

	//Åö×²
	void onCollide() override;			//´¦ÀíÅö×²

public:
	void update(int time) override;
	void render() override;


private:

	//äÖÈ¾
	Animation animationBreak;			// ÆÆËé¶¯»­

};

