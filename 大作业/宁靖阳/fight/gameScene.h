#pragma once
#include "scene.h"
#include "sceneManager.h"
#include "util.h"
#include "platform.h"
#include <vector>
#include "statusBar.h"
#include "player.h"

extern Player* player1;									//玩家
extern Player* player2;
extern Player* newplayer;

extern IMAGE imgSky;									//天空
extern IMAGE imgHills;									//山脉
extern IMAGE imgLargePlatform;							//平台
extern IMAGE imgSmallPlatform;

extern IMAGE img1PWinner;
extern IMAGE img2PWinner;
extern IMAGE imgWinnerBar;

extern IMAGE* imgPlayer1Avatar;
extern IMAGE* imgPlayer2Avatar;

extern SceneManager sceneManager;
extern std::vector<Platform> platforms;

class GameScene :public Scene {

public:
	virtual void enter();								//场景进入——初始化所有场景对象
	virtual void exit();								//退出


	virtual void receiveInput(const ExMessage& msg);	//输入
	virtual void update(int runTimeMs);					//场景更新——让场景运行的时间
	virtual void render();								//渲染

	bool isSlideOutStarted = true;
private:
	//天空山脉 世界坐标
	POINT posImgSky = { 0 };
	POINT posImgHills = { 0 };

	//状态栏
	StatusBar statusBar1P, statusBar2P;

	bool isGameOver = false;

	//结算动画
	POINT posImgWinnerBar = { 0 };
	POINT posImgWinnerText = { 0 };

	int posXImgWinnerBarDst = 0;
	int posXImgWinnerTextDst = 0;

	Timer timerWinnerSlideIn, timerWinnerSlideOut;
	Timer timerNewPlayerDuration; // 新增：新人物出现时间定时器

	float speedWinnerBar = 3.0;
	float speedWinnerText = 1.5;

	
};
