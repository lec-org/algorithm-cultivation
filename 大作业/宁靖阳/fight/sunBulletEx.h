#pragma once
#include "bullet.h"
#include "animation.h"
#include "camera.h"

extern Atlas atlasSunEx;
extern Atlas atlasSunExExplode;

class SunBulletEx : public Bullet {
public:
	void update(int time) override;
	void render() override;
public:
	SunBulletEx();
public:
	//Åö×²
	void onCollide();
	bool checkCollision(const Vector2& position, const Vector2& size) override;
private:

	//äÖÈ¾
	Animation animationIdle;				//Ä¬ÈÏ¶¯»­
	Animation animationExplode;				//±¬Õ¨¶¯»­
	Vector2 explodeRenderOffset;			//±¬Õ¨¶¯»­µÄÆ«ÒÆ
};
