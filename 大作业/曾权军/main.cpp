#include <iostream>
#include <graphics.h>		         
#include <conio.h>
#include <easyx.h>
#include <Windows.h> 
#include <string>
#include<mmsystem.h>

#define ob_wideth 1680
#define ob_highth 960

#pragma comment(lib, "Winmm.lib")

#pragma comment(lib, "MSIMG32.LIB")



inline void putimage1(int x, int y, IMAGE* img)
{
	int w = img->getwidth();
	int h = img->getheight();
	AlphaBlend(GetImageHDC(NULL), x, y, w, h,
		GetImageHDC(img), 0, 0, w, h, { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

ExMessage msg;
IMAGE ob, start_1, logo, end, end2, decob,dec1,dec2,dec3,environment1, environment2, environment3;
IMAGE lhc_attack1,lhc_attack2,lhc_attack3,lhc_attack4;
IMAGE decide1, decide2,decide22, decide3,decide4, ddecide0;
IMAGE shoot;

void Game1();
void Game2();
void Game3();

int idx = 0;
int idx1 = 0;
int idx2 = 0;
int idx3 = 0;
int idx4 = 0;

const int NUM1 = 6;

const int WALK = 8;

const int SHOOT = 9;

const int DIE = 4;

const int ACT = 10000;

IMAGE lhc_wait[NUM1];

void loadlhc_wait()
{
	for (size_t i = 0; i < NUM1; i++)
	{
		std::wstring path = L"photo/lhc_wait" + std::to_wstring(i) + L".png";
		loadimage(&lhc_wait[i], path.c_str());
	}
}

IMAGE gbl_die[DIE];

void loadgbl_die()
{
	for (size_t i = 0; i < DIE; i++)
	{
		std::wstring path = L"photo/gbl_die" + std::to_wstring(i) + L".png";
		loadimage(&gbl_die[i], path.c_str());
	}
}

IMAGE small_die[NUM1];

void loadsmall_die()
{
	for (size_t i = 0; i < NUM1; i++)
	{
		std::wstring path = L"photo/small_die" + std::to_wstring(i) + L".png";
		loadimage(&small_die[i], path.c_str());
	}
}

IMAGE big_die[WALK];

void loadbig_die()
{
	for (size_t i = 0; i < WALK; i++)
	{
		std::wstring path = L"photo/big_die" + std::to_wstring(i) + L".png";
		loadimage(&big_die[i], path.c_str());
	}
}

IMAGE die[DIE];

void loaddie()
{
	for (size_t i = 0; i < DIE; i++)
	{
		std::wstring path = L"photo/die" + std::to_wstring(i) + L".png";
		loadimage(&die[i], path.c_str());
	}
}

IMAGE lhcgongji[NUM1];

void loadlhc_gongji()
{
	for (size_t i = 0; i < NUM1; i++)
	{
		std::wstring path = L"photo/lhcgongji" + std::to_wstring(i) + L".png";
		loadimage(&lhcgongji[i], path.c_str());
	}
}

IMAGE gbl_attack[NUM1];

void loadgbl_attack()
{
	for (size_t i = 0; i < NUM1; i++)
	{
		std::wstring path = L"photo/gbl_attack" + std::to_wstring(i) + L".png";
		loadimage(&gbl_attack[i], path.c_str());
	}
}

IMAGE small_attack[WALK];

void loadsmall_attack()
{
	for (size_t i = 0; i < WALK; i++)
	{
		std::wstring path = L"photo/small_attack" + std::to_wstring(i) + L".png";
		loadimage(&small_attack[i], path.c_str());
	}
}

IMAGE big_attack[WALK];

void loadbig_attack()
{
	for (size_t i = 0; i < WALK; i++)
	{
		std::wstring path = L"photo/big_attack" + std::to_wstring(i) + L".png";
		loadimage(&big_attack[i], path.c_str());
	}
}

IMAGE big_da[WALK];

void loadbig_da()
{
	for (size_t i = 0; i < WALK; i++)
	{
		std::wstring path = L"photo/big_da" + std::to_wstring(i) + L".png";
		loadimage(&big_da[i], path.c_str());
	}
}

IMAGE gblda[NUM1];

void loadgblda()
{
	for (size_t i = 0; i < NUM1; i++)
	{
		std::wstring path = L"photo/gblda" + std::to_wstring(i) + L".png";
		loadimage(&gblda[i], path.c_str());
	}
}

IMAGE lhc_da[NUM1];

void loadlhc_da()
{
	for (size_t i = 0; i < NUM1; i++)
	{
		std::wstring path = L"photo/lhc_da" + std::to_wstring(i) + L".png";
		loadimage(&lhc_da[i], path.c_str());
	}
}

IMAGE lhc_shoot[SHOOT];

void loadlhc_shoot()
{
	for (size_t i = 0; i < SHOOT; i++)
	{
		std::wstring path = L"photo/lhc_shoot" + std::to_wstring(i) + L".png";
		loadimage(&lhc_shoot[i], path.c_str());
	}
}

IMAGE gbl_wait[NUM1];

void loadgbl_wait()
{
	for (size_t i = 0; i < NUM1; i++)
	{
		std::wstring path = L"photo/gbl_wait" + std::to_wstring(i) + L".png";
		loadimage(&gbl_wait[i], path.c_str());
	}
}

IMAGE small_wait[WALK];

void loadsmall_wait()
{
	for (size_t i = 0; i < WALK; i++)
	{
		std::wstring path = L"photo/small_wait" + std::to_wstring(i) + L".png";
		loadimage(&small_wait[i], path.c_str());
	}
}

IMAGE big_wait[WALK];

void loadbig_wait()
{
	for (size_t i = 0; i < WALK; i++)
	{
		std::wstring path = L"photo/big_wait" + std::to_wstring(i) + L".png";
		loadimage(&big_wait[i], path.c_str());
	}
}

IMAGE gbl_hurt[NUM1];

void loadgbl_hurt()
{
	for (size_t i = 0; i < NUM1; i++)
	{
		std::wstring path = L"photo/gbl_hurt" + std::to_wstring(i) + L".png";
		loadimage(&gbl_hurt[i], path.c_str());
	}
}

IMAGE small_hurt[NUM1];

void loadsmall_hurt()
{
	for (size_t i = 0; i < NUM1; i++)
	{
		std::wstring path = L"photo/small_hurt" + std::to_wstring(i) + L".png";
		loadimage(&small_hurt[i], path.c_str());
	}
}

IMAGE big_hurt[NUM1];

void loadbig_hurt()
{
	for (size_t i = 0; i < NUM1; i++)
	{
		std::wstring path = L"photo/big_hurt" + std::to_wstring(i) + L".png";
		loadimage(&big_hurt[i], path.c_str());
	}
}

IMAGE hurt[NUM1];

void loadhurt()
{
	for (size_t i = 0; i < NUM1; i++)
	{
		std::wstring path = L"photo/hurt" + std::to_wstring(i) + L".png";
		loadimage(&hurt[i], path.c_str());
	}
}

IMAGE lhc_Walk[WALK];

void loadlhc_Walk()
{
	for (size_t i = 0; i < WALK; i++)
	{
		std::wstring path = L"photo/lhc_Walk" + std::to_wstring(i) + L".png";
		loadimage(&lhc_Walk[i], path.c_str());
	}
}

IMAGE gbl_walk[WALK];

void loadgbl_walk()
{
	for (size_t i = 0; i < WALK; i++)
	{
		std::wstring path = L"photo/gbl_walk" + std::to_wstring(i) + L".png";
		loadimage(&gbl_walk[i], path.c_str());
	}
}

IMAGE big_walk[WALK];

void loadbig_walk()
{
	for (size_t i = 0; i < WALK; i++)
	{
		std::wstring path = L"photo/big_walk" + std::to_wstring(i) + L".png";
		loadimage(&big_walk[i], path.c_str());
	}
}

IMAGE big_wwalk[WALK];

void loadbig_wwalk()
{
	for (size_t i = 0; i < WALK; i++)
	{
		std::wstring path = L"photo/big_wwalk" + std::to_wstring(i) + L".png";
		loadimage(&big_wwalk[i], path.c_str());
	}
}

IMAGE small_move[WALK];

void loadgsmall_move()
{
	for (size_t i = 0; i < WALK; i++)
	{
		std::wstring path = L"photo/small_move" + std::to_wstring(i) + L".png";
		loadimage(&small_move[i], path.c_str());
	}
}

IMAGE small_mmove[WALK];

void loadgsmall_mmove()
{
	for (size_t i = 0; i < WALK; i++)
	{
		std::wstring path = L"photo/small_mmove" + std::to_wstring(i) + L".png";
		loadimage(&small_mmove[i], path.c_str());
	}
}

IMAGE lhc_wwalk[WALK];

void loadlhc_wwalk()
{
	for (size_t i = 0; i < WALK; i++)
	{
		std::wstring path = L"photo/lhc_wwalk" + std::to_wstring(i) + L".png";
		loadimage(&lhc_wwalk[i], path.c_str());
	}
}

IMAGE gbl_wwalk[WALK];

void loadgbl_wwalk()
{
	for (size_t i = 0; i < WALK; i++)
	{
		std::wstring path = L"photo/gbl_wwalk" + std::to_wstring(i) + L".png";
		loadimage(&gbl_wwalk[i], path.c_str());
	}
}

class lhc
{
	//构造函数：角色样子
public:
	
	int attack = 250;
	int life = 2500;
	int speed = 100;
}lhc;

class smal1
{
	//构造函数：角色样子
public:

	int attack = 180;
	int life = 1000;
	int speed = 100;
}smal1;

class smal2
{
	//构造函数：角色样子
public:

	int attack = 180;
	int life = 900;
	int speed = 80;
}smal2;

class big
{
	//构造函数：角色样子
public:

	int attack = 80;
	int life = 1200;
	int speed = 120;
}big;

class gbl1
{

public:
	int attack = 70;
	int life = 750;
	int speed =65;
}gbl1;

class gbl2
{

public:
	int attack = 100;
	int life = 800;
	int speed = 80;
}gbl2;


class gbl3
{

public:
	int attack = 80;
	int life = 650;
	int speed = 70;
}gbl3;

void drawtext1()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(30, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(0, 50, L"红唇少年:");
}

void drawtext2()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(30, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(1200, 50, L"哥布林:");
}

void drawtext3()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(30, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(1200, 100, L"哥布林:");
}

void drawtext33()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(30, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(1200, 100, L"火焰法师:");
}

void drawtext333()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(30, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(1200, 100, L"亡灵法师:");
}

void drawtext3333()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(30, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(1200, 50, L"火焰法师:");
}

void drawtext33333()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(30, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(1200, 150, L"火焰法师:");
}

void drawtext4()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(30, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(1200, 150, L"哥布林:");
}

void drawtext5()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(700, 0, L"轮到我方行动");
}

void drawtext6()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(700, 0, L"轮到敌方行动");
}

void drawtext7()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(700, 0, L"你已使用红唇冲击");
}

void drawtext8()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(700, 0, L"你已使用爱心箭");
}

void drawtext9()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(700, 0, L"你已使用大力一坤");
}

void drawtext10()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(600, 0, L"你已降低哥布林1的速度！");
}

void drawtext11()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(600, 0, L"你已降低哥布林2的速度！");
}

void drawtext111()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(600, 0, L"你已降低火焰法师的速度！");
}

void drawtext12()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(600, 0, L"你已降低哥布林3的速度！");
}

void drawtext13()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(600, 0, L"哥布林1的速度已经达到最低");
}

void drawtext14()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(600, 0, L"哥布林2的速度已经达到最低");
}

void drawtext44()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(600, 0, L"火焰法师的速度已经达到最低");
}

void drawtext15()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(600, 0, L"哥布林3的速度已经达到最低");
}

void drawtext16()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(700, 0, L"击杀再现");
}

void drawtext17()
{
	settextcolor(RED);  // 设置文本颜色为红色
	settextstyle(50, 0, L"黑体");  // 设置字体大小为20，字体为宋体
	setbkmode(TRANSPARENT);
	outtextxy(650, 50, L"你已可以释放大招");
}

void Decide()
{
	loadimage(&decob, L"photo/decob.png");
	loadimage(&dec1, L"photo/dec1.png",300,300);
	loadimage(&dec2, L"photo/dec2.png",300,300);
	loadimage(&dec3, L"photo/dec3.png",300,300);
	loadimage(&end2,L"photo/end2.png",100,100);
	
	
	fillrectangle(0, 0, ob_wideth, ob_highth);
	putimage(500, 0, &decob);
	putimage(200, 400, &dec1);
	putimage(700, 400, &dec2);
	putimage(1200, 400, &dec3);
	putimage(1580, 0, &end2);
	bool running = true;

	while (running)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))
		{


			if (msg.message == WM_LBUTTONDOWN)
			{
				int x = msg.x;
				int y = msg.y;
				if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
				{
					MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
					running = false;
				}
				else if (x <= 500 && x >= 200 && y >= 400 && y <= 700)
				{


					Game1();

					

				}
				else if (x <= 1000 && x >= 700 && y >= 400 && y <= 700)
				{
					

					Game2();



				}
				else if (x <= 1500 && x >= 1200 && y >= 400 && y <= 700)
				{
					

					Game3();



				}
			}
		}


		

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 144)
		{
			Sleep(1000 / 144 - delta_time);
		}
	}

	closegraph();
}












void Game1()
{
	

	loadlhc_wait();

	loadgbl_wait();

	loadlhc_Walk();

	loadlhc_wwalk();

	loadlhc_gongji();

	loadgbl_hurt();

	loadimage(&shoot, L"photo/shoot.png");

	loadimage(&lhc_attack1, L"photo/lhc_attack1.png",200,150);

	loadimage(&lhc_attack2, L"photo/lhc_attack2.png", 200, 150);

	loadimage(&lhc_attack3, L"photo/lhc_attack3.png", 200, 150);

	loadimage(&lhc_attack4, L"photo/lhc_attack4.png", 200, 150);

	loadimage(&decide1, L"photo/decide1.png", 200, 150);

	loadimage(&decide2, L"photo/decide2.png", 200, 150);

	loadimage(&decide3, L"photo/decide3.png", 200, 150);

	loadimage(&decide4, L"photo/decide4.png", 600, 150);

	loadimage(&environment1, L"photo/environment1.jpg", ob_wideth, ob_highth);
	
	loadimage(&end2, L"photo/end2.png", 100, 100);

	int n = 0;
	int act = 0;
	int da = 0;
	int lhcx = 200;
	int lhcy = 700;
	int gbl1x = 1220;
	int gbl1y = 600;
	int gbl2x = 1380;
	int gbl2y = 700;
	int gbl3x = 1280;
	int gbl3y = 800;
	int bb = 0;
	int aa = 0;
	int cc = 0;
	int dd = 0;
	int shootx = 300;
	int shooty = 740;
	int life1 = 1;
	int life2 = 1;
	int life3 = 1;
	int life = 1;

	int gg = 0;

	int cnt = 0;

	fillrectangle(0, 0, ob_wideth, ob_highth);

	int lhc_doing = 0;
	int gbl1_doing = 0;
	int gbl2_doing = 0;
	int gbl3_doing = 0;

	int x1 = 0, x2 = 0, x3 = 0;

	int x = 0;


	bool running = true;

	BeginBatchDraw();

	while (running)
	{
		DWORD start_time = GetTickCount();



		if(bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0 && lhc_doing < ACT && gbl1_doing < ACT && gbl2_doing < ACT && gbl3_doing < ACT  )
		{
			lhc_doing += lhc.speed;

			
		}

		if(life1 == 1 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0 && lhc_doing < ACT && gbl1_doing < ACT  && gbl2_doing < ACT && gbl3_doing < ACT )
		{
			gbl1_doing += gbl1.speed;
		}

		if(life2 == 1 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0 && lhc_doing < ACT && gbl1_doing < ACT  && gbl2_doing < ACT && gbl3_doing < ACT )
		{
			gbl2_doing += gbl2.speed;
		}

		if(life3 == 1 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0 && lhc_doing < ACT && gbl1_doing < ACT  && gbl2_doing < ACT && gbl3_doing < ACT )
		{
			gbl3_doing += gbl3.speed;
		}

		if (lhc_doing == gbl1_doing)
		{
			gbl1_doing -= 10;
		}

		if (lhc_doing == gbl2_doing)
		{
			gbl2_doing -= 10;
		}

		if (lhc_doing == gbl3_doing)
		{
			gbl3_doing -= 10;
		}

		if (gbl1_doing == gbl2_doing)
		{
			gbl1_doing -= 10;
		}

		if (gbl1_doing == gbl3_doing)
		{
			gbl1_doing -= 10;
		}

		if (gbl2_doing == gbl3_doing)
		{
			gbl2_doing -= 10;
		}

		while (peekmessage(&msg))
		{


			if (msg.message == WM_LBUTTONDOWN)
			{
				int x = msg.x;
				int y = msg.y;
				if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
				{
					MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
					running = false;
				}
				
			}
		}

		static int counter = 0;
		static int counter1 = 0;
		static int counter2 = 0;
		static int counter3 = 0;
		

		if (++counter % 5 == 0)
		{
			idx++;
			idx1++;
		}

		

		idx = idx % NUM1;
		idx1 = idx1 % WALK;
		

		cleardevice();

		putimage(0, 0, &environment1);

		drawtext1();

		drawtext2();

		drawtext3();

		drawtext4();

		setfillcolor(WHITE);

		fillrectangle(150, 50, 550, 80);

		fillrectangle(1320, 50, 1520, 80);

		fillrectangle(1320, 100, 1520, 130);

		fillrectangle(1320, 150, 1520, 180);

		setfillcolor(RED);

		fillrectangle(550 - x, 50, 550, 80);

		fillrectangle(1520 - x1, 50, 1520, 80);

		fillrectangle(1520 - x2, 100, 1520, 130);

		fillrectangle(1520 - x3, 150, 1520, 180);

		setfillcolor(WHITE);

		putimage(1580, 0, &end2);

		if (life1 ==0 && life2 == 0 && life3 == 0 && aa == 0 && bb == 0 && cc == 0 && dd == 0 && gg == 0)
		{
			MessageBox(GetHWnd(), _T("你已完成第一关！"), _T("恭喜你！"), MB_OK);
			running = false;
		}

		if (life == 0 && gg == 0)
		{
			MessageBox(GetHWnd(), _T("你死了！"), _T("很遗憾"), MB_OK);
			running = false;
		}

		if(bb == 0 && aa == 0 && dd == 0 && gg != 2 && gg != 5 && gg != 8 && life == 1)
			putimage1(200, 700, &lhc_wait[idx]);

		

		if (bb == 4)
		{
			putimage1(lhcx, lhcy, &lhc_Walk[idx1]);
			lhcx += 5;
			if (lhcx == 1120)
			{
				bb = 5;
			}
			if (lhcy >= 600)
			{
				lhcy -= 5;
			}
		}

		if (bb == 5)
		{
	

			putimage1(1120, 600, &lhcgongji[idx2]);

			putimage1(1220, 600, &gbl_hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				bb = 6;
				idx2 = 0;

				x1 += lhc.attack * 200.0 / gbl1.life;

				if (x1 >= 200)
				{
					x1 = 200;

					life1 = 2;

					
				}
			}
		}

		if (bb == 6)
		{
			putimage1(lhcx, lhcy, &lhc_wwalk[idx1]);

			lhcx -= 5;

			

			if (lhcy <= 700)
			{
				lhcy += 5;
			}

			if (lhcx == 200)
			{
				bb = 0;
			}
		}

		if (bb == 1)
		{
			putimage1(lhcx, lhcy, &lhc_Walk[idx1]);
			lhcx += 5;
			if (lhcx == 1280)
			{
				bb = 2;
			}
		}

		if (bb == 2)
		{


			putimage1(1280, 700, &lhcgongji[idx2]);
			
			putimage1(1380, 700, &gbl_hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				bb = 3;
				idx2 = 0;

				x2 += lhc.attack * 200.0 / gbl2.life;

				if (x2 >= 200)
				{
					x2 = 200;
					life2 = 2;
				}
			}
		}

		if (bb == 3)
		{
			putimage1(lhcx, lhcy, &lhc_wwalk[idx1]);

			lhcx -= 5;

			

			if (lhcx == 200)
			{
				bb = 0;
			}
		}

		if (bb == 7)
		{
			putimage1(lhcx, lhcy, &lhc_Walk[idx1]);
			lhcx += 5;
			if (lhcx == 1180)
			{
				bb = 8;
			}
			if (lhcy <= 800)
			{
				lhcy += 5;
			}
		}

		if (bb == 8)
		{


			putimage1(1180, 800, &lhcgongji[idx2]);

			putimage1(1280, 800, &gbl_hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				bb = 9;
				idx2 = 0;

				x3 += lhc.attack * 200.0 / gbl3.life;

				if (x3 >= 200)
				{
					x3 = 200;
					life3 = 2;
				}
			}
		}

		if (bb == 9)
		{
			putimage1(lhcx, lhcy, &lhc_wwalk[idx1]);

			lhcx -= 5;

			

			if (lhcx == 200)
			{
				bb = 0;
			}

			if (lhcy > 700)
			{
				lhcy -= 5;
			}
		}

		if (aa == 1)
		{
			putimage1(200, 700, &lhc_shoot[idx3]);

			if (++counter2 % 10 == 0)
			{
				idx3++;
			}

			idx3 = idx3 % SHOOT;

			if (idx3 == 8)
			{
				aa = 0;
				idx3 = 0;
				cc = 1;
			}
		}

		if (aa == 2)
		{
			putimage1(200, 700, &lhc_shoot[idx3]);

			if (++counter2 % 10 == 0)
			{
				idx3++;
			}

			idx3 = idx3 % SHOOT;

			if (idx3 == 8)
			{
				aa = 0;
				idx3 = 0;
				cc = 3;
			}
		}

		if (aa == 3)
		{
			putimage1(200, 700, &lhc_shoot[idx3]);

			if (++counter2 % 10 == 0)
			{
				idx3++;
			}

			idx3 = idx3 % SHOOT;

			if (idx3 == 8)
			{
				aa = 0;
				idx3 = 0;
				cc = 5;
			}
		}


		if(bb != 2 && cc != 4 && dd != 2 && life2 == 1 && gg != 4 && gg != 5 && gg != 6)
		putimage1(1380, 700, &gbl_wait[idx]);

		if(bb != 5 && cc != 2 && dd != 2 && life1 == 1 && gg != 1 && gg != 2 && gg != 3)
		putimage1(1220, 600, &gbl_wait[idx]);

		if(bb != 8 && cc != 6 && dd != 2 && life3 == 1 && gg != 7 && gg != 8 && gg !=9)
		putimage1(1280, 800, &gbl_wait[idx]);

		if (life == 2 )
		{
			putimage1(200, 700, &die[idx4]);
			

			if (++counter3 % 10 == 0)
			{
				idx4++;
			}

			idx4 = idx4 % DIE;

			if (idx4 == 3)
			{
				life = 0;
				idx4 = 0;
			}
		}

		if (life == 0)
		{
			putimage1(200, 700, &die[3]);
		}

		if (life1 == 2)
		{
			putimage1(1220, 600, &gbl_die[idx4]);
			drawtext16();

			if (++counter3 % 10 == 0)
			{
				idx4++;
			}

			idx4 = idx4 % DIE;

			if (idx4 == 3)
			{
				lhc_doing = ACT;
				life1 = 0;
				idx4 = 0;
				if (cnt < 3)
				{
					cnt++;
				}
			}
		}

		if (life1 == 0)
		{
			putimage1(1220, 600, &gbl_die[3]);
		}

		if (life2 == 2)
		{
			putimage1(1380, 700, &gbl_die[idx4]);
			drawtext16();

			if (++counter3 % 10 == 0)
			{
				idx4++;
			}

			idx4 = idx4 % DIE;

			if (idx4 == 3)
			{

				lhc_doing = ACT;
				life2 = 0;
				idx4 = 0;
				if (cnt < 3)
				{
					cnt++;
				}
			}
		}

		if (life2 == 0)
		{
			putimage1(1380,700, &gbl_die[3]);
		}

		if (life3 == 2)
		{
			putimage1(1280, 800, &gbl_die[idx4]);
			drawtext16();

			if (++counter3 % 10 == 0)
			{
				idx4++;
			}

			idx4 = idx4 % DIE;

			if (idx4 == 3)
			{
				lhc_doing = ACT;
				life3 = 0;
				idx4 = 0;
				if (cnt < 3)
				{
					cnt++;
				}
			}
		}

		if (life3 == 0)
		{
			putimage1(1280, 800, &gbl_die[3]);
		}

		if (cc == 1)
		{
			putimage1(shootx, shooty, &shoot);
			shootx += 10;
			if (shootx == 1200)
			{
				cc = 2;
				shootx = 300;
				shooty = 740;
			}
			if (shooty > 620)
			{
				shooty -= 1;
			}
		}

		if (cc == 2)
		{
			putimage1(1220, 600, &gbl_hurt[idx2]);

			if(gbl1.speed > 10)
			{
				drawtext10();
			}

			if (gbl1.speed == 10)
			{
				drawtext13();
			}

			if (++counter1 % 10 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				cc = 0;
				idx2 = 0;
				if(gbl1.speed > 10)
				{
					gbl1.speed -= 10;
				}
				if (gbl1.speed < 10)
				{
					gbl1.speed = 10;
				}

				x1 += lhc.attack * 0.5 * 200.0 / gbl1.life;

				if (x1 >= 200)
				{
					x1 = 200;
					life1 = 2;
				}
			}
		}

		if (cc == 3)
		{
			putimage1(shootx, shooty, &shoot);
			shootx += 10;
			if (shootx == 1360)
			{
				cc = 4;
				shootx = 300;
				shooty = 740;
			}
			
		}

		if (cc == 4)
		{
			putimage1(1380, 700, &gbl_hurt[idx2]);

			if (gbl2.speed > 10)
			{
				drawtext11();
			}

			if (gbl2.speed == 10)
			{
				drawtext14();
			}

			if (++counter1 % 10 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				cc = 0;
				idx2 = 0;
				if (gbl2.speed > 10)
				{
					gbl2.speed -= 10;
				}
				if (gbl2.speed < 10)
				{
					gbl2.speed = 10;
				}

				x2 += lhc.attack * 0.5 * 200.0 / gbl2.life;

				if (x2 >= 200)
				{
					x2 = 200;
					life2 = 2;
				}
			}
		}

		if (cc == 5)
		{
			putimage1(shootx, shooty, &shoot);
			shootx += 10;
			if (shootx == 1260)
			{
				cc = 6;
				shootx = 300;
				shooty = 740;
			}
			if (shooty < 850)
			{
				shooty += 2;
			}

		}

		if (cc == 6)
		{
			putimage1(1280, 800, &gbl_hurt[idx2]);

			if (gbl3.speed > 10)
			{
				drawtext12();
			}

			if (gbl3.speed == 10)
			{
				drawtext15();
			}

			if (++counter1 % 10 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				cc = 0;
				idx2 = 0;
				if (gbl3.speed > 10)
				{
					gbl3.speed -= 10;
				}
				if (gbl3.speed < 10)
				{
					gbl3.speed = 10;
				}

				x3 += lhc.attack * 0.5 * 200.0 / gbl3.life;

				if (x3 >= 200)
				{
					x3 = 200;
					life3 = 2;
				}
			}
		}

		if (dd == 1)
		{
			putimage1(lhcx, lhcy, &lhc_Walk[idx1]);
			lhcx += 5;
			if (lhcx == 1180)
			{
				dd = 2;
			}
		}

		if (dd == 2)
		{
			putimage1(lhcx, lhcy, &lhc_da[idx2]);

			if(life2 ==1)
			putimage1(1380, 700, &gbl_hurt[idx2]);

			if(life1 ==1)
			putimage1(1220, 600, &gbl_hurt[idx2]);

			if(life3 == 1)
			putimage1(1280, 800, &gbl_hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				dd = 0;
				cnt = 0;
				bb = 3;
				idx2 = 0;

				if(x2 < 200)
				x2 += lhc.attack  * 200.0 / gbl2.life;

				if(x1 < 200)
				x1 += lhc.attack  * 200.0 / gbl1.life;

				if(x3 < 200)
				x3 += lhc.attack  * 200.0 / gbl3.life;

				if (x2 >= 200 && life2 != 0)
				{
					x2 = 200;
					life2 = 2;
				}

				if (x3 >= 200 && life3 != 0)
				{
					x3 = 200;
					life3 = 2;
				}

				if (x1 >= 200 && life1 != 0)
				{
					x1 = 200;
					life1 = 2;
				}
			}
		}

		if (lhc_doing >= ACT && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0 )
		{
			if(act == 0)
			{
				drawtext5();

				putimage(0, 810, &lhc_attack1);

				putimage(200, 810, &lhc_attack2);

				if(cnt < 3)
				putimage(400, 810, &lhc_attack4);

				if(cnt == 3)
				{
					putimage(400, 810, &lhc_attack3);
					drawtext17();
				}
			}

			if (act == 1 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0)
			{
				drawtext7();

				if(life1 != 0)
				putimage(0, 810, &decide1);

				if(life2 != 0)
				putimage(200, 810, &decide2);

				if(life3 != 0)
				putimage(400, 810, &decide3);

				while (peekmessage(&msg))
				{


					if (msg.message == WM_LBUTTONDOWN)
					{
						int x = msg.x;
						int y = msg.y;
						if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
						{
							MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
							running = false;
						}

						if (x <= 200 && x >= 0 && y >= 810 && y <= 960 && life1 != 0)
						{
							bb = 4;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1320 && x >= 1220 && y >= 600 && y <= 700 && life1 != 0)
						{
							bb = 4;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 400 && x >= 200 && y >= 810 && y <= 960 && life2 != 0)
						{

							bb = 1;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1480 && x >= 1380 && y >= 700 && y <= 800 && life2 != 0)
						{

							bb = 1;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 600 && x >= 400 && y >= 810 && y <= 960 && life3 != 0)
						{
							bb = 7;

							lhc_doing -= ACT;

							act = 0;
						}

						if (x <= 1380 && x >= 1280 && y >= 800 && y <= 900 && life3 != 0)
						{
							bb = 7;

							lhc_doing -= ACT;

							act = 0;
						}
					}
				}
			}

			if (act == 2 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0)
			{
				drawtext8();

				if(life1 != 0)
				putimage(0, 810, &decide1);

				if(life2 != 0)
				putimage(200, 810, &decide2);

				if(life3 != 0)
				putimage(400, 810, &decide3);

				while (peekmessage(&msg))
				{


					if (msg.message == WM_LBUTTONDOWN)
					{
						int x = msg.x;
						int y = msg.y;
						if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
						{
							MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
							running = false;
						}

						if (x <= 200 && x >= 0 && y >= 810 && y <= 960 && life1 != 0)
						{
							aa = 1;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1320 && x >= 1220 && y >= 600 && y <= 700 && life1 != 0)
						{
							aa = 1;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 400 && x >= 200 && y >= 810 && y <= 960 && life2 != 0)
						{
							aa = 2;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1480 && x >= 1380 && y >= 700 && y <= 800 && life2 != 0)
						{
							aa = 2;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 600 && x >=400 && y >= 810 && y <= 960 && life3 != 0)
						{
							aa = 3;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1380 && x >= 1280 && y >= 800 && y <= 900 && life3 != 0)
						{
							aa = 3;

							lhc_doing -= ACT;

							act = 0;

						}
					}
				}
			}

			if (act == 3 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0)
			{
				drawtext9();

				putimage(0, 810, &decide4);
				

				while (peekmessage(&msg))
				{


					if (msg.message == WM_LBUTTONDOWN)
					{
						int x = msg.x;
						int y = msg.y;
						if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
						{
							MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
							running = false;
						}

						if (x <= 600 && x >= 0 && y >= 810 && y <= 960)
						{
							dd = 1;

							lhc_doing -= ACT;

							act = 0;

						}

						
					}
				}
			}



			while (peekmessage(&msg))
			{


				if (msg.message == WM_LBUTTONDOWN)
				{
					int x = msg.x;
					int y = msg.y;
					if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
					{
						MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
						running = false;
					}

					if (x <= 200 && x >= 0 && y >= 810 && y <=960)
					{
						act = 1;
						/*lhc_doing -= ACT;*/
						if (cnt < 3)
						{
							cnt++;
						}
						
					}

					if (x <= 400 && x >= 200 && y >= 810 && y <= 960)
					{
						act = 2;
						/*lhc_doing -= ACT;*/
						if (cnt < 3)
						{
							cnt++;
						}

					}

					if (x <= 600 && x >= 400 && y >= 810 && y <= 960 && cnt == 3)
					{
						act = 3;
						/*lhc_doing -= ACT;*/

					}
				}
			}

			/*lhc.speed -= lhc.speed;

			gbl1_doing -= gbl1.speed;

			gbl2_doing -= gbl2.speed;

			gbl3_doing -= gbl3.speed;*/

		}


		if (gbl1_doing >= ACT && dd == 0 && bb == 0 && aa == 0 && cc == 0 && life1 == 1 && gg == 0)
		{
			
			
			gg = 1;

			gbl1_doing -= ACT;

			while (peekmessage(&msg))
			{


				if (msg.message == WM_LBUTTONDOWN)
				{
					int x = msg.x;
					int y = msg.y;
					if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
					{
						MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
						running = false;
					}

				}
			}


		}

		if (gg == 1)
		{
			putimage1(gbl1x, gbl1y, &gbl_walk[idx1]);

			drawtext6();

			gbl1x -= 5;
			if (gbl1x == 300)
			{
				gg = 2;
			}
			if (gbl1y <= 700)
			{
				gbl1y += 5;
			}
		}

		if (gg == 2)
		{
			putimage1(300, 700, &gbl_attack[idx2]);

			putimage1(200, 700, &hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				gg = 3;
				idx2 = 0;

				x += gbl1.attack * 400.0 / lhc.life;

				if (x >= 400)
				{
					x = 400;

					life = 2;


				}
			}
		}

		if (gg == 3)
		{
			putimage1(gbl1x, gbl1y, &gbl_wwalk[idx1]);

			gbl1x += 5;



			if (gbl1y >= 600)
			{
				gbl1y -= 5;
			}

			if (gbl1x == 1220)
			{
				gg  = 0;
			}
		}


		if (gbl2_doing >= ACT && dd == 0 && bb == 0 && aa == 0 && cc == 0 && life2 == 1 && gg == 0)
		{


			gg = 4;

			gbl2_doing -= ACT;

			while (peekmessage(&msg))
			{


				if (msg.message == WM_LBUTTONDOWN)
				{
					int x = msg.x;
					int y = msg.y;
					if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
					{
						MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
						running = false;
					}

				}
			}


		}

		if (gg == 4)
		{
			putimage1(gbl2x, gbl2y, &gbl_walk[idx1]);

			drawtext6();

			gbl2x -= 5;
			if (gbl2x == 300)
			{
				gg = 5;
			}
			
		}

		if (gg == 5)
		{
			putimage1(300, 650, &gblda[idx2]);

			putimage1(200, 700, &hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				gg = 6;
				idx2 = 0;

				x += gbl2.attack * 400.0 / lhc.life;

				if (x >= 400)
				{
					x = 400;

					life = 2;


				}
			}
		}

		if (gg == 6)
		{
			putimage1(gbl2x, gbl2y, &gbl_wwalk[idx1]);

			gbl2x += 5;



			

			if (gbl2x == 1380)
			{
				gg = 0;
			}
		}


		if (gbl3_doing >= ACT && dd == 0 && bb == 0 && aa == 0 && cc == 0 && life3 == 1 && gg == 0)
		{


			gg = 7;

			gbl3_doing -= ACT;

			while (peekmessage(&msg))
			{


				if (msg.message == WM_LBUTTONDOWN)
				{
					int x = msg.x;
					int y = msg.y;
					if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
					{
						MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
						running = false;
					}

				}
			}


		}

		if (gg == 7)
		{
			putimage1(gbl3x, gbl3y, &gbl_walk[idx1]);

			drawtext6();

			gbl3x -= 5;
			if (gbl3x == 300)
			{
				gg = 8;
			}
			if (gbl3y >= 700)
			{
				gbl3y -= 5;
			}
		}

		if (gg == 8)
		{
			putimage1(300, 700, &gbl_attack[idx2]);

			putimage1(200, 700, &hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				gg = 9;
				idx2 = 0;

				x += gbl3.attack * 400.0 / lhc.life;

				if (x >= 400)
				{
					x = 400;

					life = 2;


				}
			}
		}

		if (gg == 9)
		{
			putimage1(gbl3x, gbl3y, &gbl_wwalk[idx1]);

			gbl3x += 5;



			if (gbl3y <= 800)
			{
				gbl3y += 5;
			}

			if (gbl3x == 1280)
			{
				gg = 0;
			}
		}

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 144)
		{
			Sleep(1000 / 144 - delta_time);
		}
	}

	EndBatchDraw();

	closegraph();
}


















void Game2()
{


	loadlhc_wait();

	loadgbl_wait();

	loadlhc_Walk();

	loadlhc_wwalk();

	loadlhc_gongji();

	loadgbl_hurt();

	loadimage(&shoot, L"photo/shoot.png");

	loadimage(&lhc_attack1, L"photo/lhc_attack1.png", 200, 150);

	loadimage(&lhc_attack2, L"photo/lhc_attack2.png", 200, 150);

	loadimage(&lhc_attack3, L"photo/lhc_attack3.png", 200, 150);

	loadimage(&lhc_attack4, L"photo/lhc_attack4.png", 200, 150);

	loadimage(&decide1, L"photo/decide1.png", 200, 150);

	loadimage(&decide2, L"photo/decide2.png", 200, 150);

	loadimage(&decide22, L"photo/decide22.png", 200, 150);

	loadimage(&decide3, L"photo/decide3.png", 200, 150);

	loadimage(&decide4, L"photo/decide4.png", 600, 150);

	loadimage(&environment1, L"photo/environment2.jpg", ob_wideth, ob_highth);

	loadimage(&end2, L"photo/end2.png", 100, 100);

	int n = 0;
	int act = 0;
	int da = 0;
	int lhcx = 200;
	int lhcy = 700;
	int gbl1x = 1020;
	int gbl1y = 600;
	int smallx = 1380;
	int smally = 600;
	int gbl3x = 1180;
	int gbl3y = 800;
	int bb = 0;
	int aa = 0;
	int cc = 0;
	int dd = 0;
	int shootx = 300;
	int shooty = 740;
	int life1 = 1;
	int life2 = 1;
	int life3 = 1;
	int life = 1;

	int gg = 0;

	int cnt = 0;

	fillrectangle(0, 0, ob_wideth, ob_highth);

	int lhc_doing = 0;
	int gbl1_doing = 0;
	int small_doing = 0;
	int gbl3_doing = 0;

	int x1 = 0, x2 = 0, x3 = 0;

	int x = 0;


	bool running = true;

	BeginBatchDraw();

	while (running)
	{
		DWORD start_time = GetTickCount();



		if (bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0 && lhc_doing < ACT && gbl1_doing < ACT && small_doing < ACT && gbl3_doing < ACT)
		{
			lhc_doing += lhc.speed;


		}

		if (life1 == 1 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0 && lhc_doing < ACT && gbl1_doing < ACT && small_doing < ACT && gbl3_doing < ACT)
		{
			gbl1_doing += gbl1.speed;
		}

		if (life2 == 1 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0 && lhc_doing < ACT && gbl1_doing < ACT && small_doing < ACT && gbl3_doing < ACT)
		{
			small_doing += smal1.speed;
		}

		if (life3 == 1 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0 && lhc_doing < ACT && gbl1_doing < ACT && small_doing < ACT && gbl3_doing < ACT)
		{
			gbl3_doing += gbl3.speed;
		}

		if (lhc_doing == gbl1_doing)
		{
			gbl1_doing -= 10;
		}

		if (lhc_doing == small_doing)
		{
			small_doing -= 10;
		}

		if (lhc_doing == gbl3_doing)
		{
			gbl3_doing -= 10;
		}

		if (gbl1_doing == small_doing)
		{
			gbl1_doing -= 10;
		}

		if (gbl1_doing == gbl3_doing)
		{
			gbl1_doing -= 10;
		}

		if (small_doing == gbl3_doing)
		{
			small_doing -= 10;
		}

		while (peekmessage(&msg))
		{


			if (msg.message == WM_LBUTTONDOWN)
			{
				int x = msg.x;
				int y = msg.y;
				if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
				{
					MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
					running = false;
				}

			}
		}

		static int counter = 0;
		static int counter1 = 0;
		static int counter2 = 0;
		static int counter3 = 0;
		static int counter4 = 0;


		if (++counter % 5 == 0)
		{
			idx++;
			idx1++;
		}



		idx = idx % NUM1;
		idx1 = idx1 % WALK;


		cleardevice();

		putimage(0, 0, &environment1);

		drawtext1();

		drawtext2();

		drawtext33();

		drawtext4();

		setfillcolor(WHITE);

		fillrectangle(150, 50, 550, 80);

		fillrectangle(1320, 50, 1520, 80);

		fillrectangle(1320, 100, 1620, 130);

		fillrectangle(1320, 150, 1520, 180);

		setfillcolor(RED);

		fillrectangle(550 - x, 50, 550, 80);

		fillrectangle(1520 - x1, 50, 1520, 80);

		fillrectangle(1620 - x2, 100, 1620, 130);

		fillrectangle(1520 - x3, 150, 1520, 180);

		setfillcolor(WHITE);

		putimage(1580, 0, &end2);

		if (life1 == 0 && life2 == 0 && life3 == 0 && aa == 0 && bb == 0 && cc == 0 && dd == 0 && gg == 0)
		{
			MessageBox(GetHWnd(), _T("你已完成第一关！"), _T("恭喜你！"), MB_OK);
			running = false;
		}

		if (life == 0 && gg == 0)
		{
			MessageBox(GetHWnd(), _T("你死了！"), _T("很遗憾"), MB_OK);
			running = false;
		}

		if (bb == 0 && aa == 0 && dd == 0 && gg != 2 && gg != 5 && gg != 8 && life == 1)
			putimage1(200, 700, &lhc_wait[idx]);



		if (bb == 4)
		{
			putimage1(lhcx, lhcy, &lhc_Walk[idx1]);
			lhcx += 5;
			if (lhcx == 920)
			{
				bb = 5;
			}
			if (lhcy >= 600)
			{
				lhcy -= 5;
			}
		}

		if (bb == 5)
		{


			putimage1(920, 600, &lhcgongji[idx2]);

			putimage1(1020, 600, &gbl_hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				bb = 6;
				idx2 = 0;

				x1 += lhc.attack * 200.0 / gbl1.life;

				if (x1 >= 200)
				{
					x1 = 200;

					life1 = 2;


				}
			}
		}

		if (bb == 6)
		{
			putimage1(lhcx, lhcy, &lhc_wwalk[idx1]);

			lhcx -= 5;



			if (lhcy <= 700)
			{
				lhcy += 5;
			}

			if (lhcx == 200)
			{
				bb = 0;
			}
		}

		if (bb == 1)
		{
			putimage1(lhcx, lhcy, &lhc_Walk[idx1]);
			lhcx += 5;
			if (lhcx == 1280)
			{
				bb = 2;
			}
			
		}

		if (bb == 2)
		{


			putimage1(1280, 700, &lhcgongji[idx2]);

			putimage1(1380, 650, &small_hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				bb = 3;
				idx2 = 0;

				x2 += lhc.attack * 300.0 / smal1.life;

				if (x2 >= 300)
				{
					x2 = 300;
					life2 = 2;
				}
			}
		}

		if (bb == 3)
		{
			putimage1(lhcx, lhcy, &lhc_wwalk[idx1]);

			lhcx -= 5;



			if (lhcx == 200)
			{
				bb = 0;
			}
		}

		if (bb == 7)
		{
			putimage1(lhcx, lhcy, &lhc_Walk[idx1]);
			lhcx += 5;
			if (lhcx == 1080)
			{
				bb = 8;
			}
			if (lhcy <= 800)
			{
				lhcy += 5;
			}
		}

		if (bb == 8)
		{


			putimage1(1080, 800, &lhcgongji[idx2]);

			putimage1(1180, 800, &gbl_hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				bb = 9;
				idx2 = 0;

				x3 += lhc.attack * 200.0 / gbl3.life;

				if (x3 >= 200)
				{
					x3 = 200;
					life3 = 2;
				}
			}
		}

		if (bb == 9)
		{
			putimage1(lhcx, lhcy, &lhc_wwalk[idx1]);

			lhcx -= 5;



			if (lhcx == 200)
			{
				bb = 0;
			}

			if (lhcy > 700)
			{
				lhcy -= 5;
			}
		}

		if (aa == 1)
		{
			putimage1(200, 700, &lhc_shoot[idx3]);

			if (++counter2 % 10 == 0)
			{
				idx3++;
			}

			idx3 = idx3 % SHOOT;

			if (idx3 == 8)
			{
				aa = 0;
				idx3 = 0;
				cc = 1;
			}
		}

		if (aa == 2)
		{
			putimage1(200, 700, &lhc_shoot[idx3]);

			if (++counter2 % 10 == 0)
			{
				idx3++;
			}

			idx3 = idx3 % SHOOT;

			if (idx3 == 8)
			{
				aa = 0;
				idx3 = 0;
				cc = 3;
			}
		}

		if (aa == 3)
		{
			putimage1(200, 700, &lhc_shoot[idx3]);

			if (++counter2 % 10 == 0)
			{
				idx3++;
			}

			idx3 = idx3 % SHOOT;

			if (idx3 == 8)
			{
				aa = 0;
				idx3 = 0;
				cc = 5;
			}
		}


		if (bb != 2 && cc != 4 && dd != 2 && life2 == 1 && gg != 4 && gg != 5 && gg != 6)
			putimage1(1380, 650, &small_wait[idx1]);

		if (bb != 5 && cc != 2 && dd != 2 && life1 == 1 && gg != 1 && gg != 2 && gg != 3)
			putimage1(1020, 600, &gbl_wait[idx]);

		if (bb != 8 && cc != 6 && dd != 2 && life3 == 1 && gg != 7 && gg != 8 && gg != 9)
			putimage1(1180, 800, &gbl_wait[idx]);

		if (life == 2)
		{
			putimage1(200, 700, &die[idx4]);


			if (++counter3 % 10 == 0)
			{
				idx4++;
			}

			idx4 = idx4 % DIE;

			if (idx4 == 3)
			{
				life = 0;
				idx4 = 0;
			}
		}

		if (life == 0)
		{
			putimage1(200, 700, &die[3]);
		}

		if (life1 == 2)
		{
			putimage1(1020, 600, &gbl_die[idx4]);
			drawtext16();

			if (++counter3 % 10 == 0)
			{
				idx4++;
			}

			idx4 = idx4 % DIE;

			if (idx4 == 3)
			{
				lhc.attack += 100;
				lhc_doing = ACT;
				life1 = 0;
				idx4 = 0;
				if (cnt < 3)
				{
					cnt++;
				}
			}
		}

		if (life1 == 0)
		{
			putimage1(1020, 600, &gbl_die[3]);
		}

		if (life2 == 2)
		{
			putimage1(1380, 650, &small_die[idx4]);
			drawtext16();

			if (++counter3 % 10 == 0)
			{
				idx4++;
			}

			idx4 = idx4 % NUM1;

			if (idx4 == 5)
			{
				lhc.attack += 100;
				lhc_doing = ACT;
				life2 = 0;
				idx4 = 0;
				if (cnt < 3)
				{
					cnt++;
				}
			}
		}

		if (life2 == 0)
		{
			putimage1(1380, 650, &small_die[5]);
		}

		if (life3 == 2)
		{
			putimage1(1180, 800, &gbl_die[idx4]);
			drawtext16();

			if (++counter3 % 10 == 0)
			{
				idx4++;
			}

			idx4 = idx4 % DIE;

			if (idx4 == 3)
			{
				lhc.attack += 100;
				lhc_doing = ACT;
				life3 = 0;
				idx4 = 0;
				if (cnt < 3)
				{
					cnt++;
				}
			}
		}

		if (life3 == 0)
		{
			putimage1(1180, 800, &gbl_die[3]);
		}

		if (cc == 1)
		{
			putimage1(shootx, shooty, &shoot);
			if(shootx < 1000)
			shootx += 10;
			if (shootx >= 1000)
			{
				cc = 2;
				shootx = 300;
				shooty = 740;
			}
			if (shooty > 620)
			{
				shooty -= 1;
			}
		}

		if (cc == 2)
		{
			putimage1(1020, 600, &gbl_hurt[idx2]);

			if (gbl1.speed > 10)
			{
				drawtext10();
			}

			if (gbl1.speed == 10)
			{
				drawtext13();
			}

			if (++counter1 % 10 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				cc = 0;
				idx2 = 0;
				if (gbl1.speed > 10)
				{
					gbl1.speed -= 10;
				}
				if (gbl1.speed < 10)
				{
					gbl1.speed = 10;
				}

				x1 += lhc.attack * 0.5 * 200.0 / gbl1.life;

				if (x1 >= 200)
				{
					x1 = 200;
					life1 = 2;
				}
			}
		}

		if (cc == 3)
		{
			putimage1(shootx, shooty, &shoot);
			if (shooty > 690)
				shooty -= 1;
			if(shootx < 1360)
			shootx += 10;
			if (shootx >= 1360)
			{
				cc = 4;
				shootx = 300;
				shooty = 740;
			}

		}

		if (cc == 4)
		{
			putimage1(1380, 650, &small_hurt[idx2]);

			if (smal1.speed > 10)
			{
				drawtext111();
			}

			if (smal1.speed == 10)
			{
				drawtext44();
			}

			if (++counter1 % 10 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				cc = 0;
				idx2 = 0;
				if (smal1.speed > 10)
				{
					smal1.speed -= 10;
				}
				if (smal1.speed < 10)
				{
					smal1.speed = 10;
				}

				x2 += lhc.attack * 0.5 * 300.0 / smal1.life;

				if (x2 >= 300)
				{
					x2 = 300;
					life2 = 2;
				}
			}
		}

		if (cc == 5)
		{
			putimage1(shootx, shooty, &shoot);
			if(shootx < 1160)
			shootx += 10;
			if (shootx >= 1160)
			{
				cc = 6;
				shootx = 300;
				shooty = 740;
			}
			if (shooty < 850)
			{
				shooty += 2;
			}

		}

		if (cc == 6)
		{
			putimage1(1180, 800, &gbl_hurt[idx2]);

			if (gbl3.speed > 10)
			{
				drawtext12();
			}

			if (gbl3.speed == 10)
			{
				drawtext15();
			}

			if (++counter1 % 10 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				cc = 0;
				idx2 = 0;
				if (gbl3.speed > 10)
				{
					gbl3.speed -= 10;
				}
				if (gbl3.speed < 10)
				{
					gbl3.speed = 10;
				}

				x3 += lhc.attack * 0.5 * 200.0 / gbl3.life;

				if (x3 >= 200)
				{
					x3 = 200;
					life3 = 2;
				}
			}
		}

		if (dd == 1)
		{
			putimage1(lhcx, lhcy, &lhc_Walk[idx1]);
			lhcx += 5;
			if (lhcx == 1080)
			{
				dd = 2;
			}
		}

		if (dd == 2)
		{
			putimage1(lhcx, lhcy, &lhc_da[idx2]);

			if (life2 == 1)
				putimage1(1380, 650, &small_hurt[idx2]);

			if (life1 == 1)
				putimage1(1020, 600, &gbl_hurt[idx2]);

			if (life3 == 1)
				putimage1(1180, 800, &gbl_hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				dd = 0;
				cnt = 0;
				bb = 3;
				idx2 = 0;

				if (x2 < 300)
					x2 += lhc.attack * 300.0 / smal1.life;

				if (x1 < 200)
					x1 += lhc.attack * 200.0 / gbl1.life;

				if (x3 < 200)
					x3 += lhc.attack * 200.0 / gbl3.life;

				if (x2 >= 300 && life2 != 0)
				{
					x2 = 300;
					life2 = 2;
				}

				if (x3 >= 200 && life3 != 0)
				{
					x3 = 200;
					life3 = 2;
				}

				if (x1 >= 200 && life1 != 0)
				{
					x1 = 200;
					life1 = 2;
				}
			}
		}

		if (lhc_doing >= ACT && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0)
		{
			if (act == 0)
			{
				drawtext5();

				putimage(0, 810, &lhc_attack1);

				putimage(200, 810, &lhc_attack2);

				if (cnt < 3)
					putimage(400, 810, &lhc_attack4);

				if (cnt == 3)
				{
					putimage(400, 810, &lhc_attack3);
					drawtext17();
				}
			}

			if (act == 1 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0)
			{
				drawtext7();

				if (life1 != 0)
					putimage(0, 810, &decide1);

				if (life2 != 0)
					putimage(200, 810, &decide22);

				if (life3 != 0)
					putimage(400, 810, &decide3);

				while (peekmessage(&msg))
				{


					if (msg.message == WM_LBUTTONDOWN)
					{
						int x = msg.x;
						int y = msg.y;
						if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
						{
							MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
							running = false;
						}

						if (x <= 200 && x >= 0 && y >= 810 && y <= 960 && life1 != 0)
						{
							bb = 4;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1120 && x >= 1020 && y >= 600 && y <= 700 && life1 != 0)
						{
							bb = 4;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 400 && x >= 200 && y >= 810 && y <= 960 && life2 != 0)
						{

							bb = 1;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1530 && x >= 1380 && y >= 650 && y <= 800 && life2 != 0)
						{

							bb = 1;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 600 && x >= 400 && y >= 810 && y <= 960 && life3 != 0)
						{
							bb = 7;

							lhc_doing -= ACT;

							act = 0;
						}

						if (x <= 1280 && x >= 1180 && y >= 800 && y <= 900 && life3 != 0)
						{
							bb = 7;

							lhc_doing -= ACT;

							act = 0;
						}
					}
				}
			}

			if (act == 2 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0)
			{
				drawtext8();

				if (life1 != 0)
					putimage(0, 810, &decide1);

				if (life2 != 0)
					putimage(200, 810, &decide22);

				if (life3 != 0)
					putimage(400, 810, &decide3);

				while (peekmessage(&msg))
				{


					if (msg.message == WM_LBUTTONDOWN)
					{
						int x = msg.x;
						int y = msg.y;
						if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
						{
							MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
							running = false;
						}

						if (x <= 200 && x >= 0 && y >= 810 && y <= 960 && life1 != 0)
						{
							aa = 1;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1120 && x >= 1020 && y >= 600 && y <= 700 && life1 != 0)
						{
							aa = 1;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 400 && x >= 200 && y >= 810 && y <= 960 && life2 != 0)
						{
							aa = 2;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1530 && x >= 1380 && y >= 650 && y <= 800 && life2 != 0)
						{
							aa = 2;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 600 && x >= 400 && y >= 810 && y <= 960 && life3 != 0)
						{
							aa = 3;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1280 && x >= 1180 && y >= 800 && y <= 900 && life3 != 0)
						{
							aa = 3;

							lhc_doing -= ACT;

							act = 0;

						}
					}
				}
			}

			if (act == 3 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0)
			{
				drawtext9();

				putimage(0, 810, &decide4);


				while (peekmessage(&msg))
				{


					if (msg.message == WM_LBUTTONDOWN)
					{
						int x = msg.x;
						int y = msg.y;
						if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
						{
							MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
							running = false;
						}

						if (x <= 600 && x >= 0 && y >= 810 && y <= 960)
						{
							dd = 1;

							lhc_doing -= ACT;

							act = 0;

						}


					}
				}
			}



			while (peekmessage(&msg))
			{


				if (msg.message == WM_LBUTTONDOWN)
				{
					int x = msg.x;
					int y = msg.y;
					if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
					{
						MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
						running = false;
					}

					if (x <= 200 && x >= 0 && y >= 810 && y <= 960)
					{
						act = 1;
						/*lhc_doing -= ACT;*/
						if (cnt < 3)
						{
							cnt++;
						}

					}

					if (x <= 400 && x >= 200 && y >= 810 && y <= 960)
					{
						act = 2;
						/*lhc_doing -= ACT;*/
						if (cnt < 3)
						{
							cnt++;
						}

					}

					if (x <= 600 && x >= 400 && y >= 810 && y <= 960 && cnt == 3)
					{
						act = 3;
						/*lhc_doing -= ACT;*/

					}
				}
			}

			/*lhc.speed -= lhc.speed;

			gbl1_doing -= gbl1.speed;

			gbl2_doing -= gbl2.speed;

			gbl3_doing -= gbl3.speed;*/

		}


		if (gbl1_doing >= ACT && dd == 0 && bb == 0 && aa == 0 && cc == 0 && life1 == 1 && gg == 0)
		{


			gg = 1;

			gbl1_doing -= ACT;

			while (peekmessage(&msg))
			{


				if (msg.message == WM_LBUTTONDOWN)
				{
					int x = msg.x;
					int y = msg.y;
					if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
					{
						MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
						running = false;
					}

				}
			}


		}

		if (gg == 1)
		{
			putimage1(gbl1x, gbl1y, &gbl_walk[idx1]);

			drawtext6();

			gbl1x -= 5;
			if (gbl1x == 300)
			{
				gg = 2;
			}
			if (gbl1y <= 700)
			{
				gbl1y += 5;
			}
		}

		if (gg == 2)
		{
			putimage1(300, 700, &gbl_attack[idx2]);

			putimage1(200, 700, &hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				gg = 3;
				idx2 = 0;

				x += gbl1.attack * 400.0 / lhc.life;

				if (x >= 400)
				{
					x = 400;

					life = 2;


				}
			}
		}

		if (gg == 3)
		{
			putimage1(gbl1x, gbl1y, &gbl_wwalk[idx1]);

			gbl1x += 5;



			if (gbl1y >= 600)
			{
				gbl1y -= 5;
			}

			if (gbl1x == 1020)
			{
				gg = 0;
			}
		}


		if (small_doing >= ACT && dd == 0 && bb == 0 && aa == 0 && cc == 0 && life2 == 1 && gg == 0)
		{


			gg = 4;

			small_doing -= ACT;

			while (peekmessage(&msg))
			{


				if (msg.message == WM_LBUTTONDOWN)
				{
					int x = msg.x;
					int y = msg.y;
					if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
					{
						MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
						running = false;
					}

				}
			}


		}

		if (gg == 4)
		{
			putimage1(smallx, smally, &small_move[idx1]);

			drawtext6();

			smallx -= 5;
			if (smallx == 300)
			{
				gg = 5;
			}

		}

		if (gg == 5)
		{
			putimage1(300, 650, &small_attack[idx3]);

			putimage1(200, 700, &hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
				idx3++;
			}

			idx2 = idx2 % NUM1;
			idx3 = idx3 % WALK;

			if (idx3 == 7)
			{
				gg = 6;
				idx2 = 0;
				idx3 = 0;

				x += smal1.attack * 400.0 / lhc.life;

				if (x >= 400)
				{
					x = 400;

					life = 2;


				}
			}
		}

		if (gg == 6)
		{
			putimage1(smallx, smally, &small_mmove[idx1]);

			smallx += 5;





			if (smallx == 1380)
			{
				gg = 0;
			}
		}


		if (gbl3_doing >= ACT && dd == 0 && bb == 0 && aa == 0 && cc == 0 && life3 == 1 && gg == 0)
		{


			gg = 7;

			gbl3_doing -= ACT;

			while (peekmessage(&msg))
			{


				if (msg.message == WM_LBUTTONDOWN)
				{
					int x = msg.x;
					int y = msg.y;
					if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
					{
						MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
						running = false;
					}

				}
			}


		}

		if (gg == 7)
		{
			putimage1(gbl3x, gbl3y, &gbl_walk[idx1]);

			drawtext6();

			gbl3x -= 5;
			if (gbl3x == 300)
			{
				gg = 8;
			}
			if (gbl3y >= 700)
			{
				gbl3y -= 5;
			}
		}

		if (gg == 8)
		{
			putimage1(300, 700, &gbl_attack[idx2]);

			putimage1(200, 700, &hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				gg = 9;
				idx2 = 0;

				x += gbl3.attack * 400.0 / lhc.life;

				if (x >= 400)
				{
					x = 400;

					life = 2;


				}
			}
		}

		if (gg == 9)
		{
			putimage1(gbl3x, gbl3y, &gbl_wwalk[idx1]);

			gbl3x += 5;



			if (gbl3y <= 800)
			{
				gbl3y += 5;
			}

			if (gbl3x == 1180)
			{
				gg = 0;
			}
		}

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 144)
		{
			Sleep(1000 / 144 - delta_time);
		}
	}

	EndBatchDraw();

	closegraph();
}


















void Game3()
{
	


	loadlhc_wait();

	loadgbl_wait();

	loadlhc_Walk();

	loadlhc_wwalk();

	loadlhc_gongji();

	loadgbl_hurt();

	loadimage(&shoot, L"photo/shoot.png");

	loadimage(&lhc_attack1, L"photo/lhc_attack1.png", 200, 150);

	loadimage(&lhc_attack2, L"photo/lhc_attack2.png", 200, 150);

	loadimage(&lhc_attack3, L"photo/lhc_attack3.png", 200, 150);

	loadimage(&lhc_attack4, L"photo/lhc_attack4.png", 200, 150);

	loadimage(&decide1, L"photo/decide22.png", 200, 150);

	loadimage(&decide2, L"photo/decide0.png", 200, 150);

	loadimage(&decide3, L"photo/decide22.png", 200, 150);

	loadimage(&decide4, L"photo/decide4.png", 600, 150);

	loadimage(&environment1, L"photo/environment3.jpg", ob_wideth, ob_highth);

	loadimage(&end2, L"photo/end2.png", 100, 100);

	int n = 0;
	int act = 0;
	int da = 0;
	int lhcx = 200;
	int lhcy = 700;
	int small1x = 1020;
	int small1y = 550;
	int bigx = 1380;
	int bigy = 550;
	int small2x = 1180;
	int small2y = 750;
	int bb = 0;
	int aa = 0;
	int cc = 0;
	int dd = 0;
	int shootx = 300;
	int shooty = 740;
	int life1 = 1;
	int life2 = 1;
	int life3 = 1;
	int life = 1;
	int bi = 0;

	int gg = 0;

	int cnt = 0;

	fillrectangle(0, 0, ob_wideth, ob_highth);

	int lhc_doing = 0;
	int small1_doing = 0;
	int small2_doing = 0;
	int big_doing = 0;

	int x1 = 0, x2 = 0, x3 = 0;

	int x = 0;


	bool running = true;

	BeginBatchDraw();

	while (running)
	{
		DWORD start_time = GetTickCount();



		if (bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0 && lhc_doing < ACT && small1_doing < ACT && small2_doing < ACT && big_doing < ACT)
		{
			lhc_doing += lhc.speed;


		}

		if (life1 == 1 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0 && lhc_doing < ACT && small1_doing < ACT && small2_doing < ACT && big_doing < ACT)
		{
			small1_doing += smal1.speed;
		}

		if (life2 == 1 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0 && lhc_doing < ACT && small1_doing < ACT && small2_doing < ACT && big_doing < ACT)
		{
			big_doing += big.speed;
		}

		if (life3 == 1 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0 && lhc_doing < ACT && small1_doing < ACT && small2_doing < ACT && big_doing < ACT)
		{
			small2_doing += smal2.speed;
		}

		if (lhc_doing == small1_doing)
		{
			small1_doing -= 10;
		}

		if (lhc_doing == small2_doing)
		{
			small2_doing -= 10;
		}

		if (lhc_doing == big_doing)
		{
			big_doing -= 10;
		}

		if (small1_doing == small2_doing)
		{
			small1_doing -= 10;
		}

		if (small1_doing == big_doing)
		{
			small1_doing -= 10;
		}

		if (small2_doing == big_doing)
		{
			small2_doing -= 10;
		}

		while (peekmessage(&msg))
		{


			if (msg.message == WM_LBUTTONDOWN)
			{
				int x = msg.x;
				int y = msg.y;
				if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
				{
					MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
					running = false;
				}

			}
		}

		static int counter = 0;
		static int counter1 = 0;
		static int counter2 = 0;
		static int counter3 = 0;


		if (++counter % 5 == 0)
		{
			idx++;
			idx1++;
		}



		idx = idx % NUM1;
		idx1 = idx1 % WALK;


		cleardevice();

		putimage(0, 0, &environment1);

		drawtext1();

		drawtext3333();

		drawtext333();

		drawtext33333();

		setfillcolor(WHITE);

		fillrectangle(150, 50, 550, 80);

		fillrectangle(1320, 50, 1520, 80);

		fillrectangle(1320, 100, 1620, 130);

		fillrectangle(1320, 150, 1520, 180);

		setfillcolor(RED);

		fillrectangle(550 - x, 50, 550, 80);

		fillrectangle(1520 - x1, 50, 1520, 80);

		fillrectangle(1620 - x2, 100, 1620, 130);

		fillrectangle(1520 - x3, 150, 1520, 180);

		setfillcolor(WHITE);

		putimage(1580, 0, &end2);

		if (life1 == 0 && life2 == 0 && life3 == 0 && aa == 0 && bb == 0 && cc == 0 && dd == 0 && gg == 0)
		{
			MessageBox(GetHWnd(), _T("你已完成第一关！"), _T("恭喜你！"), MB_OK);
			running = false;
		}

		if (life == 0 && gg == 0)
		{
			MessageBox(GetHWnd(), _T("你死了！"), _T("很遗憾"), MB_OK);
			running = false;
		}

		if (bb == 0 && aa == 0 && dd == 0 && gg != 2 && gg != 5 && gg != 8 && life == 1)
			putimage1(200, 700, &lhc_wait[idx]);



		if (bb == 4)
		{
			putimage1(lhcx, lhcy, &lhc_Walk[idx1]);
			lhcx += 5;
			if (lhcx == 920)
			{
				bb = 5;
			}
			if (lhcy >= 600)
			{
				lhcy -= 5;
			}
		}

		if (bb == 5)
		{


			putimage1(920, 600, &lhcgongji[idx2]);

			putimage1(1020, 550, &small_hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				bb = 6;
				idx2 = 0;

				x1 += lhc.attack * 200.0 / smal1.life;

				if (x1 >= 200)
				{
					x1 = 200;

					life1 = 2;


				}
			}
		}

		if (bb == 6)
		{
			putimage1(lhcx, lhcy, &lhc_wwalk[idx1]);

			lhcx -= 5;



			if (lhcy <= 700)
			{
				lhcy += 5;
			}

			if (lhcx == 200)
			{
				bb = 0;
			}
		}

		if (bb == 1)
		{
			putimage1(lhcx, lhcy, &lhc_Walk[idx1]);
			lhcx += 5;
			if (lhcx == 1280)
			{
				bb = 2;
			}
		}

		if (bb == 2)
		{


			putimage1(1280, 700, &lhcgongji[idx2]);

			putimage1(1380, 550, &big_hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				bb = 3;
				idx2 = 0;

				x2 += lhc.attack * 300.0 / big.life;

				if (x2 >= 300)
				{
					x2 = 300;
					life2 = 2;
				}
			}
		}

		if (bb == 3)
		{
			putimage1(lhcx, lhcy, &lhc_wwalk[idx1]);

			lhcx -= 5;



			if (lhcx == 200)
			{
				bb = 0;
			}
		}

		if (bb == 7)
		{
			putimage1(lhcx, lhcy, &lhc_Walk[idx1]);
			lhcx += 5;
			if (lhcx == 1080)
			{
				bb = 8;
			}
			if (lhcy <= 800)
			{
				lhcy += 5;
			}
		}

		if (bb == 8)
		{


			putimage1(1080, 800, &lhcgongji[idx2]);

			putimage1(1180, 750, &small_hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				bb = 9;
				idx2 = 0;

				x3 += lhc.attack * 200.0 / smal2.life;

				if (x3 >= 200)
				{
					x3 = 200;
					life3 = 2;
				}
			}
		}

		if (bb == 9)
		{
			putimage1(lhcx, lhcy, &lhc_wwalk[idx1]);

			lhcx -= 5;



			if (lhcx == 200)
			{
				bb = 0;
			}

			if (lhcy > 700)
			{
				lhcy -= 5;
			}
		}

		if (aa == 1)
		{
			putimage1(200, 700, &lhc_shoot[idx3]);

			if (++counter2 % 10 == 0)
			{
				idx3++;
			}

			idx3 = idx3 % SHOOT;

			if (idx3 == 8)
			{
				aa = 0;
				idx3 = 0;
				cc = 1;
			}
		}

		if (aa == 2)
		{
			putimage1(200, 700, &lhc_shoot[idx3]);

			if (++counter2 % 10 == 0)
			{
				idx3++;
			}

			idx3 = idx3 % SHOOT;

			if (idx3 == 8)
			{
				aa = 0;
				idx3 = 0;
				cc = 3;
			}
		}

		if (aa == 3)
		{
			putimage1(200, 700, &lhc_shoot[idx3]);

			if (++counter2 % 10 == 0)
			{
				idx3++;
			}

			idx3 = idx3 % SHOOT;

			if (idx3 == 8)
			{
				aa = 0;
				idx3 = 0;
				cc = 5;
			}
		}


		if (bb != 2 && cc != 4 && dd != 2 && life2 == 1 && gg != 4 && gg != 5 && gg != 6 && gg != 10)
			putimage1(1380, 550, &big_wait[idx]);

		if (bb != 5 && cc != 2 && dd != 2 && life1 == 1 && gg != 1 && gg != 2 && gg != 3)
			putimage1(1020, 550, &small_wait[idx]);

		if (bb != 8 && cc != 6 && dd != 2 && life3 == 1 && gg != 7 && gg != 8 && gg != 9)
			putimage1(1180, 750, &small_wait[idx]);

		if (life == 2)
		{
			putimage1(200, 700, &die[idx4]);


			if (++counter3 % 10 == 0)
			{
				idx4++;
			}

			idx4 = idx4 % DIE;

			if (idx4 == 3)
			{
				life = 0;
				idx4 = 0;
			}
		}

		if (life == 0)
		{
			putimage1(200, 700, &die[3]);
		}

		if (life1 == 2)
		{
			putimage1(1020, 550, &small_die[idx4]);
			drawtext16();

			if (++counter3 % 10 == 0)
			{
				idx4++;
			}

			idx4 = idx4 % NUM1;

			if (idx4 == 5)
			{
				lhc.attack += 100;
				lhc.speed *= 2;
				lhc_doing = ACT;
				life1 = 0;
				idx4 = 0;
				if (cnt < 3)
				{
					cnt++;
				}
			}
		}

		if (life1 == 0)
		{
			putimage1(1020, 550, &small_die[5]);
		}

		if (life2 == 2)
		{
			putimage1(1380, 550, &big_die[idx4]);
			drawtext16();

			if (++counter3 % 10 == 0)
			{
				idx4++;
			}

			idx4 = idx4 % WALK;

			if (idx4 == 7)
			{
				lhc.attack += 100;
				lhc.speed *= 2;
				lhc_doing = ACT;
				life2 = 0;
				idx4 = 0;
				if (cnt < 3)
				{
					cnt++;
				}
			}
		}

		if (life2 == 0)
		{
			putimage1(1380, 550, &big_die[7]);
		}

		if (life3 == 2)
		{
			putimage1(1180, 750, &small_die[idx4]);
			drawtext16();

			if (++counter3 % 10 == 0)
			{
				idx4++;
			}

			idx4 = idx4 % NUM1;

			if (idx4 == 5)
			{
				lhc.attack += 100;
				lhc.speed *= 2;
				lhc_doing = ACT;
				life3 = 0;
				idx4 = 0;
				if (cnt < 3)
				{
					cnt++;
				}
			}
		}

		if (life3 == 0)
		{
			putimage1(1180, 750, &small_die[5]);
		}

		if (cc == 1)
		{
			putimage1(shootx, shooty, &shoot);
			shootx += 10;
			if (shootx == 1000)
			{
				cc = 2;
				shootx = 300;
				shooty = 740;
			}
			if (shooty > 620)
			{
				shooty -= 2;
			}
		}

		if (cc == 2)
		{
			putimage1(1020, 550, &small_hurt[idx2]);

			if (gbl1.speed > 10)
			{
				drawtext111();
			}

			if (gbl1.speed == 10)
			{
				drawtext44();
			}

			if (++counter1 % 10 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				cc = 0;
				idx2 = 0;
				if (smal1.speed > 10)
				{
					smal1.speed -= 10;
				}
				if (smal1.speed < 10)
				{
					smal1.speed = 10;
				}

				x1 += lhc.attack * 0.5 * 200.0 / smal1.life;

				if (x1 >= 200)
				{
					x1 = 200;
					life1 = 2;
				}
			}
		}

		if (cc == 3)
		{
			putimage1(shootx, shooty, &shoot);
			shootx += 10;
			if (shooty >= 700)
				shooty -= 1;
			if (shootx == 1360)
			{
				cc = 4;
				shootx = 300;
				shooty = 740;
			}

		}

		if (cc == 4)
		{
			putimage1(1380, 550, &big_hurt[idx2]);

			if (big.speed > 10)
			{
				drawtext111();
			}

			if (big.speed == 10)
			{
				drawtext44();
			}

			if (++counter1 % 10 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				cc = 0;
				idx2 = 0;
				if (big.speed > 10)
				{
					big.speed -= 10;
				}
				if (big.speed < 10)
				{
					big.speed = 10;
				}

				x2 += lhc.attack * 0.5 * 300.0 / big.life;

				if (x2 >= 300)
				{
					x2 = 300;
					life2 = 2;
				}
			}
		}

		if (cc == 5)
		{
			putimage1(shootx, shooty, &shoot);
			shootx += 10;
			if (shootx == 1160)
			{
				cc = 6;
				shootx = 300;
				shooty = 740;
			}
			if (shooty < 830)
			{
				shooty += 2;
			}

		}

		if (cc == 6)
		{
			putimage1(1180, 750, &small_hurt[idx2]);

			if (smal2.speed > 10)
			{
				drawtext111();
			}

			if (smal2.speed == 10)
			{
				drawtext44();
			}

			if (++counter1 % 10 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				cc = 0;
				idx2 = 0;
				if (smal2.speed > 10)
				{
					smal2.speed -= 10;
				}
				if (smal2.speed < 10)
				{
					smal2.speed = 10;
				}

				x3 += lhc.attack * 0.5 * 200.0 / smal2.life;

				if (x3 >= 200)
				{
					x3 = 200;
					life3 = 2;
				}
			}
		}

		if (dd == 1)
		{
			putimage1(lhcx, lhcy, &lhc_Walk[idx1]);
			lhcx += 5;
			if (lhcx == 1080)
			{
				dd = 2;
			}
		}

		if (dd == 2)
		{
			putimage1(lhcx, lhcy, &lhc_da[idx2]);

			if (life2 == 1)
				putimage1(1380, 550, &big_hurt[idx2]);

			if (life1 == 1)
				putimage1(1020, 550, &small_hurt[idx2]);

			if (life3 == 1)
				putimage1(1180, 750, &small_hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
			}

			idx2 = idx2 % NUM1;

			if (idx2 == 5)
			{
				dd = 0;
				cnt = 0;
				bb = 3;
				idx2 = 0;

				if (x2 < 300)
					x2 += lhc.attack * 300.0 / big.life;

				if (x1 < 200)
					x1 += lhc.attack * 200.0 / smal1.life;

				if (x3 < 200)
					x3 += lhc.attack * 200.0 / smal2.life;

				if (x2 >= 300 && life2 != 0)
				{
					x2 = 300;
					life2 = 2;
				}

				if (x3 >= 200 && life3 != 0)
				{
					x3 = 200;
					life3 = 2;
				}

				if (x1 >= 200 && life1 != 0)
				{
					x1 = 200;
					life1 = 2;
				}
			}
		}

		if (lhc_doing >= ACT && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0)
		{
			if (act == 0)
			{
				drawtext5();

				putimage(0, 810, &lhc_attack1);

				putimage(200, 810, &lhc_attack2);

				if (cnt < 3)
					putimage(400, 810, &lhc_attack4);

				if (cnt == 3)
				{
					putimage(400, 810, &lhc_attack3);
					drawtext17();
				}
			}

			if (act == 1 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0)
			{
				drawtext7();

				if (life1 != 0)
					putimage(0, 810, &decide1);

				if (life2 != 0)
					putimage(200, 810, &decide2);

				if (life3 != 0)
					putimage(400, 810, &decide3);

				while (peekmessage(&msg))
				{


					if (msg.message == WM_LBUTTONDOWN)
					{
						int x = msg.x;
						int y = msg.y;
						if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
						{
							MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
							running = false;
						}

						if (x <= 200 && x >= 0 && y >= 810 && y <= 960 && life1 != 0)
						{
							bb = 4;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1170 && x >= 1020 && y >= 600 && y <= 700 && life1 != 0)
						{
							bb = 4;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 400 && x >= 200 && y >= 810 && y <= 960 && life2 != 0)
						{

							bb = 1;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1630 && x >= 1380 && y >= 700 && y <= 800 && life2 != 0)
						{

							bb = 1;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 600 && x >= 400 && y >= 810 && y <= 960 && life3 != 0)
						{
							bb = 7;

							lhc_doing -= ACT;

							act = 0;
						}

						if (x <= 1330 && x >= 1180 && y >= 800 && y <= 900 && life3 != 0)
						{
							bb = 7;

							lhc_doing -= ACT;

							act = 0;
						}
					}
				}
			}

			if (act == 2 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0)
			{
				drawtext8();

				if (life1 != 0)
					putimage(0, 810, &decide1);

				if (life2 != 0)
					putimage(200, 810, &decide2);

				if (life3 != 0)
					putimage(400, 810, &decide3);

				while (peekmessage(&msg))
				{


					if (msg.message == WM_LBUTTONDOWN)
					{
						int x = msg.x;
						int y = msg.y;
						if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
						{
							MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
							running = false;
						}

						if (x <= 200 && x >= 0 && y >= 810 && y <= 960 && life1 != 0)
						{
							aa = 1;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1170 && x >= 1020 && y >= 600 && y <= 700 && life1 != 0)
						{
							aa = 1;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 400 && x >= 200 && y >= 810 && y <= 960 && life2 != 0)
						{
							aa = 2;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1630 && x >= 1380 && y >= 700 && y <= 800 && life2 != 0)
						{
							aa = 2;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 600 && x >= 400 && y >= 810 && y <= 960 && life3 != 0)
						{
							aa = 3;

							lhc_doing -= ACT;

							act = 0;

						}

						if (x <= 1330 && x >= 1180 && y >= 800 && y <= 900 && life3 != 0)
						{
							aa = 3;

							lhc_doing -= ACT;

							act = 0;

						}
					}
				}
			}

			if (act == 3 && bb == 0 && aa == 0 && cc == 0 && dd == 0 && gg == 0)
			{
				drawtext9();

				putimage(0, 810, &decide4);


				while (peekmessage(&msg))
				{


					if (msg.message == WM_LBUTTONDOWN)
					{
						int x = msg.x;
						int y = msg.y;
						if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
						{
							MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
							running = false;
						}

						if (x <= 600 && x >= 0 && y >= 810 && y <= 960)
						{
							dd = 1;

							lhc_doing -= ACT;

							act = 0;

						}


					}
				}
			}



			while (peekmessage(&msg))
			{


				if (msg.message == WM_LBUTTONDOWN)
				{
					int x = msg.x;
					int y = msg.y;
					if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
					{
						MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
						running = false;
					}

					if (x <= 200 && x >= 0 && y >= 810 && y <= 960)
					{
						act = 1;
						/*lhc_doing -= ACT;*/
						if (cnt < 3)
						{
							cnt++;
						}

					}

					if (x <= 400 && x >= 200 && y >= 810 && y <= 960)
					{
						act = 2;
						/*lhc_doing -= ACT;*/
						if (cnt < 3)
						{
							cnt++;
						}

					}

					if (x <= 600 && x >= 400 && y >= 810 && y <= 960 && cnt == 3)
					{
						act = 3;
						/*lhc_doing -= ACT;*/

					}
				}
			}

			/*lhc.speed -= lhc.speed;

			gbl1_doing -= gbl1.speed;

			gbl2_doing -= gbl2.speed;

			gbl3_doing -= gbl3.speed;*/

		}


		if (small1_doing >= ACT && dd == 0 && bb == 0 && aa == 0 && cc == 0 && life1 == 1 && gg == 0)
		{


			gg = 1;

			small1_doing -= ACT;

			while (peekmessage(&msg))
			{


				if (msg.message == WM_LBUTTONDOWN)
				{
					int x = msg.x;
					int y = msg.y;
					if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
					{
						MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
						running = false;
					}

				}
			}


		}

		if (gg == 1)
		{
			putimage1(small1x, small1y, &small_move[idx1]);

			drawtext6();

			small1x -= 5;
			if (small1x == 300)
			{
				gg = 2;
			}
			if (small1y <= 600)
			{
				small1y += 5;
			}
		}

		if (gg == 2)
		{
			putimage1(300, 650, &small_attack[idx3]);

			putimage1(200, 700, &hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
				idx3++;
			}

			idx2 = idx2 % NUM1;
			idx3 = idx3 % WALK;

			if (idx3 == 7)
			{
				gg = 3;
				idx2 = 0;
				idx3 = 0;

				x += smal1.attack * 400.0 / lhc.life;

				if (x >= 400)
				{
					x = 400;

					life = 2;


				}
			}
		}

		if (gg == 3)
		{
			putimage1(small1x, small1y, &small_mmove[idx1]);

			small1x += 5;



			if (small1y >= 550)
			{
				small1y -= 5;
			}

			if (small1x == 1020)
			{
				gg = 0;
			}
		}


		if (big_doing >= ACT && dd == 0 && bb == 0 && aa == 0 && cc == 0 && life2 == 1 && gg == 0)
		{


			gg = 4;

			big_doing -= ACT;

			while (peekmessage(&msg))
			{


				if (msg.message == WM_LBUTTONDOWN)
				{
					int x = msg.x;
					int y = msg.y;
					if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
					{
						MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
						running = false;
					}

				}
			}


		}

		if (gg == 4)
		{
			putimage1(bigx, bigy, &big_walk[idx1]);

			drawtext6();

			bigx -= 5;
			if (bigx == 300)
			{
				if(bi < 2)
				{
					gg = 5;
					bi++;
				}
				else if (bi == 2)
				{
					gg = 10;
					bi = 0;
				}
			}

		}

		if (gg == 10)
		{
			putimage1(300, 550, &big_attack[idx3]);

			putimage1(200, 700, &hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
				idx3++;
			}

			idx2 = idx2 % NUM1;
			idx3 = idx3 % WALK;

			if (idx3 == 7)
			{
				gg = 6;
				idx2 = 0;
				idx3 = 0;

				x += big.attack * 1.5 * 400.0 / lhc.life;

				if (x >= 400)
				{
					x = 400;

					life = 2;


				}
			}
		}

		if (gg == 5)
		{
			putimage1(300, 550, &big_da[idx3]);

			putimage1(200, 700, &hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
				idx3++;
			}

			idx2 = idx2 % NUM1;
			idx3 = idx3 % WALK;

			if (idx3 == 7)
			{
				gg = 6;
				idx2 = 0;
				idx3 = 0;

				x += big.attack * 400.0 / lhc.life;

				if (x >= 400)
				{
					x = 400;

					life = 2;


				}
			}
		}

		if (gg == 6)
		{
			putimage1(bigx, bigy, &big_wwalk[idx1]);

			bigx += 5;





			if (bigx == 1380)
			{
				gg = 0;
			}
		}


		if (small2_doing >= ACT && dd == 0 && bb == 0 && aa == 0 && cc == 0 && life3 == 1 && gg == 0)
		{


			gg = 7;

			small2_doing -= ACT;

			while (peekmessage(&msg))
			{


				if (msg.message == WM_LBUTTONDOWN)
				{
					int x = msg.x;
					int y = msg.y;
					if (x <= 1680 && x >= 1580 && y >= 0 && y <= 100)
					{
						MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
						running = false;
					}

				}
			}


		}

		if (gg == 7)
		{
			putimage1(small2x, small2y, &small_move[idx1]);

			drawtext6();

			small2x -= 5;
			if (small2x == 300)
			{
				gg = 8;
			}
			if (small2y >= 600)
			{
				small2y -= 5;
			}
		}

		if (gg == 8)
		{
			putimage1(300, 650, &small_attack[idx3]);

			putimage1(200, 700, &hurt[idx2]);

			if (++counter1 % 15 == 0)
			{
				idx2++;
				idx3++;
			}

			idx2 = idx2 % NUM1;
			idx3 = idx3 % WALK;

			if (idx3 == 7)
			{
				gg = 9;
				idx2 = 0;
				idx3 = 0;

				x += smal2.attack * 400.0 / lhc.life;

				if (x >= 400)
				{
					x = 400;

					life = 2;


				}
			}
		}

		if (gg == 9)
		{
			putimage1(small2x, small2y, &small_mmove[idx1]);

			small2x += 5;



			if (small2y <= 750)
			{
				small2y += 5;
			}

			if (small2x == 1180)
			{
				gg = 0;
			}
		}

		FlushBatchDraw();

		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 144)
		{
			Sleep(1000 / 144 - delta_time);
		}
	}

	EndBatchDraw();

	closegraph();
}


int main()
{
	initgraph(ob_wideth,ob_highth);


	mciSendStringW(_T("open music/bgm.wav alias bgm"),NULL,0,NULL);

	mciSendStringW(_T("play bgm repeat from 0"),NULL,0,NULL);

	bool running = true;

	loadbig_walk();

	loadbig_wwalk();

	loadlhc_wait();

	loadsmall_wait();

	loadbig_wait();

	loadbig_die();

	loadgblda();

	loadgbl_walk();

	loadgsmall_move();

	loadgsmall_mmove();

	loadbig_da();

	loadsmall_die();

	loadgbl_wwalk();

	loadlhc_shoot();

	loadgbl_attack();

	loadbig_attack();

	loadsmall_attack();

	loadsmall_hurt();

	loadbig_hurt();

	loadhurt();

	loaddie();

	loadgbl_die();

	loadlhc_da();

	loadimage(&ob, L"photo/ob.jpg", ob_wideth, ob_highth);
	loadimage(&start_1, L"photo/start_1.jpg", 336, 118);
	loadimage(&logo, L"photo/logo.png");
	loadimage(&end, L"photo/end.jpg", 336, 118);
	
	putimage(0, 0, &ob);
	putimage(694, 420, &start_1);
	putimage(694, 540, &end);
	putimage(0, 0, &logo);

	BeginBatchDraw();
	
	while (running)
	{
		DWORD start_time = GetTickCount();

		while (peekmessage(&msg))
		{
			

			if (msg.message == WM_LBUTTONDOWN)
			{
				int x = msg.x;
				int y = msg.y;
				if (x <= 1030 && x >= 694 && y >= 540 && y <= 658)
				{
					MessageBox(GetHWnd(), _T("你已退出游戏"), _T("提示"), MB_OK);
					running = false;
				}
				else if (x <= 1030 && x >= 694 && y >= 420 && y <= 538)
				{
					

					
					
					Decide();

				}
			}
		}

		static int counter = 0;

		if (++counter % 5 == 0)
		{
			idx++;
		}

		idx = idx % NUM1;

		putimage1(200, 700, &lhc_wait[idx]);

		FlushBatchDraw();
		
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 144)
		{
			Sleep(1000 / 144 - delta_time);
		}
	}
	
	
	EndBatchDraw();
	
	closegraph();			// 关闭绘图窗口
	return 0;
}