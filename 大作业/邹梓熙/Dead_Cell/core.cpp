//反思：用queue来储存图片，用完就pop，占用内存小-------2024.12.20，17:22



//反思：用sleep函数控制每次加载图片的时间来达到每一次打印图片的时间间隔更相同， 但是基于有时一次循环要加载多章图片，消耗的时间长，导致动画要么卡顿， 要么动画帧率低，
//		现在在考虑的几种解决方案：1. 每次循环只loadimage一张图片 2. 取消使用queue，改用数组，循环之前就loadimage全部图片 3. 牺牲图片像素
//		现在还有要学习的知识来优化卡顿问题：1. 双缓存 2. 多线程--------2025.01.01，21:13



//决定：现在决定使用vector在循环之前加载图片，使得主循环while循环时只需要渲染图片即可，减少卡顿-------2025.01.0，21:00



//学习：学习和实现双缓存的函数 beginbatchdraw() 和 flushbatchdraw() 函数-------2025.01.03，13:21

//决定：因双人对战感觉很复杂，而且不是我想要的游戏效果，然后我想要BOOS的技能很多很强的效果，画风是那种偏黑暗的，因为素材只找到一个简洁黑暗风的人物，各个人物的技能攻击种类数量也不相同
// 所以现在暂定游戏为单人游戏，只有一个人物，多动作，多小怪，多BOOS--------2025.01.04， 20:04

//决定：感觉弄很多人物需要的时间太多了，所以只做一个boos----------2025.01.20,  10:14

//进度：将帧率从60帧降到了30帧，是画面更流畅不卡顿了---------2025.01.31,    12:33
#include<iostream>
#include<Windows.h>
#include<mmsystem.h>
#include<string>
#include<easyx.h>
#include<graphics.h>
#include<math.h>

#include"keyboard.h"
#include"enemy_water.h"
#include"Player.h"
#include"background.h"
#include"BOOS.h"
#include"bullet.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "MSIMG32.LIB")



int main()
{
	//界面音乐
	mciSendString(L"open \"./image_source/music/2.mp3\" alias music1", NULL, 0, NULL);
	mciSendString(L"setaudio music1 volume to 550", NULL, 0, NULL);
	//背景音乐
	mciSendString(L"open \"./image_source/music/7.mp3\" alias music", NULL, 0, NULL);
	mciSendString(L"setaudio music volume to 550", NULL, 0, NULL);
	/*mciSendString(L"open \"./image_source/music/1.mp3\" alias music1", NULL, 0, NULL);
	mciSendString(L"play music1 repeat from 0", NULL, 0, NULL);*/


	//player音效

	//脚步声
	mciSendString(L"open \"./sound/run4.wav\" alias run", NULL, 0, NULL);


	//attack声
	mciSendString(L"open \"./sound/player/attack1.wav\" alias attack1", NULL, 0, NULL);
	mciSendString(L"open \"./sound/player/attack2.wav\" alias attack2", NULL, 0, NULL);
	mciSendString(L"open \"./sound/player/attack_impact1.wav\" alias attack_impact1", NULL, 0, NULL);
	mciSendString(L"open \"./sound/player/attack_impact2.wav\" alias attack_impact2", NULL, 0, NULL);
	mciSendString(L"open \"./sound/player/dash.wav\" alias dash", NULL, 0, NULL);
	


	initgraph(1280, 720, EW_SHOWCONSOLE);

	bool running = true;

	//water死亡
	int water_time = 0;
	//player死亡
	int player_time = 0;


//变量声明
	//声明玩家
	Player player(17, 6, 5, 3, 4, 7, 7, 3, 19, 15);
	//水元素法师玩家
	Enemy_water water(8, 10, 8, 3, 3, 6, 7, 21, 27, 21, 12, 12, 7, 16, 8);
	//子弹
	Bullet bullet(4, 6, 4, 5, 5);
	
	//背景
	Background background;

	//储存键盘信息的变量
	ExMessage msg;



	//储存时间
	unsigned long start_time = 0;
	unsigned long end_time = 0;

	//加载背景
	background.load_background();
	background.load_ui();

	//播放界面音乐
	mciSendString(L"play music1 repeat from 0", NULL, 0, NULL);
	BeginBatchDraw();
	while (running)
	{
		bool is_Mouse_Down = false;
		static int mouse_x;
		static int mouse_y;

		static int count_time = 0;
		static bool check1 = false;
		static bool check2 = false;
		while (peekmessage(&msg))//获取外设信息，有外部输入返回1，如果在攻击时间里就不进入循环
		{
			if (msg.message == WM_LBUTTONDOWN)//键盘按下
			{
				is_Mouse_Down = true;
			}
			else if (msg.message == WM_LBUTTONUP)//键盘抬起
			{
				is_Mouse_Down = false;
			}
			else if (msg.message == WM_MOUSEMOVE)//鼠标移动
			{
				mouse_x = msg.x;
				mouse_y = msg.y;
			}



		}

		background.put_background();
		player.put_start();


		if (is_Mouse_Down && (mouse_x >= 659 && mouse_x <= 659 + 90) && (mouse_y >= 550 && mouse_y <= 550 + 90)) {
			background.put_ui2();
			check1 = true;
		}
		else if (is_Mouse_Down && check1) {
			background.put_ui2();
		}
		else if (check1 && !is_Mouse_Down) {
			background.put_ui1();
			check2 = true;
		}
		else {
			background.put_ui1();
		}

		background.put_text();




		if (check2) {
			count_time++;
		}

		if (count_time >= 10) {
			break;
		}




		end_time = GetTickCount64();//获取这一帧结束时间
		unsigned long delta_time = end_time - start_time;

		//计时器，使每一帧的时间是一样的
		if (delta_time < 1000 / 32)
		{
			Sleep(1000 / 32 - delta_time);
		}

		FlushBatchDraw();

		start_time = GetTickCount64();//这一帧开始时间
	}
	EndBatchDraw();

	//结束界面音乐
	mciSendString(L"close music1", NULL, 0, NULL);





















	//播放背景音乐
	mciSendString(L"play music repeat from 0", NULL, 0, NULL);


	BeginBatchDraw();

	while (running)
	{
		while (peekmessage(&msg) && water.HP > 0 && player.HP > 0)//获取外设信息，有外部输入返回1，如果在攻击时间里就不进入循环
		{
			if (msg.message == WM_KEYDOWN && !player.dash_ing)//键盘按下
			{
				switch (msg.vkcode)//键值
				{
				case VK_A:
					player.is_move_left = true;
					player.point_right = false;
					break;

				case VK_D:
					player.is_move_right = true;   
					player.point_right = true;
					break;

				case VK_W:

					break;

				case VK_S:
					break;

				case VK_U:

					break;

				case VK_L:
					if (!player.no_dash) {
						player.dash_ing = 5;
						player.no_dash = 20;
					}
					break;  

				case VK_I:

					break;

				case VK_K:
					player.is_j_up = true;
					break;

				case VK_O:
					break;

				case VK_J:
					if (!player.atk_1_ing && !player.atk_time && !player.atk_2_ing) {
						player.atk_1_ing = 7;
						player.atk_time = 14;
					}
					else if (!player.atk_1_ing && player.atk_time && !player.atk_2_ing) {
						player.atk_2_ing = 7;
					}
				}
			}
			else if (msg.message == WM_KEYUP)//键盘抬起
			{
				switch (msg.vkcode)//键值
				{
				case VK_A:
					player.is_move_left = false;
					break;

				case VK_D:
					player.is_move_right = false;
					break;

				case VK_W:

					break;

				case VK_S:
					
					break;
				case VK_K:
					player.is_j_up = false;
				}
			}
		}

		//player与enemy的位置差
		int player_xx = player.enemy_point.x + 75;
		int player_yy = player.enemy_point.y + 75;
		int water_xx = water.enemy_point.x + 288;
		int water_yy = water.enemy_point.y + 213;
		int bullet_xx = bullet.bullet_point.x + 48;
		int bullet_yy = bullet.bullet_point.y + 68;

		int dif = player_xx - water_xx;
		int dif_h = player_yy - water_yy ;

		int dif_bullet = 10000;
		for (int i = -150 * 4; i <= 150 * 4; i += 150) {
			dif_bullet = min(dif_bullet, abs(player_xx + i - bullet_xx));
		}
		int dif_bullet_h = player_yy - bullet_yy;


		//渲染背景
		background.put_background();
		player.put_hp();


		//water攻击计时
		if (water.HP <= 0 || player.HP <= 0) {

		}
		else if (water.act_time % (32 * 4) == 20) {
			water.surf_ing = 40;
		}
		else if (water.act_time % (32 * 4) == 32 * 2 + 20 && water.HP <= 200) {
			water.sp_attack = 42;
		}



		//攻击判定or受伤判定
		if ((player.atk_1_ing || player.atk_2_ing) && !water.surf_ing && !water.sp_attack) {
			if (player.point_right && water.enemy_point.x + 288 > player.enemy_point.x + 80 && water.enemy_point.x + 288 < player.enemy_point.x + 155 && water.enemy_point.y + 178 > player.enemy_point.y + 25 && water.enemy_point.y + 178 < player.enemy_point.y + 125) {
				water.take_hit_ing = 7;
				water.HP--;
			}
			else if (!player.point_right && water.enemy_point.x + 288 > player.enemy_point.x - 5 && water.enemy_point.x + 288 < player.enemy_point.x + 60 && water.enemy_point.y + 178 > player.enemy_point.y + 25 && water.enemy_point.y + 178 < player.enemy_point.y + 125) {
				water.take_hit_ing = 7;
				water.HP--;
			}
		}


		if (abs(dif) <= 30 && !player.no_enemy_time && !player.take_hit_ing && !player.take_hit_ing_serious && dif_h >= -50) {
			player.take_hit_ing = 6;
			player.no_enemy_time = 70;
		}
		if (abs(dif_bullet) <= 40 && !player.no_enemy_time && !player.take_hit_ing && !player.take_hit_ing_serious && abs(dif_bullet_h) <= 150) {
			player.take_hit_ing = 6;
			player.no_enemy_time = 70;
		}
		if (water.sp_attack <= 20 && water.sp_attack >= 4 && !player.no_enemy_time && !player.take_hit_ing && !player.take_hit_ing_serious) {
			if (water.point_right && player_xx >= water_xx && player_xx <= water_xx + 192) {
				player.take_hit_ing_serious = 6;
				player.no_enemy_time = 70;
			}
			else if(player_xx <= water_xx && player_xx >= water_xx - 192 && !player.no_enemy_time && !player.take_hit_ing && !player.take_hit_ing_serious){
				player.take_hit_ing_serious = 6;
				player.no_enemy_time = 70;
			}
		}



		//人物动作
		if (player.is_move_right && !player.is_move_left)player.point_right = true;
		if (!player.is_move_right && player.is_move_left)player.point_right = false;


		//bullet数据修改
		if (water.sp_attack >= 4) {
			if (water.sp_attack <= 20) {
				bullet.bullet_point.y += bullet.down_speed;
			}
		}



		//bullet图像修改
		if (water.sp_attack >= 4) {
			bullet.put_bullet();
		}







		//enemy数据修改
		if (player.HP <= 0) {
			if (player_time <= 10) {
				if (dif >= 0) {
					water.enemy_point.x -= 25;
				}
				else {
					water.enemy_point.x += 25;
				}
			}
		}
		else if (water.HP <= 0) {
			if (water_time <= 10) {
				if (dif >= 0) {
					water.enemy_point.x -= 25;
				}
				else {
					water.enemy_point.x += 25;
				}
			}
		}
		else if (water.sp_attack) {
			if (water.sp_attack == 21) {
				if (dif >= 0) {
					water.point_right = true;
				}
				else {
					water.point_right = false;
				}
			}
		}
		else if (water.surf_ing) {
			if (water.surf_ing == 40) {
				if (dif >= 0) {
					water.point_right = true;
				}
				else {
					water.point_right = false;
				}
			}
			if (water.point_right) {
				if (water.surf_ing >= 35) {
					water.enemy_point.x -= water.S_SPEED;
				}
				else {
					water.enemy_point.x += water.S_SPEED;
				}
			}
			else {
				if (water.surf_ing >= 35) {
					water.enemy_point.x += water.S_SPEED;
				}
				else {
					water.enemy_point.x -= water.S_SPEED;
				}
			}
		}
		else if (water.take_hit_ing) {
				if (dif >= 0) {
					water.enemy_point.x -= 3;
				}
				else {
					water.enemy_point.x += 3;
				}
		}
		else if (dif >= 0) {
			water.point_right = true;
			water.enemy_point.x += water.MOVE_SPEED;
		}
		else {
			water.point_right = false;
			water.enemy_point.x -= water.MOVE_SPEED;
		}
		//water边界限制
		if (water.enemy_point.x > 900)water.enemy_point.x = 900;
		if (water.enemy_point.x < -200)water.enemy_point.x = -200;
		

		//enemy图像修改
		if (player.HP <= 0) {
			if (player_time <= 10) {
				water.put_take_hit();
			}
			else {
				water.put_idle();
			}
		}
		else if (water.HP <= 0) {
			if (water_time <= 10) {
				water.put_take_hit();
			}
			else {
				water.put_death();
			}
			if ((water_time - 10) / 40 == 16) {
				std::cout << "you are winner" << "\n\n" << "thank your playing\n\n";
				break;
			}

		}
		else if (water.sp_attack) {
			water.put_sp_attack();
		}
		else if (water.surf_ing) {
			water.put_surf();
		}
		else if (water.take_hit_ing) {
			water.put_take_hit();
		}
		else {
			water.put_walk();
		}

		//player数据修改
		if (player.HP <= 0) {
			if (player_time == 0) {
				player.is_move_left = false;
				player.is_move_right = false;
				player.is_j_up = false;
				player.dash_ing = 0;
				if (dif >= 0) {
					player.point_right = false;
				}
				else {
					player.point_right = true;
				}
			}
			if (player_time <= 10) {
				if (dif >= 0) {
					player.enemy_point.x += 25;
				}
				else {
					player.enemy_point.x -= 25;
				}
			}
		}
		else if (water.HP <= 0) {  //water死亡
			if (water_time == 0) {
				player.is_move_left = false;
				player.is_move_right = false;
				player.is_j_up = false;
				player.dash_ing = 0;
				if (dif >= 0) {
					player.point_right = false;
				}
				else {
					player.point_right = true;
				}
			}
			if (water_time <= 10) {
				if (dif >= 0) {
					player.enemy_point.x += 25;
				}
				else {
					player.enemy_point.x -= 25;
				}
			}
		}
		else if (player.take_hit_ing || player.take_hit_ing_serious) {//player受到攻击
			player.dash_ing = 0;
			player.atk_1_ing = 0;
			player.atk_2_ing = 0;
			if (player.take_hit_ing == 6)player.HP--;
			if (player.take_hit_ing_serious == 6)player.HP -= 2;
			if (player.HP < 0)player.HP = 0;
			if (water.surf_ing) {
				if (dif >= 0) {
					player.enemy_point.x += 60;
				}
				else {
					player.enemy_point.x -= 60;
				}
			}
			else {
				if (dif >= 0) {
					player.enemy_point.x += 22;
				}
				else {
					player.enemy_point.x -= 22;
				}
			}
		}
		else if (player.dash_ing && !player.dash_count) {//冲刺
			player.dash_ing--;
			player.atk_1_ing = 0;
			player.atk_2_ing = 0;
			if (player.point_right)player.enemy_point.x += 40;
			else player.enemy_point.x -= 40;
		}
		else {
			//数据修改
			if (player.YSPEED && player.dash_ing)player.dash_count++;

			if (player.is_move_left) player.enemy_point.x -= player.XSPEED;
			if (player.is_move_right) player.enemy_point.x += player.XSPEED;


			if (player.is_j_up && player.height == player.enemy_point.y) {
				player.YSPEED = -27;
				player.enemy_point.y += player.YSPEED;
			}
		}

		//独立的下落数据修改
		if (player.height != player.enemy_point.y) {
			player.YSPEED += player.g;
			player.enemy_point.y += player.YSPEED;
		}
		else if (!player.is_j_up && player.height == player.enemy_point.y) {
			player.YSPEED = 0;
			player.dash_count = 0;
		}




		//player边界限制
		if (player.enemy_point.x < 0)player.enemy_point.x = 0;
		if (player.enemy_point.x > 1280 - 150)player.enemy_point.x = 1280 - 150;


		//player图像渲染
		if (player.HP <= 0) {
			if (player_time <= 10) {
				player.put_take_hit();
			}
			else {
				player.put_death();
			}
			if ((player_time - 10) / 40 == 19) {
				std::cout << "you are dead\n\n" << "thank your playing\n";
				break;
			}
		}
		else if (water.HP <= 0 && water_time <= 10) {
			player.put_take_hit();
		}
		else if (player.take_hit_ing || player.take_hit_ing_serious) {
			player.put_take_hit();
		}
		else if (player.dash_ing) {
			player.put_dash();
			mciSendString(L"play dash from 0", NULL, 0, NULL);
		}
		else if (player.atk_1_ing) {
			player.put_attack_1();
			if (water.take_hit_ing && !player.no_attack_impact1) {
				mciSendString(L"play attack_impact1 from 0", NULL, 0, NULL);
				player.no_attack_impact1 = 7;
			}
			else if (!player.no_attack1 && !player.no_attack_impact1) {
				mciSendString(L"play attack1 from 0", NULL, 0, NULL);
				player.no_attack_impact1 = 7;
			}

		}
		else if (player.atk_2_ing) {
			player.put_attack_2();
			if (water.take_hit_ing && !player.no_attack_impact2) {
				mciSendString(L"play attack_impact2 from 0", NULL, 0, NULL);
				player.no_attack_impact2 = 7;
			}
			else if (!player.no_attack2 && !player.no_attack_impact2) {
				mciSendString(L"play attack2 from 0", NULL, 0, NULL);
				player.no_attack_impact2 = 7;
			}
		}
		else if (player.enemy_point.y != player.height) {
			if (player.YSPEED < 0) {
				player.put_j_up();
			}
			else if (player.YSPEED >= 0) {
				if (player.YSPEED > 15) {
					player.put_land();
				}
				else {
					player.put_j_down();
				}
			}
		}
		else if ((player.is_move_left && player.is_move_right) || (!player.is_move_left && !player.is_move_right)) {
			player.put_idle();
		}
		else {
			player.put_run();
			//脚步声
			if (!player.no_run_sound) {
				mciSendString(L"play run from 0", NULL, 0, NULL);
				player.no_run_sound = 6;
			}
		}


		//player
		if (player.no_dash) {
			player.no_dash--;
		}
		if (player.atk_1_ing) {
			player.atk_1_ing--;
		}
		if (player.atk_2_ing) {
			player.atk_2_ing--;
		}
		if (player.atk_time) {
			player.atk_time--;
		}
		if (player.no_run_sound) {
			player.no_run_sound--;
		}
		if (player.no_attack1) {
			player.no_attack1--;
		}
		if (player.no_attack2) {
			player.no_attack2--;
		}
		if (player.no_attack_impact1) {
			player.no_attack_impact1--;
		}
		if (player.no_attack_impact2) {
			player.no_attack_impact2--;
		}
		if (player.take_hit_ing) {
			player.take_hit_ing--;
		}
		if (player.no_enemy_time) {
			player.no_enemy_time--;
		}
		if (player.take_hit_ing_serious) {
			player.take_hit_ing_serious--;
		}

		if (player.HP <= 0) {
			player_time++;
		}


		//water
		if (water.take_hit_ing) {
			water.take_hit_ing--;
		}
		if (water.surf_ing) {
			water.surf_ing--;
		}
		if (water.sp_attack) {
			if (water.sp_attack == 4) {
				bullet.restart();
			}
			water.sp_attack--;
		}

		if (water.HP <= 0) {
			water_time++;
		}
		
		water.act_time++;


		end_time = GetTickCount64();//获取这一帧结束时间
		unsigned long delta_time = end_time - start_time;

		//计时器，使每一帧的时间是一样的
		if (delta_time < 1000 / 32)
		{
			Sleep(1000 / 32 - delta_time);
		}
		
		FlushBatchDraw();

		start_time = GetTickCount64();//这一帧开始时间
	}
	EndBatchDraw();

	// 关闭音频资源
	mciSendString(L"close music", NULL, 0, NULL);

	return 0;
}
