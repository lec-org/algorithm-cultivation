#pragma once
#include "scene.h"
#include "sceneManager.h"
#include "util.h"
#include "platform.h"
#include <vector>
#include "statusBar.h"
#include "player.h"

extern Player* player1;									//���
extern Player* player2;
extern Player* newplayer;

extern IMAGE imgSky;									//���
extern IMAGE imgHills;									//ɽ��
extern IMAGE imgLargePlatform;							//ƽ̨
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
	virtual void enter();								//�������롪����ʼ�����г�������
	virtual void exit();								//�˳�


	virtual void receiveInput(const ExMessage& msg);	//����
	virtual void update(int runTimeMs);					//�������¡����ó������е�ʱ��
	virtual void render();								//��Ⱦ

	bool isSlideOutStarted = true;
private:
	//���ɽ�� ��������
	POINT posImgSky = { 0 };
	POINT posImgHills = { 0 };

	//״̬��
	StatusBar statusBar1P, statusBar2P;

	bool isGameOver = false;

	//���㶯��
	POINT posImgWinnerBar = { 0 };
	POINT posImgWinnerText = { 0 };

	int posXImgWinnerBarDst = 0;
	int posXImgWinnerTextDst = 0;

	Timer timerWinnerSlideIn, timerWinnerSlideOut;
	Timer timerNewPlayerDuration; // ���������������ʱ�䶨ʱ��

	float speedWinnerBar = 3.0;
	float speedWinnerText = 1.5;

	
};
