#pragma once
#include "scene.h"
#include "animation.h"
#include "sceneManager.h"
#include "util.h"
#include "peaShooterPlayer.h"
#include "sunFlowerPlayer.h"
#include "newPlayer.h"	

extern Player* player1;
extern Player* player2;
extern Player* newplayer;

//VS艺术字
extern IMAGE imgVS;
//玩家
extern IMAGE img1P;
extern IMAGE img2P;
//键位描述
extern IMAGE img1PDesc;
extern IMAGE img2PDesc;
//背景
extern IMAGE imgSelectorBackground;
//提示信息
extern IMAGE imgSelectorTip;
//墓碑
extern IMAGE imgGraveStoneLeft;
extern IMAGE imgGraveStoneRight;

//1P button
extern IMAGE img1PSelectorButtonIdleLeft;
extern IMAGE img1PSelectorButtonIdleRight;
extern IMAGE img1PSelectorButtonDownLeft;
extern IMAGE img1PSelectorButtonDownRight;
//2P button
extern IMAGE img2PSelectorButtonIdleLeft;
extern IMAGE img2PSelectorButtonIdleRight;
extern IMAGE img2PSelectorButtonDownLeft;
extern IMAGE img2PSelectorButtonDownRight;
//background
extern IMAGE imgPeaShooterSelectorBackgroundLeft;
extern IMAGE imgPeaShooterSelectorBackgroundRight;
extern IMAGE imgSunFlowerSelectorBackgroundLeft;
extern IMAGE imgSunFlowerSelectorBackgroundRight;

extern Atlas atlasPeaShooterIdleRight;
extern Atlas atlasSunFlowerIdleRight;

extern IMAGE imgPeaShooterAvatar;
extern IMAGE imgSunFlowerAvatar;

extern IMAGE* imgPlayer1Avatar;
extern IMAGE* imgPlayer2Avatar;

extern SceneManager sceneManager;

class SelectorScene :public Scene {
public:
	void enter() override;								//场景进入
	void exit() override;								//场景退出

	void receiveInput(const ExMessage& msg) override;	//场景接收输入
	void update(int runTimeMs) override;				//场景更新——让场景运行的时间
	void render() override;								//场景渲染

private:
	POINT posImgVS = { 0 };							//VS艺术字 位置
	POINT posImgTip = { 0 };						//提示信息 位置
	POINT posImg1P = { 0 };							//1P 位置
	POINT posImg2P = { 0 };							//2P 位置

	POINT posImg1PDesc = { 0 };						//1P键位描述 位置
	POINT posImg2PDesc = { 0 };						//2P键位描述 位置
	POINT posImg1PName = { 0 };						//1P姓名 位置
	POINT posImg2PName = { 0 };						//2P姓名 位置

	POINT posAnimation1P = { 0 };					//1P角色 位置
	POINT posAnimation2P = { 0 };					//2P角色 位置

	POINT posImg1PGravestone = { 0 };				//1P墓碑 位置
	POINT posImg2PGravestone = { 0 };				//2P墓碑 位置

	POINT pos1PSelectorButtonLeft = { 0 };			//1P向左切换按钮 位置
	POINT pos1PSelectorButtonRight = { 0 };			//1P向右切换按钮 位置
	POINT pos2PSelectorButtonLeft = { 0 };			//2P向左切换按钮 位置
	POINT pos2PSelectorButtonRight = { 0 };			//2P向右切换按钮 位置

	Animation animationPeaShooter;
	Animation animationSunFlower;
private:
	enum PlayerType { peaShooter, sunFlower, invalid };

	PlayerType playerType1P = peaShooter;
	PlayerType playerType2P = sunFlower;

	LPCTSTR strPeaShooterName = _T("恶霸劳付");
	LPCTSTR strSunFlowerName = _T("正义之宁");

	int selectorBackgroundScrollX = 0;

	bool isButton1PDownLeft = false;
	bool isButton1PDownRight = false;
	bool isButton2PDownLeft = false;
	bool isButton2PDownRight = false;
private:
	void outTextXYShaded(int x, int y, LPCTSTR text);
};
