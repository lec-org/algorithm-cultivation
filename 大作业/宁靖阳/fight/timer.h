#pragma once
#include <functional>

class Timer {
public:
	void setTimer(int timerMs);								//设置定时时间
	void setIsOneShot(bool isOneShot);						//设置定时任务 是否只触发一次
	void setCallback(const std::function<void()>& cb);		//设置定时任务
public:
	void reStart();											//重新计时
	void update(int runTimeMs);								//让定时器运行runTimeMs
public:
	void setTimer(int timerMs, bool isOneShot, const std::function<void()>& cb);
public:
	void pause();
	void resume();							//恢复运行

private:
	int timer = 0;							//定时时间
	int time = 0;							//计时器已经经过的时间

	bool isPause = false;
	bool isOneShot = false;					//任务是否只触发一次
	bool isShotted = false;					//任务是否已触发

	std::function<void()> callback;
};
