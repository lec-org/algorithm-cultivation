#include <iostream>
#include <easyx.h>
#include"tools.hpp"
#include <time.h>
#include <stdlib.h>
using namespace std;

//�ӵ��ṹ
struct Bullet
{
    int x;
	int y;
	bool isShot;
	int speed;
};

#define BULLET_NUM 15  

//�л��ṹ
struct Enemy
{
	int x;
	int y;
	int w;
	int h;
	int speed;
	bool active; //�Ƿ���;
	int type;//�л�����;
	int hp;
};
#define ENEMY_NUM 15

bool pointInRect(int x,int y, int rx,int ry, int rw,int rh) {
	if (x >= rx && y >= ry && x < rx + rw && y < ry + rh) return true;
	return false;
}

int main() {
	initgraph(480,852);

	setbkcolor(LIGHTGRAY);

	cleardevice();

	//�������������
	srand(time(NULL));

	IMAGE img_bk;
	IMAGE img_player[2];
	IMAGE img_bullet[2];
	IMAGE img_enemy[3];
	loadimage(&img_bk, "resource/images/background.png");
	loadimage(img_player+0, "resource/images/hero1.png");
	loadimage(img_player+1, "resource/images/hero2.png");
	loadimage(img_bullet + 0, "resource/images/bullet1.png");
	loadimage(img_bullet + 1, "resource/images/bullet2.png");
	loadimage(img_enemy + 0, "resource/images/enemy1.png");
	loadimage(img_enemy + 1, "resource/images/enemy2.png");
	loadimage(img_enemy + 2, "resource/images/enemy3_n1.png");
	
	int yPos = 0;
	int yPos1 = -getheight();

	int playerX = 0;
	int playerY = 0;
	int frameIdx = 0;
	int playerSpeed = 3;

	Bullet bullet[BULLET_NUM] = {0};
	Enemy enemies [ENEMY_NUM] = { 0 };

	while (1) {
	   //����˫�����ͼ
	   BeginBatchDraw();
	   cleardevice();
	   //����ͼ
       putimage(0, yPos1, &img_bk);
	   yPos1+=2;
	   if (yPos1 >= 0)yPos1 = -getheight();
	   putimage(0, yPos, &img_bk);
	   yPos+=2;
	   if (yPos >= getheight()) {
		   yPos = 0;
	   }
	   //���
	   drawImg(playerX, playerY, img_player + frameIdx);
	   //frameIdx = (frameIdx + 1) % 2;
	   frameIdx = (clock() / 500) % 2;
	   
	   for (size_t i = 0; i < BULLET_NUM; i++ ) {
         
	   if (bullet[i].isShot) {
		   //�����ӵ�
               drawImg(bullet[i].x, bullet[i].y, img_bullet + 0);
			//�ƶ��ӵ�
			   bullet[i].y -= bullet[i].speed;
			//����ӵ������˴��ڵı߽磬�ͻ�����
			   if (bullet[i].y < -15)
				   bullet[i].isShot = false;
	   } 
	   }
	
	     
	   for (size_t i = 0; i < ENEMY_NUM;i++) {
		   if (enemies[i].active)
		   {
			   //���Ƶл�
			   drawImg(enemies[i].x, enemies[i].y,img_enemy + enemies[i].type);
			   //���µл�����
			   enemies[i].y += enemies[i].speed;
		   }
	   }

	   static int count = 0;
	   //�Զ�����л�
	   if (count % 60 == 0)
	   {
		   for (size_t i = 0; i < ENEMY_NUM;i++) {
			   if (!enemies[i].active) {
				   enemies[i].active = true;
				   enemies[i].speed = rand() % 4 + 1;
				   enemies[i].type = rand() % 3;
                   enemies[i].w = img_enemy[enemies[i].type].getwidth();
				   enemies[i].h = img_enemy[enemies[i].type].getheight();
				   enemies[i].x = rand() %(getwidth() - enemies[i].w);
				   enemies[i].y = -rand() %300;
				   enemies[i].hp = rand() % 3 + 1;
				   break;
			   }
		   }
	   }
	   
	   if (count % 12 == 0) {
		   //��һ��û�з�����ӵ������������ȥ
		   for (size_t i = 0; i < BULLET_NUM; i++)
		   {
			   if (!bullet[i].isShot) {
				   bullet[i].speed = playerSpeed + 2;
				   bullet[i].x = playerX + 47;
				   bullet[i].y = playerY - 15;
				   bullet[i].isShot = true;
				   break;
			   }

		   }
	   }
	   
	   //��ײ���
	   for (size_t i = 0; i < BULLET_NUM; i++) {
		   if (!bullet[i].isShot) continue;

		   for (size_t k = 0; k < ENEMY_NUM; k++) {
			   if (!enemies[k].active)
				   continue;

			   //�ж��ӵ���л��Ƿ���ײ
			   if (pointInRect(bullet[i].x, bullet[i].y, enemies[k].x, enemies[k].y, enemies[k].w, enemies[k].h)){
				   //�л���ʧ
				   
				   if (enemies[k].hp > 0) enemies[k].hp--;
				   else enemies[k].active = false;
				   //�ӵ���ʧ
				   bullet[i].isShot = false;
			   }
		   }
	   }
	   //��Ϣ����
	   ExMessage msg = { 0 };
	   //��ȡ��Ϣ
	   while (peekmessage(&msg)) {
           //�������
		   //��������
		   if (msg.message == WM_KEYDOWN)
		   {
			   switch (msg.vkcode) {
			   case VK_UP://�ϼ�
				   playerY -= playerSpeed;
				   break;
			   case VK_DOWN://�¼�
				   playerY += playerSpeed;
				   break;
			   case VK_LEFT://���
				   playerX -= playerSpeed;
				   break;
			   case VK_RIGHT://�Ҽ�
				   playerX += playerSpeed;
				   break;
			   default:
				   break;
			   }
		   }
		   else if (msg.message == WM_MOUSEMOVE)
		   {
			   playerX = msg.x - 50;
			   playerY = msg.y - 63;
		   }
		   else if (msg.message == WM_LBUTTONDOWN)
		   {  
			   //�ҵ�һ��û�з�����ӵ������������ȥ
			   for (size_t i = 0; i < BULLET_NUM; i++)
			   {
				   if (!bullet[i].isShot) {
			   bullet[i].speed = playerSpeed + 2;
			   bullet[i].x = playerX + 47;
			   bullet[i].y = playerY - 15;
			   bullet[i].isShot = true;
			   break;
				   }

			   }
			  
		   }
	   }
	   
	   EndBatchDraw();
	   //�ӳ�
	   Sleep(10);
	   count++;
	}
	

	//��ֹ�����˳�
	getchar();
	return 0;
}