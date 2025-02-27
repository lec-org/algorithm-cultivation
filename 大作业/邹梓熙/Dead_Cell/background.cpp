#define _CRT_SECURE_NO_WARNINGS
#include<easyx.h>
#include<string>
#include<iostream>
#include"background.h"
#include"putimage_alpha.h"


Background::Background()
{
	load_background();
	load_ui();

	text_style = { 10, 0, 10, false, false, false };
}

Background::~Background()
{

}

void Background::load_background()
{
	loadimage(&img_background_1, L"./image_source/background/1.png", 1280, 720, true);
	loadimage(&img_background_2, L"./image_source/background/2.png", 1280, 720, true);
	loadimage(&img_background_3, L"./image_source/background/3.png", 1280, 720, true);
	loadimage(&img_background_2, L"./image_source/background/4.png", 1280, 720, true);
	loadimage(&img_background_3, L"./image_source/background/5.png", 1280, 720, true);
}


void Background::load_ui()
{
	loadimage(&img_ui1, L"./image_source/UI/1.png", 90, 90, true);
	loadimage(&img_ui2, L"./image_source/UI/1.png", 80, 80, true);
	//"D:\Visual Studio Project\Dead_Cell\image_source\UI\1.png"
}


void Background::put_background()
{
	Putimage_alpha::putimage_alpha(0, 0, &img_background_1);
	Putimage_alpha::putimage_alpha(0, 0, &img_background_2);
	Putimage_alpha::putimage_alpha(0, 0, &img_background_3);
	Putimage_alpha::putimage_alpha(0, 0, &img_background_4);
	Putimage_alpha::putimage_alpha(0, 0, &img_background_5);
	

}

void  Background::put_ui1()
{
	Putimage_alpha::putimage_alpha(659, 550, &img_ui1);
}

void Background::put_ui2()
{
	Putimage_alpha::putimage_alpha(664, 555, &img_ui2);
}

void Background::put_text()
{

	outtextxy(1000, 500, str_ad);
	outtextxy(1000, 550, str_k);
	outtextxy(1000, 600, str_l);
	outtextxy(1000, 650, str_j);
}

