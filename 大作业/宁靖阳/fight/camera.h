#pragma once

#include "vector2.h"
#include "timer.h"

class Camera {

public:
	static Camera& getCamera();

	void update(int runTimeMs);									//�������ִ��runTimeMs
	void shake(float shakingAmplitude, int shakingTimeMs);		//���������

public:
	void reset();												//���������λ��
	const Vector2& getPostion() const;

private:
	Vector2 pos;

	bool isShaking = false;						//�Ƿ񶶶�
	float shakingAmplitude = 0;

	Timer shakeTimer;
private:
	Camera();
};
