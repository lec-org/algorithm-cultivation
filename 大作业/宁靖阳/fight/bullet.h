
#pragma once
#include "vector2.h"
#include <functional>
#include "playerID.h"
#include "camera.h"
#include "graphics.h"

extern bool isDebug;

class Bullet {

public:
	//�˺�
	void setDamage(int val);
	int getDamage() const;
	//λ��
	void setPosition(float x, float y);
	const Vector2& getPosition() const;
	const Vector2& getSize() const;
	void setVelocity(float x, float y);

	//��ײ
	void setCollideTarget(const PlayerID& id);
	const PlayerID& getCollideTarget() const;

	void setValid(bool flag);
	bool getValid() const;
	bool checkCanRemove() const;

	virtual bool checkCollision(const Vector2& position, const Vector2& size);		//�����ײ
	virtual void onCollide();														//������ײ

	//�ص�
	void setCallback(const std::function<void()>& cb);
	bool isSlideOutStarted2 = false;

protected:
	//��Ļ
	bool checkIsExceedScreen();


public:
	virtual void update(int time);
	virtual void render();

protected:

	//�ӵ��ƶ�
	Vector2 position;					//λ��
	Vector2 size;						//�ߴ�
	Vector2 velocity;					//�ٶ�

	//�˺�
	int damage = 10;

	//�ӵ�״̬
	bool isValid = true;				//�Ƿ���Ч
	bool isCanRemove = false;			//�Ƿ����ɾ��

	//�ص����������������
	std::function<void()> cb;

	//Ŀ�����
	PlayerID targetID = P1;

};
