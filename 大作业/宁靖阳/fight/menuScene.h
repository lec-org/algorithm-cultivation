#pragma once
#include "scene.h"
#include "sceneManager.h"

#include "atlas.h"
#include "animation.h"
#include "camera.h"
#include "timer.h"

extern SceneManager sceneManager;
extern Atlas atlasPeaShooterRunRight;
extern IMAGE imgMenuBackground;

class MenuScene :public Scene {

public:
	virtual void enter();								//����
	virtual void exit();								//�˳�

	virtual void receiveInput(const ExMessage& msg);	//��������
	virtual void update(int runTimeMs);					//�������¡����ó������е�ʱ��
	virtual void render();								//��Ⱦ

private:
	Animation aniPeaShooterRunRight;
};
