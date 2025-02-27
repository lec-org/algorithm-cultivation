#include "peaShooterPlayer.h"
#include "peaBullet.h"
#include "newPlayer.h"
#include <chrono>
std::chrono::steady_clock::time_point transStartTime;

PeaShooterPlayer::PeaShooterPlayer(bool isFacingRight) :Player(isFacingRight) {

	//��ʼ������
	animationIdleLeft.setAtlas(&atlasPeaShooterIdleLeft);
	animationIdleRight.setAtlas(&atlasPeaShooterIdleRight);
	animationRunLeft.setAtlas(&atlasPeaShooterRunLeft);
	animationRunRight.setAtlas(&atlasPeaShooterRunRight);
	animationAttackExLeft.setAtlas(&atlasPeaShooterAttackExLeft);
	animationAttackExRight.setAtlas(&atlasPeaShooterAttackExRight);

	animationDieLeft.setAtlas(&atlasPeaShooterDieLeft);
	animationDieRight.setAtlas(&atlasPeaShooterDieRight);

	animationIdleLeft.setInterval(75);
	animationIdleRight.setInterval(75);
	animationRunLeft.setInterval(75);
	animationRunRight.setInterval(75);
	animationAttackExLeft.setInterval(75);
	animationAttackExRight.setInterval(75);

	animationDieLeft.setInterval(150);
	animationDieRight.setInterval(150);

	animationDieLeft.setIsLoop(false);
	animationDieRight.setIsLoop(false);

	size.x = 96, size.y = 96;

	//���ö�ʱ��
	timerAttackEx.setCallback([&] {isAttackingEx = false; });
	timerAttackEx.setTimer(attackExDuration);
	timerAttackEx.setIsOneShot(true);

	timerSpawnPeaEx.setCallback([&] {spawnPeaBullet(speedPeaEx); });
	timerSpawnPeaEx.setTimer(100);

	//�չ�cd
	attackCd = 100;
}

void PeaShooterPlayer::update(int time) {
	Player::update(time);

	if (isAttackingEx) {
		Camera::getCamera().shake(5, 100);

		timerAttackEx.update(time);
		timerSpawnPeaEx.update(time);
	}
}

void PeaShooterPlayer::receiveInput(const ExMessage& msg)
{
	Player::receiveInput(msg);
	if (msg.message == WM_KEYDOWN) {
		switch (msg.vkcode) {
		case 0x45: // 'E' ��
			if (mp >= 100) {
				trans();
				mp = 0;
			}
		default:
			break;
		}
	}
}

//void PeaShooterPlayer::receiveInput(const ExMessage& msg) {
//	// �ȵ��û���� receiveInput ����������ͨ�ð����¼�
//	Player::receiveInput(msg);
//
//	// ���� PeaShooter �ض��İ����¼�
//	if (msg.message == WM_KEYDOWN) {
//		switch (msg.vkcode) {
//		case 0x45: // 'E' ��
//			if (mp >= 100) {
//				mp
//					= 0;
//				trans();
//			}
//			break;
//		default:
//			break;
//		}
//	}
//}

void PeaShooterPlayer::onAttack() {

	spawnPeaBullet(speedPea);

	switch (rand() % 2) {

	case 0:
		mciSendString(_T("play peaShoot1 from 0"), nullptr, 0, nullptr);
		break;
	case 1:
		mciSendString(_T("play peaShoot2 from 0"), nullptr, 0, nullptr);
		break;
	default:
		break;
	}

}

void PeaShooterPlayer::onAttackEx() {

	isAttackingEx = true;
	timerAttackEx.reStart();

	isFacingRight ? animationAttackExRight.reset() : animationAttackExLeft.reset();

	mciSendString(_T("play peaShootEx from 0"), nullptr, 0, nullptr);
}

void PeaShooterPlayer::trans() {

	isSlideOutStarted = true;
	/*Vector2 originalPosition = this->getPosition();
    bool isFacingRight = this->isFacingRight;*/
	/*newplayer->setPosition(originalPosition.x, originalPosition.y);*/
	/*newplayer->setInvincibleTime(1000);*/
	newplayer->setPosition(200, 50);
	newplayer->isFacingRight = true;
	// newplayer �̳�ԭ��ɫ��Ѫ��
	newplayer->setHp(this->getHp());
	if (this == player1) {
		player1 = newplayer;
		isSlideOutStarted = false;
		/*isSlideOutStarted1 = false;
		isSlideOutStarted2 = true;*/
	}
	else if (this == player2) {
		player2 = newplayer;
		isSlideOutStarted = false;
		/*isSlideOutStarted1 = false;
		isSlideOutStarted2 = true;*/

	}

	this->setPosition(-100, -100);
	newplayer->setId(this->id);	
	
}

void PeaShooterPlayer::spawnPeaBullet(float speed) {

	auto bullet = new PeaBullet;

	Vector2 bulletPosition, bulletVelocity;

	auto bulletSize = bullet->getSize();

	//�����ӵ�λ��Ϊ�㶹ͷ��
	bulletPosition.x = isFacingRight ? position.x + size.x - bulletSize.x / 2 :
		position.x - bulletSize.x / 2;

	bulletPosition.y = position.y;

	//�����ӵ��ٶ�
	bulletVelocity.x = isFacingRight ? speed : -speed;
	bulletVelocity.y = 0;

	bullet->setPosition(bulletPosition.x, bulletPosition.y);
	bullet->setVelocity(bulletVelocity.x, bulletVelocity.y);

	//�����ӵ�����ײĿ��
	bullet->setCollideTarget(id == P1 ? P2 : P1);

	//�����ӵ��ص�
	bullet->setCallback([&] {mp += 25; });

	bullets.push_back(bullet);

}


