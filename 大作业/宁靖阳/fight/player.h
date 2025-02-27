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
//	int invincibleTime;  // 无敌时间，单位为毫秒
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
	//攻击
	virtual void onAttack() = 0;
	virtual void onAttackEx() = 0;
	/*virtual void trans() = 0;*/
protected:
	//无敌
	void makeInvulnerable();

public:
	//hp mp
	void setHp(int val);
	void setMp(int val);
	const int getHp() const;
	const int getMp() const;
	bool isFacingRight = true;					//玩家朝向——(根据按键决定)

//public:
//	virtual void trans();
protected:
	virtual void onRun(float distance);			//奔跑
	virtual void onJump();						//跳跃
	virtual void onLand();						//落地

	void moveAndCollide(int time);				//重力和碰撞

protected:
	const float runVelocity = 0.55;				//奔跑速度
	const float jumpVelocity = -0.85;			//跳跃速度
	const float gravity = 1.6e-3f;				//重力加速度
	Vector2 velocity;							//玩家速度

	PlayerID id = P1;

	//HP MP
	int hp = 100, mp = 0;

	//攻击
	bool isCanAttck = true;
	Timer timerAttckCd;
	int attackCd = 500;

	bool isAttackingEx = false;

	//变身
	bool isCantrans = false;

	//无敌
	IMAGE imgSketch;

	bool isInvulnerable = false;
	bool isShowSketchFram = false;		//当前帧是否应该显示剪影

	Timer timerInvulnerable;					//玩家无敌
	Timer timerInvulnerableBlink;				//闪烁切换

	//粒子特效
	std::vector<Particle> particles;

	Timer timerRunEffectGeneration;				//玩家跑动粒子发射器
	Timer timerDieEffectGeneration;				//玩家死亡粒子发射器

	//初始化光标
	bool isCursorVisible = true;
	Timer timerCursorVisibility;
	//死亡
	Vector2 lastHurtDirection;					//死亡时的受击方向

	//按键信息
	bool isLeftKeyDown = false;
	bool isRightKeyDown = false;


	//移动信息
	Vector2 position;							//玩家位置
	Vector2 size;								//碰撞尺寸

	


	//渲染数据
	Animation animationIdleLeft;
	Animation animationIdleRight;
	Animation animationRunLeft;
	Animation animationRunRight;

	Animation animationAttackExLeft;
	Animation animationAttackExRight;

	Animation animationJumpEffect;				//跳跃动画
	Animation animationLandEffect;				//落地

	Animation animationDieLeft;					//死亡
	Animation animationDieRight;

	bool isJumpEffectVisible = false;			//跳跃可见
	bool isLandEffectVisible = false;			//落地可见

	Vector2 positionJumpEffect;
	Vector2 positionLandEffect;

	Animation* currentAni = nullptr;

};
