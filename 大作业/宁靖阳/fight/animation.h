#pragma once
#include <graphics.h>
#include "atlas.h"
#include <functional>

class Animation {
public:
	void update(int playTime);								//���¶������ݡ����ö������ŵ�ʱ�䡣
	void render(int x, int y);								//��Ⱦ
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
	int time = 0;								//��ʱ�����������Ѿ����ŵ�ʱ��
	int index = 0;								//֡����
	bool isLoop = true;

	int interval;								//֡���
	Atlas* atlas;
	std::function<void()> callback;
};
