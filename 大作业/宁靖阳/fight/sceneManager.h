#pragma once
#include "scene.h"

extern Scene* menuScene;
extern Scene* gameScene;
extern Scene* selectorScene;

class SceneManager {
private:
	Scene* currentScene;
public:
	enum SceneType { Menu, Selector, Game };
public:
	void setSceneManager(Scene* scene);			//初始化设置
public:
	void switchTo(SceneType type);				//场景切换由场景来判断——场景内不要有其他场景的引用
public:
	void receiveInput(const ExMessage& msg);	//输入
	void update(int runTimeMs);					//管理器更新——让管理器运行的时间
	void render();								//渲染
};
