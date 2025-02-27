#pragma once

#include "atlas.h"
#include "vector2.h"
#include "util.h"

class Particle {

public:
	Particle() = default;
	Particle(const Vector2& position, Atlas* atlas, int lifeSpan) :position(position), lifeSpan(lifeSpan),
		atlas(atlas) {
	}

public:
	//����
	void setPosition(const Vector2& position);
	void setAtlas(Atlas* atlas);
	void setLifeSpan(int lifeSpan);

	//���
	bool checkIsValid() const;

	//����
	void update(int deltaT);
	//��Ⱦ
	void render() const;

private:

	//����
	Vector2 position;
	bool isValid = true;						//�����Ƿ���Ч

	//��Ⱦ
	int timer = 0;								//��ʱ��
	int lifeSpan = 0;							//��֡����ʱ��
	int index = 0;								//��ǰ֡
	Atlas* atlas = nullptr;
};
