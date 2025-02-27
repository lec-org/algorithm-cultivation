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
	void setSceneManager(Scene* scene);			//��ʼ������
public:
	void switchTo(SceneType type);				//�����л��ɳ������жϡ��������ڲ�Ҫ����������������
public:
	void receiveInput(const ExMessage& msg);	//����
	void update(int runTimeMs);					//���������¡����ù��������е�ʱ��
	void render();								//��Ⱦ
};
