#include "timer.h"

void Timer::reStart() {

	time = 0;
	isShotted = false;
}

void Timer::setTimer(int timerMs) {
	this->timer = timerMs;
}

void Timer::setIsOneShot(bool isOneShot) {
	this->isOneShot = isOneShot;
}

void Timer::setCallback(const std::function<void()>& cb) {
	callback = cb;
}

void Timer::setTimer(int timerMs, bool isOneShot, const std::function<void()>& cb) {
	setTimer(timerMs);
	setIsOneShot(isOneShot);
	setCallback(cb);
}

void Timer::pause() {

	isPause = true;
}

void Timer::resume() {
	isPause = false;
}

void Timer::update(int runTimeMs) {

	if (isPause)
		return;

	time += runTimeMs;		// 让定时器运行runTimeMs

	if (time >= timer) {

		if ((!isOneShot || isOneShot && !isShotted) && callback)
			callback();

		isShotted = true;
		time = 0;
	}

}

