#pragma once
#ifndef _STATUS_BAR_H_
#define _STATUS_BAR_H_

#include "util.h"

class StatusBar {
public:
	void setAvatar(IMAGE* img);
	void setPosition(int x, int y);

	void setHp(int val);
	void setMp(int val);

	void render();

private:
	const int width = 275;			//×´Ì¬Ìõ¿í¶È

private:
	int hp = 0;
	int mp = 0;
	POINT position = { 0 };
	IMAGE* imgAvatar = nullptr;
};


#endif // !_STATUS_BAR_H_

