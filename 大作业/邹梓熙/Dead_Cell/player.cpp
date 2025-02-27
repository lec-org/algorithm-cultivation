#include<easyx.h>
#include<vector>
#include<string>
#include"player.h"
#include"putimage_alpha.h"

Player::Player(int IDLE, int RUN, int J_UP, int J_DOWN, int LAND, int ATK_1, int ATK_2, int TAKE_HIT, int DEATH, int DASH)
{
	_IDLE = IDLE;
	_RUN = RUN;
	_ATK_1 = ATK_1;
	_ATK_2 = ATK_2;
	_LAND = LAND;
	_J_UP = J_UP + 100;
	_J_DOWN = J_DOWN;
	_TAKE_HIT = TAKE_HIT;
	_DEATH = DEATH;
	_DASH = DASH;


	load_attack_1();
	load_attack_2();
	load_idle();
	load_j_up();
	load_j_down();
	load_land();
	load_run();
	load_dash();

	load_death();
	load_take_hit();

	load_hp();

	load_start();

}

Player::~Player()
{

}

void Player::load_attack_1()
{
	//加载attack_1
	for (int i = 0; i < _ATK_1; i++)
	{
		std::wstring path = L"./image_source/player/Attack1/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_attack_1_right.push_back(img);
	}
	for (int i = 0; i < _ATK_1; i++)
	{
		std::wstring path = L"./image_source/player/Attack1/0" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_attack_1_left.push_back(img);
	}
}

void Player::load_attack_2()
{
	//加载attack_2
	for (int i = 0; i < _ATK_1; i++)
	{
		std::wstring path = L"./image_source/player/Attack2/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_attack_2_right.push_back(img);
	}
	for (int i = 0; i < _ATK_1; i++)
	{
		std::wstring path = L"./image_source/player/Attack2/0" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_attack_2_left.push_back(img);
	}
}

void Player::load_idle()
{
	//加载idle
	for (int i = 0; i < _IDLE; i++)
	{
		std::wstring path = L"./image_source/player/Idle/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_idle_right.push_back(img);
	}
	for (int i = 0; i < _IDLE; i++)
	{
		std::wstring path = L"./image_source/player/Idle/0" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_idle_left.push_back(img);
	}
}

void Player::load_j_up()
{
	//加载j_up
	for (int i = 0; i < _J_UP - 100; i++)
	{
		std::wstring path = L"./image_source/player/j_up/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_j_up_right.push_back(img);
	}
	for (int i = 0; i < _J_UP - 100; i++)
	{
		std::wstring path = L"./image_source/player/j_up/0" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_j_up_left.push_back(img);
	}
	IMAGE img1;
	loadimage(&img1, L"./image_source/player/j_up/5.png", 150, 150, true);
	IMAGE img2;
	loadimage(&img2, L"./image_source/player/j_up/05.png", 150, 150, true);
	for (int i = 0; i < 100; i++) {
		img_j_up_right.push_back(img1);
		img_j_up_left.push_back(img2);
	}
}

void Player::load_j_down()
{
	//加载j_down
	for (int i = 0; i < _J_DOWN; i++)
	{
		std::wstring path = L"./image_source/player/j_down/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_j_down_right.push_back(img);
	}
	for (int i = 0; i < _J_DOWN; i++)
	{
		std::wstring path = L"./image_source/player/j_down/0" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_j_down_left.push_back(img);
	}
}

void Player::load_land()
{
	//加载land
	for (int i = 0; i < _LAND; i++)
	{
		std::wstring path = L"./image_source/player/Land/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_land_right.push_back(img);
	}
	for (int i = 0; i < _LAND; i++)
	{
		std::wstring path = L"./image_source/player/Land/0" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_land_left.push_back(img);
	}
}

void Player::load_run()
{
	//加载run
	for (int i = 0; i < _RUN; i++)
	{
		std::wstring path = L"./image_source/player/Run/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_run_right.push_back(img);
	}
	for (int i = 0; i < _RUN; i++)
	{
		std::wstring path = L"./image_source/player/Run/0" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_run_left.push_back(img);
	}
}

void Player::load_death()
{
	//加载death
	for (int i = 0; i < _DEATH; i++)
	{
		std::wstring path = L"./image_source/player/Death/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_death_right.push_back(img);
	}
	for (int i = 0; i < _DEATH; i++)
	{
		std::wstring path = L"./image_source/player/Death/0" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_death_left.push_back(img);
	}
}

void Player::load_take_hit()
{
	//加载take_hit
	for (int i = 0; i < _TAKE_HIT; i++)
	{
		std::wstring path = L"./image_source/player/Hit/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_take_hit_right.push_back(img);
	}
	for (int i = 0; i < _TAKE_HIT; i++)
	{
		std::wstring path = L"./image_source/player/Hit/0" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);  
		img_take_hit_left.push_back(img);
	}
}

void Player::load_dash()
{
	//加载dash
	for (int i = 0; i < _DASH; i++)
	{
		std::wstring path = L"./image_source/player/dash/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_dash_right.push_back(img);
	}
	for (int i = 0; i < _DASH; i++)
	{
		std::wstring path = L"./image_source/player/dash/0" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 150, 150, true);
		img_dash_left.push_back(img);
	}
}


void Player::load_hp()
{
	//加载hp
	for (int i = 0; i < 6; i++)
	{
		std::wstring path = L"./image_source/hp/" + std::to_wstring(i) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 188, 174, true);
		img_hp.push_back(img);
	}
	
}

void Player::load_start()
{
	//加载start
	for (int i = 0; i < 3; i++)
	{
		std::wstring path = L"./image_source/player/stare/" + std::to_wstring(i + 1) + L".png";
		IMAGE img;
		loadimage(&img, path.c_str(), 550, 550, true);
		img_start.push_back(img);
	}
	std::wstring path = L"./image_source/player/stare/2.png";
	IMAGE img;
	loadimage(&img, path.c_str(), 550, 550, true);
	img_start.push_back(img);
}


void Player::put_idle()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_idle_right[time]);
	else Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_idle_left[time]);
	time++;
	if (time == _IDLE)time = 0;
}

void Player::put_run()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_run_right[time]);
	else Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_run_left[time]);
	time++;
	if (time == _RUN)time = 0;
}

void Player::put_attack_1()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_attack_1_right[time]);
	else Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_attack_1_left[time]);
	time++;
	if (time == _ATK_1)time = 0;
}

void Player::put_attack_2()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_attack_2_right[time]);
	else Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_attack_2_left[time]);
	time++;
	if (time == _ATK_2)time = 0;
}

void Player::put_j_up()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_j_up_right[time]);
	else Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_j_up_left[time]);
	time++;
	if (time == _J_UP)time = 0;
}

void Player::put_j_down()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_j_down_right[time]);
	else Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_j_down_left[time]);
	time++;
	if (time == _J_DOWN)time = 0;
}

void Player::put_land()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_land_right[time]);
	else Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_land_left[time]);
	time++;
	if (time == _LAND)time = 0;
}

void Player::put_take_hit()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_take_hit_right[time]);
	else Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_take_hit_left[time]);
	time++;
	if (time == _TAKE_HIT)time = 0;
}

void Player::put_death()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_death_right[time / 40]);
	else Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_death_left[time / 40]);
	time++;
	if (time / 40 == _DEATH)time = 0;
}


void Player::put_dash()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_dash_right[time]);
	else Putimage_alpha::putimage_alpha(enemy_point.x, enemy_point.y, &img_dash_left[time]);
	time++;
	if (time == _DASH)time = 0;
}

void Player::put_hp()
{
	Putimage_alpha::putimage_alpha(0, 10, &img_hp[HP]);
}

void Player::put_start()
{
	static int time = 0;
	Putimage_alpha::putimage_alpha(-70, 170, &img_start[time / 23]);
	time++;
	if (time / 23 == _START)time = 0;
}