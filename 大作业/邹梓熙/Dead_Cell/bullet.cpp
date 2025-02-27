#pragma once
#include<easyx.h>
#include<vector>
#include<string>
#include"bullet.h"
#include"putimage_alpha.h"
#include"player.h"

Bullet::Bullet(int BULLET1, int BULLET2, int BULLET3, int BULLET4, int HIT)
{
	_BULLET1 = BULLET1;
	_BULLET2 = BULLET2;
	_BULLET3 = BULLET3;
	_BULLET4 = BULLET4;
	_HIT = HIT;

	load_bullet();
}

Bullet::~Bullet()
{

}

void Bullet::load_bullet()
{
	for (int i = 0; i < _BULLET1; i++) {
		std::wstring path = L"./image_source/water/bullet/bullet1/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 96, 136, true);
		img_bullet1.push_back(img);
	}

	for (int i = 0; i < _BULLET2; i++) {
		std::wstring path = L"./image_source/water/bullet/bullet2/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 96, 126, true);
		img_bullet2.push_back(img);
	}

	for (int i = 0; i < _BULLET3; i++) {
		std::wstring path = L"./image_source/water/bullet/bullet3/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 96, 189, true);
		img_bullet3.push_back(img);
	}

	for (int i = 0; i < _BULLET4; i++) {
		std::wstring path = L"./image_source/water/bullet/bullet4/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 96, 189, true);
		img_bullet4.push_back(img);
	}

	for (int i = 0; i < 3; i++) {
		for (int i = 0; i < 2; i++) {
			std::wstring path = L"./image_source/water/bullet/hit/" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 96, 96, true);
			img_hit.push_back(img);
		}
	}
	for (int i = 0; i < _HIT; i++) {
		std::wstring path = L"./image_source/water/bullet/hit/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 96, 96, true);
		img_hit.push_back(img);
	}
}

void Bullet::put_bullet()
{
	static int time = 0;
	for (int i = -150 * 4; i <= 150 * 4; i += 150) {
		Putimage_alpha::putimage_alpha(bullet_point.x + i, bullet_point.y, &img_bullet1[time / 2]);
	}
	time++;
	if (time / 2 == _BULLET1)time = 0;
}

void Bullet::put_hit()
{
	static int time = 0;
	Putimage_alpha::putimage_alpha(hit_point.x, hit_point.y, &img_bullet1[time]);
	time++;
	if (time == _BULLET1)time = 0;
}

void Bullet::restart()
{
	bullet_point = bullet_point_const;
	hit_point = hit_point_const;
}