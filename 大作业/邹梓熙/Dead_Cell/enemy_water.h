#pragma once
#include<easyx.h>
#include<vector>
#include<iostream>
#include"enemy_base.h"
class Enemy_water : public Enemy_base {
public:
	Enemy_water(int IDLE, int WALK, int SURF, int J_UP, int J_DOWN, int TUMBLE, int ATK_1, int ATK_2, int ATK_3, int SP_ATK, int HEAL, int DEFEND, int TAKE_HIT, int DEATH, int AIR_ATK);
	~Enemy_water();

	//加载图片函数
	void load_idle();
	void load_sp_attack();
	void load_walk();
	void load_surf();
	void load_attack_1();
	void load_attack_2();
	void load_attack_3();
	void load_j_up();
	void load_j_down();
	void load_tumble();
	void load_heal();
	void load_defend();
	void load_take_hit();
	void load_death();
	void load_air_attack();



	//渲染图片
	void put_idle();
	void put_sp_attack();
	void put_walk();
	void put_surf();
	void put_attack_1();
	void put_attack_2();
	void put_attack_3();
	void put_j_up();
	void put_j_down();
	void put_tumble();
	void put_heal();
	void put_defend();
	void put_take_hit();
	void put_death();
	void put_air_attack();


	void change_data();

	void player_action();


	//使用vector来取代传统数组来储存，
	std::vector<IMAGE> img_idle_left;
	std::vector<IMAGE> img_idle_right;

	std::vector<IMAGE> img_sp_attack_right;
	std::vector<IMAGE> img_sp_attack_left;

	std::vector<IMAGE> img_walk_right;
	std::vector<IMAGE> img_walk_left;

	std::vector<IMAGE> img_surf_right;
	std::vector<IMAGE> img_surf_left;

	std::vector<IMAGE> img_attack_1_right;
	std::vector<IMAGE> img_attack_1_left;

	std::vector<IMAGE> img_attack_2_right;
	std::vector<IMAGE> img_attack_2_left;

	std::vector<IMAGE> img_attack_3_right;
	std::vector<IMAGE> img_attack_3_left;

	std::vector<IMAGE> img_j_up_right;
	std::vector<IMAGE> img_j_up_left;

	std::vector<IMAGE> img_j_down_right;
	std::vector<IMAGE> img_j_down_left;

	std::vector<IMAGE> img_tumble_right;
	std::vector<IMAGE> img_tumble_left;

	std::vector<IMAGE> img_heal_right;
	std::vector<IMAGE> img_heal_left;

	std::vector<IMAGE> img_defend_right;
	std::vector<IMAGE> img_defend_left;

	std::vector<IMAGE> img_take_hit_right;
	std::vector<IMAGE> img_take_hit_left;

	std::vector<IMAGE> img_death_right;
	std::vector<IMAGE> img_death_left;

	std::vector<IMAGE> img_air_attack_right;
	std::vector<IMAGE> img_air_attack_left;


	//判断在这一帧中，有无键盘A,D信息
	bool is_move_left = false;//A
	bool is_move_right = false;//D

	bool point_right = false;//判断人物朝向变量

	//判断动作是否还在进行
	int surf_ing = 0;//I
	bool atk_3_ing = false;//S + U
	bool atk_2_ing = false;//W + U
	bool atk_1_ing = false;//U
	bool j_up_ing = false;//K
	bool j_down_ing = false;//下落
	bool tumble_ing = false;//L
	bool heal_ing = false;//O

	int take_hit_ing = 0;
	bool death_ing = false;
	bool air_ing = false;//空中J

	bool idle_ing = true;

	int sp_attack = 0;


	POINT enemy_point = { 900, 355 };

	int HP = 200;
	int act_time = 0;
	const int S_SPEED = 20;

private:
	//动画帧数
	int _IDLE;
	int _SP_ATK;
	int _WALK;
	int _SURF;
	int _ATK_1;
	int _ATK_2;
	int _ATK_3;
	int _J_UP;
	int _J_DOWN;
	int _TUMBLE;
	int _HEAL;
	int _DEFEND;
	int _TAKE_HIT;
	int _DEATH;
	int _AIR_ATK;



};