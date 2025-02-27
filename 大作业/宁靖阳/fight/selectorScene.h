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

//VS������
extern IMAGE imgVS;
//���
extern IMAGE img1P;
extern IMAGE img2P;
//��λ����
extern IMAGE img1PDesc;
extern IMAGE img2PDesc;
//����
extern IMAGE imgSelectorBackground;
//��ʾ��Ϣ
extern IMAGE imgSelectorTip;
//Ĺ��
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
	void enter() override;								//��������
	void exit() override;								//�����˳�

	void receiveInput(const ExMessage& msg) override;	//������������
	void update(int runTimeMs) override;				//�������¡����ó������е�ʱ��
	void render() override;								//������Ⱦ

private:
	POINT posImgVS = { 0 };							//VS������ λ��
	POINT posImgTip = { 0 };						//��ʾ��Ϣ λ��
	POINT posImg1P = { 0 };							//1P λ��
	POINT posImg2P = { 0 };							//2P λ��

	POINT posImg1PDesc = { 0 };						//1P��λ���� λ��
	POINT posImg2PDesc = { 0 };						//2P��λ���� λ��
	POINT posImg1PName = { 0 };						//1P���� λ��
	POINT posImg2PName = { 0 };						//2P���� λ��

	POINT posAnimation1P = { 0 };					//1P��ɫ λ��
	POINT posAnimation2P = { 0 };					//2P��ɫ λ��

	POINT posImg1PGravestone = { 0 };				//1PĹ�� λ��
	POINT posImg2PGravestone = { 0 };				//2PĹ�� λ��

	POINT pos1PSelectorButtonLeft = { 0 };			//1P�����л���ť λ��
	POINT pos1PSelectorButtonRight = { 0 };			//1P�����л���ť λ��
	POINT pos2PSelectorButtonLeft = { 0 };			//2P�����л���ť λ��
	POINT pos2PSelectorButtonRight = { 0 };			//2P�����л���ť λ��

	Animation animationPeaShooter;
	Animation animationSunFlower;
private:
	enum PlayerType { peaShooter, sunFlower, invalid };

	PlayerType playerType1P = peaShooter;
	PlayerType playerType2P = sunFlower;

	LPCTSTR strPeaShooterName = _T("����͸�");
	LPCTSTR strSunFlowerName = _T("����֮��");

	int selectorBackgroundScrollX = 0;

	bool isButton1PDownLeft = false;
	bool isButton1PDownRight = false;
	bool isButton2PDownLeft = false;
	bool isButton2PDownRight = false;
private:
	void outTextXYShaded(int x, int y, LPCTSTR text);
};
