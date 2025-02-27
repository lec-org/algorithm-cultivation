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
	//����
	void onAttack() override;
	void onAttackEx() override;
	void trans();
private:
	void spawnPeaBullet(float speed);

private:
	//����
	const float speedPea = 0.75;
	const float speedPeaEx = 1.5;
	const int attackExDuration = 2500;		//���⹥��ʱ��

	Timer timerAttackEx;					//��ɫ���⹥��
	Timer timerSpawnPeaEx;					//�ӵ����ⷢ��
};
