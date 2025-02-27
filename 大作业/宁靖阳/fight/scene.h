#pragma once
#include <graphics.h>

/*
场景
	菜单
	角色选择
	游戏
*/

class Scene {
public:
	virtual ~Scene();
public:
	virtual void enter();								//场景进入——负责场景所有游戏对象的初始化
	virtual void exit();								//场景退出

	virtual void receiveInput(const ExMessage& msg);	//场景接收
	virtual void update(int runTimeMs);					//场景更新——让场景运行的时间
	virtual void render();								//场景渲染
};

