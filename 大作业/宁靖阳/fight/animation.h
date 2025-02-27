#pragma once
#include <graphics.h>
#include "atlas.h"
#include <functional>

class Animation {
public:
	void update(int playTime);								//更新动画数据——让动画播放的时间。
	void render(int x, int y);								//渲染
public:
	void reset();
public:
	void setAtlas(Atlas* atlas);
	void setInterval(int ms);
	void setIsLoop(bool isLoop);
	void setCallback(const std::function<void()>& cb);

public:
	int getFrameIndex();
	IMAGE* getFrame();
public:
	bool checkFinish();

private:
	int time = 0;								//计时器——动画已经播放的时间
	int index = 0;								//帧索引
	bool isLoop = true;

	int interval;								//帧间隔
	Atlas* atlas;
	std::function<void()> callback;
};
