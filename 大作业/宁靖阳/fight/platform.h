#pragma once
#include <graphics.h>
#include "camera.h"
#include "util.h"

extern bool isDebug;

class Platform {

	//碰撞箱为一条直线
	struct CollisionShape {
		float y;			//线的高度

		float left, right;	//线的左右端点
	};

public:
	//渲染数据
	IMAGE* img = nullptr;
	POINT renderPos = { 0 };

	//碰撞数据
	CollisionShape shape;	//平台碰撞箱
public:

	void render() const;
};
