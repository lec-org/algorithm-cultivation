
#pragma once
#include "vector2.h"
#include <functional>
#include "playerID.h"
#include "camera.h"
#include "graphics.h"

extern bool isDebug;

class Bullet {

public:
	//伤害
	void setDamage(int val);
	int getDamage() const;
	//位置
	void setPosition(float x, float y);
	const Vector2& getPosition() const;
	const Vector2& getSize() const;
	void setVelocity(float x, float y);

	//碰撞
	void setCollideTarget(const PlayerID& id);
	const PlayerID& getCollideTarget() const;

	void setValid(bool flag);
	bool getValid() const;
	bool checkCanRemove() const;

	virtual bool checkCollision(const Vector2& position, const Vector2& size);		//检测碰撞
	virtual void onCollide();														//处理碰撞

	//回调
	void setCallback(const std::function<void()>& cb);
	bool isSlideOutStarted2 = false;

protected:
	//屏幕
	bool checkIsExceedScreen();


public:
	virtual void update(int time);
	virtual void render();

protected:

	//子弹移动
	Vector2 position;					//位置
	Vector2 size;						//尺寸
	Vector2 velocity;					//速度

	//伤害
	int damage = 10;

	//子弹状态
	bool isValid = true;				//是否有效
	bool isCanRemove = false;			//是否可以删除

	//回调——增加玩家能量
	std::function<void()> cb;

	//目标玩家
	PlayerID targetID = P1;

};
