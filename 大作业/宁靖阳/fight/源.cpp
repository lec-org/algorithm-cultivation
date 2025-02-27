#include <Windows.h>		//windowsҪ����graphics֮ǰ
#include <graphics.h>
#include "menuScene.h"
#include "gameScene.h"
#include "selectorScene.h"
#include "sceneManager.h"
#include "util.h"
#include "atlas.h"
#include "platform.h"
#include <iostream>
using namespace std;

#pragma comment(lib, "Winmm.lib")	//mciSendString

bool isDebug = false;

IMAGE	imgMenuBackground;

IMAGE	imgVS;										//VS������

IMAGE	img1P;										//�ı�
IMAGE	img2P;
IMAGE	img1PDesc;									//��λ����
IMAGE	img2PDesc;

IMAGE	imgGraveStoneLeft;							//����Ĺ��
IMAGE	imgGraveStoneRight;
IMAGE	imgSelectorTip;								//ѡ����ʾ
IMAGE	imgSelectorBackground;

IMAGE	img1PSelectorButtonIdleLeft;				//1P����ѡ��ťĬ��
IMAGE	img1PSelectorButtonIdleRight;
IMAGE	img1PSelectorButtonDownLeft;
IMAGE	img1PSelectorButtonDownRight;				//1P����ѡ��ť����

IMAGE	img2PSelectorButtonIdleLeft;
IMAGE	img2PSelectorButtonIdleRight;
IMAGE	img2PSelectorButtonDownLeft;
IMAGE	img2PSelectorButtonDownRight;

IMAGE	imgPeaShooterSelectorBackgroundLeft;		//��������ѡ�����
IMAGE	imgPeaShooterSelectorBackgroundRight;
IMAGE	imgSunFlowerSelectorBackgroundLeft;			//һ������ѡ�����
IMAGE	imgSunFlowerSelectorBackgroundRight;

IMAGE	imgSky;										//���
IMAGE	imgHills;									//ɽ��
IMAGE	imgLargePlatform;							//ƽ̨
IMAGE	imgSmallPlatform;

IMAGE	img1PCursor;
IMAGE	img2PCursor;

Atlas	atlasPeaShooterIdleLeft;			//p1����
Atlas	atlasPeaShooterIdleRight;
Atlas	atlasPeaShooterRunLeft;
Atlas	atlasPeaShooterRunRight;
Atlas	atlasPeaShooterAttackExLeft;		//p1�������⹥��
Atlas	atlasPeaShooterAttackExRight;
Atlas	atlasPeaShooterDieLeft;				//��������
Atlas	atlasPeaShooterDieRight;

Atlas	atlasSunFlowerIdleLeft;				//p2
Atlas	atlasSunFlowerIdleRight;
Atlas	atlasSunFlowerRunLeft;
Atlas	atlasSunFlowerRunRight;
Atlas	atlasSunFlowerAttackExLeft;
Atlas	atlasSunFlowerAttackExRight;
Atlas	atlasSunFlowerDieLeft;
Atlas	atlasSunFlowerDieRight;

Atlas	atlasnewPlayerIdleLeft;				//p3
Atlas	atlasnewPlayerIdleRight;
Atlas	atlasnewPlayerRunLeft;
Atlas	atlasnewPlayerRunRight;
Atlas	atlasnewPlayerAttackExLeft;
Atlas	atlasnewPlayerAttackExRight;
Atlas	atlasnewPlayerDieLeft;
Atlas	atlasnewPlayerDieRight;


IMAGE	imgPea;								//�㶹
Atlas	atlasPeaBreak;

IMAGE imgtrans;
Atlas atlastransBreak;

Atlas	atlasSun;
Atlas	atlasSunExplode;					//̫����ը
Atlas	atlasSunEx;							//���⶯��
Atlas	atlasSunExExplode;					//���ⱬը
Atlas	atlasSunText;						//�ı�����

Atlas	atlastransEx;						//��������⶯��	
Atlas   atlastransExExplode;				//��������ⱬը

Atlas	atlasRunEffect;						//������Ч
Atlas	atlasJumpEffect;
Atlas	atlasLandEffect;

IMAGE	img1PWinner;						//1P��ʤ�ı�
IMAGE	img2PWinner;
IMAGE	imgWinnerBar;						//��ʤ����

IMAGE	imgPeaShooterAvatar;				//�㶹ͷ��
IMAGE	imgSunFlowerAvatar;					//���տ�ͷ��

//�����볡����������������
Scene* menuScene = new MenuScene;
Scene* gameScene = new GameScene;
Scene* selectorScene = new SelectorScene;

SceneManager sceneManager;

vector<Bullet*> bullets;
vector<Platform> platforms;

Player* player1 = nullptr;	Player* player2 = nullptr;
Player* newplayer = nullptr;

bool isSlideOutStarted = false;	

IMAGE* imgPlayer1Avatar = nullptr;	IMAGE* imgPlayer2Avatar = nullptr;

void flipAtlas(Atlas& src, Atlas& dst) {

	dst.clear();

	for (int i = 0; i < src.getSize(); i++) {

		IMAGE img;
		flipImage(src.getImage(i), &img);

		dst.addImage(img);
	}

}

void loadResources() {

	//��������
		//�� IPix.ttf" ���ص�ϵͳ�����У�����������Ϊ˽�����塣
	AddFontResourceEx(_T("resources/IPix.ttf"), FR_PRIVATE, nullptr);

	//����ͼƬ
	loadimage(&imgMenuBackground, _T("resources/menu_background.png"));

	loadimage(&imgVS, _T("resources/VS.png"));
	loadimage(&img1P, _T("resources/1P.png"));
	loadimage(&img2P, _T("resources/2P.png"));
	loadimage(&img1PDesc, _T("resources/1P_desc.png"));
	loadimage(&img2PDesc, _T("resources/2P_desc.png"));
	loadimage(&imgGraveStoneRight, _T("resources/gravestone.png"));
	flipImage(&imgGraveStoneRight, &imgGraveStoneLeft);

	loadimage(&imgSelectorTip, _T("resources/selector_tip.png"));
	loadimage(&imgSelectorBackground, _T("resources/selector_background.png"));

	loadimage(&img1PSelectorButtonIdleRight, _T("resources/1P_selector_btn_idle.png"));
	flipImage(&img1PSelectorButtonIdleRight, &img1PSelectorButtonIdleLeft);
	loadimage(&img1PSelectorButtonDownRight, _T("resources/1P_selector_btn_down.png"));
	flipImage(&img1PSelectorButtonDownRight, &img1PSelectorButtonDownLeft);

	loadimage(&img2PSelectorButtonIdleRight, _T("resources/2P_selector_btn_idle.png"));
	flipImage(&img2PSelectorButtonIdleRight, &img2PSelectorButtonIdleLeft);
	loadimage(&img2PSelectorButtonDownRight, _T("resources/2P_selector_btn_down.png"));
	flipImage(&img2PSelectorButtonDownRight, &img2PSelectorButtonDownLeft);

	loadimage(&imgPeaShooterSelectorBackgroundRight, _T("resources/peashooter_selector_background.png"));
	flipImage(&imgPeaShooterSelectorBackgroundRight, &imgPeaShooterSelectorBackgroundLeft);
	loadimage(&imgSunFlowerSelectorBackgroundRight, _T("resources/sunflower_selector_background.png"));
	flipImage(&imgSunFlowerSelectorBackgroundRight, &imgSunFlowerSelectorBackgroundLeft);

	loadimage(&imgSky, _T("resources/sky.png"));
	loadimage(&imgHills, _T("resources/hills.png"));
	loadimage(&imgLargePlatform, _T("resources/platform_large.png"));
	loadimage(&imgSmallPlatform, _T("resources/platform_small.png"));

	loadimage(&img1PCursor, _T("resources/1P_cursor.png"));
	loadimage(&img2PCursor, _T("resources/2P_cursor.png"));

	//��������
	atlasPeaShooterIdleRight.loadImages(_T("resources/peashooter_idle_%d.png"), 9);
	flipAtlas(atlasPeaShooterIdleRight, atlasPeaShooterIdleLeft);
	atlasPeaShooterRunRight.loadImages(_T("resources/peashooter_run_%d.png"), 5);
	flipAtlas(atlasPeaShooterRunRight, atlasPeaShooterRunLeft);
	atlasPeaShooterAttackExRight.loadImages(_T("resources/peashooter_attack_ex_%d.png"), 3);
	flipAtlas(atlasPeaShooterAttackExRight, atlasPeaShooterAttackExLeft);
	atlasPeaShooterDieRight.loadImages(_T("resources/peashooter_die_%d.png"), 4);
	flipAtlas(atlasPeaShooterDieRight, atlasPeaShooterDieLeft);

	//һ��
	atlasSunFlowerIdleRight.loadImages(_T("resources/sunflower_idle_%d.png"), 8);
	flipAtlas(atlasSunFlowerIdleRight, atlasSunFlowerIdleLeft);
	atlasSunFlowerRunRight.loadImages(_T("resources/sunflower_run_%d.png"), 5);
	flipAtlas(atlasSunFlowerRunRight, atlasSunFlowerRunLeft);
	atlasSunFlowerAttackExRight.loadImages(_T("resources/sunflower_attack_ex_%d.png"), 9);
	flipAtlas(atlasSunFlowerAttackExRight, atlasSunFlowerAttackExLeft);
	atlasSunFlowerDieRight.loadImages(_T("resources/sunflower_die_%d.png"), 2);
	flipAtlas(atlasSunFlowerDieRight, atlasSunFlowerDieLeft);

	//p2����Ч��
	atlasnewPlayerIdleRight.loadImages(_T("resources/transp2_idle_%d.png"), 9);
	flipAtlas(atlasnewPlayerIdleRight, atlasnewPlayerIdleLeft);
	atlasnewPlayerRunRight.loadImages(_T("resources/transp2_run_%d.png"), 5);
	flipAtlas(atlasnewPlayerRunRight, atlasnewPlayerRunLeft);
	atlasnewPlayerAttackExRight.loadImages(_T("resources/transp2_attack_ex_%d.png"), 3);
	flipAtlas(atlasnewPlayerAttackExRight, atlasnewPlayerAttackExLeft);
	atlasnewPlayerDieRight.loadImages(_T("resources/transp2_die_%d.png"), 4);
	flipAtlas(atlasnewPlayerDieRight, atlasnewPlayerDieLeft);




	loadimage(&imgPea, _T("resources/pea.png"));
	atlasPeaBreak.loadImages(_T("resources/pea_break_%d.png"), 3);

	loadimage(&imgtrans, _T("resources/trans.png"));	
	atlastransBreak.loadImages(_T("resources/trans_break_%d.png"), 3);

	atlasSun.loadImages(_T("resources/sun_%d.png"), 5);
	atlasSunExplode.loadImages(_T("resources/sun_explode_%d.png"), 5);
	atlasSunEx.loadImages(_T("resources/sun_ex_%d.png"), 5);
	atlasSunExExplode.loadImages(_T("resources/sun_ex_explode_%d.png"), 5);
	atlasSunText.loadImages(_T("resources/sun_text_%d.png"), 6);

	atlastransEx.loadImages(_T("resources/trans_ex_%d.png"), 5);
	atlastransExExplode.loadImages(_T("resources/trans_ex_explode_%d.png"), 5);

	atlasRunEffect.loadImages(_T("resources/run_effect_%d.png"), 4);
	atlasJumpEffect.loadImages(_T("resources/jump_effect_%d.png"), 5);
	atlasLandEffect.loadImages(_T("resources/land_effect_%d.png"), 2);

	loadimage(&img1PWinner, _T("resources/1P_winner.png"));
	loadimage(&img2PWinner, _T("resources/2P_winner.png"));
	loadimage(&imgWinnerBar, _T("resources/winnner_bar.png"));

	loadimage(&imgPeaShooterAvatar, _T("resources/avatar_peashooter.png"));
	loadimage(&imgSunFlowerAvatar, _T("resources/avatar_sunflower.png"));

	//��������
	mciSendString(_T("open resources/bgm_game.mp3 alias bgmGame"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/bgm_menu.mp3 alias bgmMenu"), nullptr, 0, nullptr);

	mciSendString(_T("open resources/pea_break_1.mp3 alias peaBreak1"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/pea_break_2.mp3 alias peaBreak2"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/pea_break_3.mp3 alias peaBreak3"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/pea_shoot_1.mp3 alias peaShoot1"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/pea_shoot_2.mp3 alias peaShoot2"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/pea_shoot_ex.mp3 alias peaShootEx"), nullptr, 0, nullptr);

	mciSendString(_T("open resources/sun_explode.mp3 alias sunExplode"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/sun_explode_ex.mp3 alias sunExplodeEx"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/sun_text.mp3 alias sunText"), nullptr, 0, nullptr);

	mciSendString(_T("open resources/ui_confirm.wav alias uiConfirm"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/ui_switch.wav alias uiSwitch"), nullptr, 0, nullptr);
	mciSendString(_T("open resources/ui_win.wav alias uiWin"), nullptr, 0, nullptr);
}

int main() {
	//������Դ
	loadResources();

	//��ʼ��������	
	sceneManager.setSceneManager(menuScene);
	ExMessage msg;
	const int FPS = 1000 / 60;

	initgraph(1280, 720, EW_SHOWCONSOLE);	//EW_SHOWCONSOLE

	//�����ı���ʽ
		//Ҫ��initgraph��������
	settextstyle(28, 0, _T("IPix"));
	setbkmode(TRANSPARENT);

	BeginBatchDraw();

	while (1) {
		auto startTime = GetTickCount64();

		//������Ϣ
		if (peekmessage(&msg))
			sceneManager.receiveInput(msg);

		//���������е�ʱ��
		static auto managerLastTime = GetTickCount64();
		auto managerCurrentTime = GetTickCount64();

		sceneManager.update(managerCurrentTime - managerLastTime);

		managerLastTime = managerCurrentTime;

		cleardevice();

		//��Ⱦ
		sceneManager.render();

		FlushBatchDraw();

		//hertz
		auto excutionTime = GetTickCount64() - startTime;
		if (excutionTime < FPS)
			Sleep(FPS - excutionTime);

	}

	EndBatchDraw();

	//�ͷ���Դ
	delete menuScene;
	delete gameScene;

}
