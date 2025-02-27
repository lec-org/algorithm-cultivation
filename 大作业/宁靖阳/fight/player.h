#pragma once
#include <graphics.h>
#include "vector2.h"
#include "animation.h"
#include "playerID.h"
#include "platform.h"
#include "bullet.h"
#include "particle.h"


extern bool isDebug;

extern IMAGE img1PCursor;
extern IMAGE img2PCursor;

extern Atlas atlasRunEffect;
extern Atlas atlasJumpEffect;
extern Atlas atlasLandEffect;

extern std::vector<Bullet*> bullets;
extern std::vector<Platform> platforms;

class Player {
public:
	Player(bool isFacingRight = true);
//private:
//	int invincibleTime;  // �޵�ʱ�䣬��λΪ����
//public:
//	void setInvincibleTime(int time) { invincibleTime = time; }
//	int getInvincibleTime() const { return invincibleTime; }
//	void reduceInvincibleTime(int time) { invincibleTime = (((0) > (invincibleTime - time)) ? (0) : (invincibleTime - time)); }
public:
	virtual void receiveInput(const ExMessage& msg);
	virtual void update(int time);
	virtual void render();

	void setId(const PlayerID& id);
	void setPosition(float x, float y);
	/*bool isSlideOutStarted1 = true;
	bool isSlideOutStarted2 = false;*/
public:
	const Vector2& getPosition() const;
	const Vector2& getSize() const;
public:
	//����
	virtual void onAttack() = 0;
	virtual void onAttackEx() = 0;
	/*virtual void trans() = 0;*/
protected:
	//�޵�
	void makeInvulnerable();

public:
	//hp mp
	void setHp(int val);
	void setMp(int val);
	const int getHp() const;
	const int getMp() const;
	bool isFacingRight = true;					//��ҳ��򡪡�(���ݰ�������)

//public:
//	virtual void trans();
protected:
	virtual void onRun(float distance);			//����
	virtual void onJump();						//��Ծ
	virtual void onLand();						//���

	void moveAndCollide(int time);				//��������ײ

protected:
	const float runVelocity = 0.55;				//�����ٶ�
	const float jumpVelocity = -0.85;			//��Ծ�ٶ�
	const float gravity = 1.6e-3f;				//�������ٶ�
	Vector2 velocity;							//����ٶ�

	PlayerID id = P1;

	//HP MP
	int hp = 100, mp = 0;

	//����
	bool isCanAttck = true;
	Timer timerAttckCd;
	int attackCd = 500;

	bool isAttackingEx = false;

	//����
	bool isCantrans = false;

	//�޵�
	IMAGE imgSketch;

	bool isInvulnerable = false;
	bool isShowSketchFram = false;		//��ǰ֡�Ƿ�Ӧ����ʾ��Ӱ

	Timer timerInvulnerable;					//����޵�
	Timer timerInvulnerableBlink;				//��˸�л�

	//������Ч
	std::vector<Particle> particles;

	Timer timerRunEffectGeneration;				//����ܶ����ӷ�����
	Timer timerDieEffectGeneration;				//����������ӷ�����

	//��ʼ�����
	bool isCursorVisible = true;
	Timer timerCursorVisibility;
	//����
	Vector2 lastHurtDirection;					//����ʱ���ܻ�����

	//������Ϣ
	bool isLeftKeyDown = false;
	bool isRightKeyDown = false;


	//�ƶ���Ϣ
	Vector2 position;							//���λ��
	Vector2 size;								//��ײ�ߴ�

	


	//��Ⱦ����
	Animation animationIdleLeft;
	Animation animationIdleRight;
	Animation animationRunLeft;
	Animation animationRunRight;

	Animation animationAttackExLeft;
	Animation animationAttackExRight;

	Animation animationJumpEffect;				//��Ծ����
	Animation animationLandEffect;				//���

	Animation animationDieLeft;					//����
	Animation animationDieRight;

	bool isJumpEffectVisible = false;			//��Ծ�ɼ�
	bool isLandEffectVisible = false;			//��ؿɼ�

	Vector2 positionJumpEffect;
	Vector2 positionLandEffect;

	Animation* currentAni = nullptr;

};
