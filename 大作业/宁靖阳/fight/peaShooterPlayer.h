#pragma once
#include "player.h"
#include "gameScene.h"

extern Player* player1;	
extern Player* player2;	
extern Player* newplayer;	
extern bool isSlideOutStarted;
extern Atlas atlasPeaShooterIdleLeft;
extern Atlas atlasPeaShooterIdleRight;
extern Atlas atlasPeaShooterRunLeft;
extern Atlas atlasPeaShooterRunRight;
extern Atlas atlasPeaShooterAttackExLeft;
extern Atlas atlasPeaShooterAttackExRight;

extern Atlas atlasPeaShooterDieLeft;
extern Atlas atlasPeaShooterDieRight;

class PeaShooterPlayer : public Player {

public:
	PeaShooterPlayer(bool isFacingRight = true);

public:
	void update(int time) override;

	void receiveInput(const ExMessage& msg);

public:
	//攻击
	void onAttack() override;
	void onAttackEx() override;
	void trans();
private:
	void spawnPeaBullet(float speed);

private:
	//攻击
	const float speedPea = 0.75;
	const float speedPeaEx = 1.5;
	const int attackExDuration = 2500;		//特殊攻击时长

	Timer timerAttackEx;					//角色特殊攻击
	Timer timerSpawnPeaEx;					//子弹特殊发射
};
