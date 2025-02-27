#pragma once
#include <graphics.h>

/*
����
	�˵�
	��ɫѡ��
	��Ϸ
*/

class Scene {
public:
	virtual ~Scene();
public:
	virtual void enter();								//�������롪�����𳡾�������Ϸ����ĳ�ʼ��
	virtual void exit();								//�����˳�

	virtual void receiveInput(const ExMessage& msg);	//��������
	virtual void update(int runTimeMs);					//�������¡����ó������е�ʱ��
	virtual void render();								//������Ⱦ
};

