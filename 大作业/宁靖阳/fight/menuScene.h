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
	virtual void enter();								//进入
	virtual void exit();								//退出

	virtual void receiveInput(const ExMessage& msg);	//接收输入
	virtual void update(int runTimeMs);					//场景更新——让场景运行的时间
	virtual void render();								//渲染

private:
	Animation aniPeaShooterRunRight;
};
