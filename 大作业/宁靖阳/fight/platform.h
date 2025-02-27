#pragma once
#include <graphics.h>
#include "camera.h"
#include "util.h"

extern bool isDebug;

class Platform {

	//��ײ��Ϊһ��ֱ��
	struct CollisionShape {
		float y;			//�ߵĸ߶�

		float left, right;	//�ߵ����Ҷ˵�
	};

public:
	//��Ⱦ����
	IMAGE* img = nullptr;
	POINT renderPos = { 0 };

	//��ײ����
	CollisionShape shape;	//ƽ̨��ײ��
public:

	void render() const;
};
