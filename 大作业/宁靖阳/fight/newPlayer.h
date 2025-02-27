#pragma once
#include "player.h"

extern Atlas atlasnewPlayerIdleLeft;
extern Atlas atlasnewPlayerIdleRight;
extern Atlas atlasnewPlayerRunLeft;
extern Atlas atlasnewPlayerRunRight;
extern Atlas atlasnewPlayerAttackExLeft;
extern Atlas atlasnewPlayerAttackExRight;

extern Atlas atlasnewPlayerDieLeft;
extern Atlas atlasnewPlayerDieRight;

extern Player* player1;
extern Player* player2;


class newPlayer : public Player {

public:
	newPlayer(bool isFacingRight = true);


//private:
//	int invincibleTime;  // 无敌时间，单位为毫秒
//public:
//	void setInvincibleTime(int time) { invincibleTime = time; }
//	int getInvincibleTime() const { return invincibleTime; }
//	void reduceInvincibleTime(int time) { invincibleTime = (((0) > (invincibleTime - time)) ? (0) : (invincibleTime - time)); }
public:
	void update(int time) override;
	/*void receiveInput(const ExMessage& msg) override;	*/
public:
	//攻击
	void onAttack() override;
	void onAttackEx() override;
private:
	void spawnPeaBullet(float speed);

private:

	//子弹速度
	const Vector2 velocitySun{ 0.25, -0.5 };
	const float speedtransEx = 0.3;
	Animation animationtransText;
	bool istransTextVisible = false;

private:
	//攻击
	const float speedPea = 0.75;
	const float speedPeaEx = 1.5;
	const int attackExDuration = 2500;		//特殊攻击时长

	Timer timerAttackEx;					//角色特殊攻击
	Timer timerSpawnPeaEx;					//子弹特殊发射
};
