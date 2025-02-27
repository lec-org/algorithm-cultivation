#pragma once
#include<iostream>
#include<windows.h>
#include<easyx.h>
#include<graphics.h>
#include<vector>



class Bullet {
public:
	Bullet(int BULLET1, int BULLET2, int BULLET3, int BULLET4, int HIT);
	~Bullet();

	void load_bullet();

	void put_bullet();
	void put_hit();

	void restart();


	std::vector<IMAGE> img_bullet1;
	std::vector<IMAGE> img_bullet2;
	std::vector<IMAGE> img_bullet3;
	std::vector<IMAGE> img_bullet4;
	std::vector<IMAGE> img_hit;

	


	POINT bullet_point = { 1280 / 2 - 48, 0 };

	POINT hit_point = { 0, 0 };



	const int down_speed = 30;
private:
	int _BULLET1;
	int _BULLET2;
	int _BULLET3;
	int _BULLET4;
	int _HIT;
	
	POINT bullet_point_const = { 1280 / 2 - 48, 0 };

	POINT hit_point_const = { 0, 0 };
};