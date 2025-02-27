#pragma once
#include "player.h"
#include "sunBullet.h"
#include "sunBulletEx.h"


extern Atlas atlasSunFlowerIdleLeft;
extern Atlas atlasSunFlowerIdleRight;
extern Atlas atlasSunFlowerRunLeft;
extern Atlas atlasSunFlowerRunRight;

extern Atlas atlasSunFlowerAttackExLeft;
extern Atlas atlasSunFlowerAttackExRight;
extern Atlas atlasSunText;

extern Atlas atlasSunFlowerDieLeft;
extern Atlas atlasSunFlowerDieRight;

extern Player* player1;
extern Player* player2;

class SunFlowerPlayer : public Player {

public:
	SunFlowerPlayer(bool isFacingRight = true);

public:
	void update(int time) override;
	void render() override;
public:
	//¹¥»÷
	void onAttack() override;
	void onAttackEx() override;
private:

	//×Óµ¯ËÙ¶È
	const Vector2 velocitySun{ 0.25, -0.5 };
	const float speedSunEx = 0.15;

	//äÖÈ¾
	Animation animationSunText;
	bool isSunTextVisible = false;
};
