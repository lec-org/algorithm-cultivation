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
	//设置
	void setPosition(const Vector2& position);
	void setAtlas(Atlas* atlas);
	void setLifeSpan(int lifeSpan);

	//检测
	bool checkIsValid() const;

	//更新
	void update(int deltaT);
	//渲染
	void render() const;

private:

	//物理
	Vector2 position;
	bool isValid = true;						//粒子是否有效

	//渲染
	int timer = 0;								//计时器
	int lifeSpan = 0;							//单帧持续时间
	int index = 0;								//当前帧
	Atlas* atlas = nullptr;
};
