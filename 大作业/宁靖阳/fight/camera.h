#pragma once

#include "vector2.h"
#include "timer.h"

class Camera {

public:
	static Camera& getCamera();

	void update(int runTimeMs);									//让摄像机执行runTimeMs
	void shake(float shakingAmplitude, int shakingTimeMs);		//让摄像机震动

public:
	void reset();												//重置摄像机位置
	const Vector2& getPostion() const;

private:
	Vector2 pos;

	bool isShaking = false;						//是否抖动
	float shakingAmplitude = 0;

	Timer shakeTimer;
private:
	Camera();
};
