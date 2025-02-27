#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include"player_water.h"
#include"putimage_alpha.h"

Player_water::Player_water(int IDLE, int WALK, int SURF, int J_UP, int J_DOWN, int TUMBLE, int ATK_1, int ATK_2, int ATK_3, int SP_ATK, int HEAL, int DEFEND, int TAKE_HIT, int DEATH, int AIR_ATK)
{
	PLAYER_IDLE = IDLE;
	PLAYER_SP_ATK = SP_ATK;
	PLAYER_WALK = WALK;
	PLAYER_SURF = SURF;
	PLAYER_ATK_1 = ATK_1;
	PLAYER_ATK_2 = ATK_2;
	PLAYER_ATK_3 = ATK_3;
	PLAYER_J_UP = J_UP;
	PLAYER_J_DOWN = J_DOWN;
	PLAYER_TUMBLE = TUMBLE;
	PLAYER_HEAL = HEAL;
	PLAYER_DEFEND = DEFEND;
	PLAYER_TAKE_HIT = TAKE_HIT;
	PLAYER_DEATH = DEATH;
	PLAYER_AIR_ATK = AIR_ATK;


	load_idle();
	load_sp_attack();
	load_walk();
	load_surf();
	load_attack_1();
	load_attack_2();
	load_attack_3();
	load_j_up();
	load_j_down();
	load_tumble();
	load_heal();
	load_defend();
	load_take_hit();
	load_death();
	load_air_attack();
}

Player_water::~Player_water()
{
	printf("have deleted");
}


//加载图片函数


void Player_water::load_idle()
{
	//加载idle
	if (!img_idle_left.size() || !img_idle_right.size()) {

		static int run_time = 0;
		run_time++;
		if (run_time == 2) {
			run_time = 0;
			idle_ing = false;
		}

		for (int i = 0; i < PLAYER_IDLE; i++)
		{
			std::wstring path = L"./image_source/water/idle/idle_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_idle_right.push_back(img);
		}
		for (int i = 0; i < PLAYER_IDLE; i++)
		{
			std::wstring path = L"./image_source/water/idle/idle_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_idle_left.push_back(img);
		}
	}
}

void Player_water::load_sp_attack()
{
	//加载sp_atk
	if (!img_sp_attack_right.size() || !img_sp_attack_left.size()) {
		for (int i = 0; i < PLAYER_SP_ATK; i++)
		{
			std::wstring path = L"./image_source/water/sp_atk/sp_atk_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_sp_attack_right.push_back(img);
		}
		for (int i = PLAYER_SP_ATK - 1, j = 1; i > 0; i--, j++)
		{
			std::wstring path = L"./image_source/water/sp_atk/sp_atk_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_sp_attack_left.push_back(img);
		}
	}
}

void Player_water::load_walk()
{
	//加载walk
	if (!img_walk_right.size() || !img_walk_left.size())
	{
		for (int i = 0; i < PLAYER_WALK; i++)
		{
			std::wstring path = L"./image_source/water/walk/walk_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_walk_right.push_back(img);
		}
		for (int i = 0; i < PLAYER_WALK; i++)
		{
			std::wstring path = L"./image_source/water/walk/walk_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_walk_left.push_back(img);
		}
	}
}

void Player_water::load_surf()
{
	//加载surf
	if (!img_surf_right.size() || !img_surf_left.size())
	{
		for (int i = 0; i < PLAYER_SURF; i++)
		{
			std::wstring path = L"./image_source/water/surf/surf_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_surf_right.push_back(img);
		}
		for (int i = 0; i < PLAYER_SURF; i++)
		{
			std::wstring path = L"./image_source/water/surf/surf_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_surf_left.push_back(img);
		}
	}
}

void Player_water::load_attack_1()
{
	//加载attack_1
	if (!img_attack_1_right.size() || !img_attack_1_left.size())
	{
		for (int i = 0; i < PLAYER_ATK_1; i++)
		{
			std::wstring path = L"./image_source/water/atk_1/1_atk_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_attack_1_right.push_back(img);
		}
		for (int i = 0; i < PLAYER_ATK_1; i++)
		{
			std::wstring path = L"./image_source/water/atk_1/1_atk_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_attack_1_left.push_back(img);
		}
	}
}

void Player_water::load_attack_2()
{
	//加载attack_2
	if (!img_attack_2_right.size() || !img_attack_2_left.size())
	{
		for (int i = 0; i < PLAYER_ATK_1; i++)
		{
			std::wstring path = L"./image_source/water/atk_2/2_atk_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_attack_2_right.push_back(img);
		}
		for (int i = 0; i < PLAYER_ATK_1; i++)
		{
			std::wstring path = L"./image_source/water/atk_2/2_atk_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_attack_2_left.push_back(img);
		}
	}
}

void Player_water::load_attack_3()
{
	//加载atk_3
	if (!img_attack_3_right.size() || !img_attack_3_left.size())
	{
		for (int i = 0; i < PLAYER_ATK_3; i++)
		{
			std::wstring path = L"./image_source/water/atk_3/3_atk_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_attack_3_right.push_back(img);
		}
		for (int i = 0; i < PLAYER_ATK_3; i++)
		{
			std::wstring path = L"./image_source/water/atk_3/3_atk_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_attack_3_left.push_back(img);
		}
	}
}

void Player_water::load_j_up()
{
	//加载j_up
	if (!img_j_up_right.size() || !img_j_up_left.size())
	{
		for (int i = 0; i < PLAYER_J_UP; i++)
		{
			std::wstring path = L"./image_source/water/j_up/j_up_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_j_up_right.push_back(img);
		}
		for (int i = 0; i < PLAYER_J_UP; i++)
		{
			std::wstring path = L"./image_source/water/j_up/j_up_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_j_up_left.push_back(img);
		}
	}
}

void Player_water::load_j_down()
{
	//加载j_ down
	if (!img_j_down_right.size() || !img_j_down_left.size())
	{
		for (int i = 0; i < PLAYER_J_DOWN; i++)
		{
			std::wstring path = L"./image_source/water/j_down/j_down_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_j_down_right.push_back(img);
		}
		for (int i = 0; i < PLAYER_J_UP; i++)
		{
			std::wstring path = L"./image_source/water/j_down/j_down_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_j_down_left.push_back(img);
		}
	}
}

void Player_water::load_tumble()
{
	//加载tumble
	if (!img_tumble_right.size() || !img_tumble_left.size())
	{
		for (int i = 0; i < PLAYER_TUMBLE; i++)
		{
			std::wstring path = L"./image_source/water/tumble/tumble_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_tumble_right.push_back(img);
		}
		for (int i = 0; i < PLAYER_TUMBLE; i++)
		{
			std::wstring path = L"./image_source/water/tumble/tumble_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_tumble_left.push_back(img);
		}
	}
}

void Player_water::load_heal()
{
	//加载heal
	if (!img_heal_right.size() || !img_heal_left.size())
	{
		for (int i = 0; i < PLAYER_HEAL; i++)
		{
			std::wstring path = L"./image_source/water/heal/heal_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_heal_right.push_back(img);
		}
		for (int i = 0; i < PLAYER_HEAL; i++)
		{
			std::wstring path = L"./image_source/water/heal/heal_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_heal_left.push_back(img);
		}
	}
}

void Player_water::load_defend()
{
	//加载defend
	if (!img_defend_right.size() || !img_defend_left.size())
	{
		for (int i = 0; i < PLAYER_DEFEND; i++)
		{
			std::wstring path = L"./image_source/water/heal/heal_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_defend_right.push_back(img);
		}
		for (int i = 0; i < PLAYER_DEFEND; i++)
		{
			std::wstring path = L"./image_source/water/heal/heal_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_defend_left.push_back(img);
		}
	}
}

void Player_water::load_take_hit()
{
	//加载take_hit
	if (!img_take_hit_right.size() || !img_take_hit_left.size())
	{
		for (int i = 0; i < PLAYER_TAKE_HIT; i++)
		{
			std::wstring path = L"./image_source/water/take_hit/take_hit_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_take_hit_right.push_back(img);
		}
		for (int i = 0; i < PLAYER_TAKE_HIT; i++)
		{
			std::wstring path = L"./image_source/water/take_hit/take_hit_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_take_hit_left.push_back(img);
		}
	}
}

void Player_water::load_death()
{
	//加载death
	if (!img_death_right.size() || !img_death_left.size())
	{
		for (int i = 0; i < PLAYER_TAKE_HIT; i++)
		{
			std::wstring path = L"./image_source/water/death/death_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_take_hit_right.push_back(img);
		}
		for (int i = 0; i < PLAYER_TAKE_HIT; i++)
		{
			std::wstring path = L"./image_source/water/death/death_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_take_hit_left.push_back(img);
		}
	}
}

void Player_water::load_air_attack()
{
	//加载air_attack
	if (!img_air_attack_right.size() || !img_air_attack_left.size())
	{
		for (int i = 0; i < PLAYER_AIR_ATK; i++)
		{
			std::wstring path = L"./image_source/water/air_atk/air_atk_" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_air_attack_right.push_back(img);
		}
		for (int i = 0; i < PLAYER_AIR_ATK; i++)
		{
			std::wstring path = L"./image_source/water/air_atk/air_atk_0" + std::to_wstring(i + 1) + L".png";
			IMAGE img;
			loadimage(&img, path.c_str(), 576, 256, true);
			img_air_attack_left.push_back(img);
		}
	}
}



//渲染图片函数
void Player_water::put_idle()
{
	static int time = 0;
	if(point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_IDLE)time = 0;
}

void Player_water::put_sp_attack()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_SP_ATK)time = 0;
}

void Player_water::put_walk()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_WALK)time = 0;
}

void Player_water::put_surf()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_IDLE)time = 0;
}

void Player_water::put_attack_1()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_IDLE)time = 0;
}

void Player_water::put_attack_2()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_IDLE)time = 0;
}

void Player_water::put_attack_3()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_IDLE)time = 0;
}

void Player_water::put_j_up()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_IDLE)time = 0;
}

void Player_water::put_j_down()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_IDLE)time = 0;
}

void Player_water::put_tumble()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_IDLE)time = 0;
}

void Player_water::put_heal()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_IDLE)time = 0;
}

void Player_water::put_defend()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_IDLE)time = 0;
}

void Player_water::put_take_hit()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_IDLE)time = 0;
}

void Player_water::put_death()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_IDLE)time = 0;
}

void Player_water::put_air_attack()
{
	static int time = 0;
	if (point_right)Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_right[time / 2]);
	else Putimage_alpha::putimage_alpha(player_point.x, player_point.y, &img_idle_left[time / 2]);
	time++;
	if (time / 2 == PLAYER_IDLE)time = 0;
}



void Player_water::change_data()
{
	
}

void Player_water::player_action()
{

}