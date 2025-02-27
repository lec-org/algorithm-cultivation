#pragma once
#include <functional>

class Timer {
public:
	void setTimer(int timerMs);								//���ö�ʱʱ��
	void setIsOneShot(bool isOneShot);						//���ö�ʱ���� �Ƿ�ֻ����һ��
	void setCallback(const std::function<void()>& cb);		//���ö�ʱ����
public:
	void reStart();											//���¼�ʱ
	void update(int runTimeMs);								//�ö�ʱ������runTimeMs
public:
	void setTimer(int timerMs, bool isOneShot, const std::function<void()>& cb);
public:
	void pause();
	void resume();							//�ָ�����

private:
	int timer = 0;							//��ʱʱ��
	int time = 0;							//��ʱ���Ѿ�������ʱ��

	bool isPause = false;
	bool isOneShot = false;					//�����Ƿ�ֻ����һ��
	bool isShotted = false;					//�����Ƿ��Ѵ���

	std::function<void()> callback;
};
