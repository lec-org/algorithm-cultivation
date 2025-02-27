#include "statusBar.h"

void StatusBar::setAvatar(IMAGE* img) {
	imgAvatar = img;
}

void StatusBar::setPosition(int x, int y) {
	position.x = x, position.y = y;
}

void StatusBar::setHp(int val) {
	hp = val;
}

void StatusBar::setMp(int val) {
	mp = val;
}

void StatusBar::render() {

	putImageAlpha(position.x, position.y, imgAvatar);

	//»æÖÆ×´Ì¬À¸
	setfillcolor(RGB(5, 5, 5));
	solidroundrect(position.x + 100, position.y + 10, position.x + 100 + width + 3 * 2, position.y + 36, 8, 8);
	solidroundrect(position.x + 100, position.y + 45, position.x + 100 + width + 3 * 2, position.y + 71, 8, 8);

	setfillcolor(RGB(67, 47, 47));
	solidroundrect(position.x + 100, position.y + 10, position.x + 100 + width + 3, position.y + 33, 8, 8);
	solidroundrect(position.x + 100, position.y + 45, position.x + 100 + width + 3, position.y + 68, 8, 8);

	//¼ÆËãÌî³ä±ÈÀý
	float hpBarWidth = width * max(0, hp) / 100.0;
	float mpBarWidth = width * min(mp, 100) / 100.0;

	setfillcolor(RGB(197, 61, 67));
	solidroundrect(position.x + 100, position.y + 10, position.x + 100 + hpBarWidth + 3, position.y + 33, 8, 8);
	setfillcolor(RGB(83, 131, 195));
	solidroundrect(position.x + 100, position.y + 45, position.x + 100 + mpBarWidth + 3, position.y + 68, 8, 8);
}

