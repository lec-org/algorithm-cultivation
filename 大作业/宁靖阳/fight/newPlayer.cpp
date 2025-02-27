#include "newPlayer.h"
#include "trans.h"
#include "peaShooterPlayer.h"

newPlayer::newPlayer(bool isFacingRight) :Player(isFacingRight) {

	//初始化动画
	animationIdleLeft.setAtlas(&atlasnewPlayerIdleLeft);
	animationIdleRight.setAtlas(&atlasnewPlayerIdleRight);
	animationRunLeft.setAtlas(&atlasnewPlayerRunLeft);
	animationRunRight.setAtlas(&atlasnewPlayerRunRight);
	animationAttackExLeft.setAtlas(&atlasnewPlayerAttackExLeft);
	animationAttackExRight.setAtlas(&atlasnewPlayerAttackExRight);
	//animationtransText.setAtlas(&atlastransEx); // 注意此处！！！！！！！

	animationDieLeft.setAtlas(&atlasnewPlayerDieLeft);
	animationDieRight.setAtlas(&atlasnewPlayerDieRight);

	animationIdleLeft.setInterval(75);
	animationIdleRight.setInterval(75);
	animationRunLeft.setInterval(75);
	animationRunRight.setInterval(75);
	animationAttackExLeft.setInterval(75);
	animationAttackExRight.setInterval(75);
	animationtransText.setInterval(100);

	animationDieLeft.setInterval(150);
	animationDieRight.setInterval(150);

	animationDieLeft.setIsLoop(false);
	animationDieRight.setIsLoop(false);
	animationAttackExLeft.setIsLoop(false);
	animationAttackExRight.setIsLoop(false);
	animationtransText.setIsLoop(false);

	size.x = 130, size.y = 150;

	//设置定时器
	timerAttackEx.setCallback([&] {isAttackingEx = false; });
	timerAttackEx.setTimer(attackExDuration);
	timerAttackEx.setIsOneShot(true);

	timerSpawnPeaEx.setCallback([&] {spawnPeaBullet(speedPeaEx); });
	timerSpawnPeaEx.setTimer(100);

	//普攻cd
	attackCd = 50;
}

//void newPlayer::receiveInput(const ExMessage& msg) {
//	Player::receiveInput(msg);
//	// 获取当前位置
//	Vector2 currentPosition = getPosition();
//
//	// 判断是否在地图内，假设地图范围是 x: [0, getwidth()]，y: [0, getheight()]
//	bool isInMap = currentPosition.x >= 0 && currentPosition.x <= getwidth() &&
//		currentPosition.y >= 0 && currentPosition.y <= getheight();
//
//	if (msg.message == WM_KEYDOWN) {
//		if (msg.vkcode == 'J' && isInMap) {  // 假设 J 键是发动普通攻击的按键
//			// 发动普通攻击的代码
//			onAttack();
//		}
//	}
//}


void newPlayer::update(int time) {
	Player::update(time);

	if (istransTextVisible)
		animationtransText.update(time);

	if (isAttackingEx) {
		Camera::getCamera().shake(5, 100);

		timerAttackEx.update(time);
		timerSpawnPeaEx.update(time);
	}
}

void newPlayer::onAttack() {
	
		//isAttackingEx = true;
		//istransTextVisible = true;

		//animationtransText.reset();

		//isFacingRight ? animationAttackExRight.reset() : animationAttackExLeft.reset();

		//auto bullet = new transEx;
		//auto targetPlayer = id == P2 ? player1 : player2;

		//Vector2 bulletPosition, bulletVelocity;

		//auto bulletSize = bullet->getSize();
		//auto targetSize = targetPlayer->getSize();
		//auto targetPosition = targetPlayer->getPosition();


		////子弹位于玩家头顶中心
		//bulletPosition.x = targetPosition.x + (targetSize.x - bulletSize.x) / 2;
		//bulletPosition.y = -size.y;
		//bulletVelocity.x = 0;
		//bulletVelocity.y = speedtransEx;

		//bullet->setPosition(bulletPosition.x, bulletPosition.y);
		//bullet->setVelocity(bulletVelocity.x, bulletVelocity.y);

		////设置子弹的碰撞目标
		//bullet->setCollideTarget(id == P1 ? P2 : P1);

		////设置子弹回调
		//bullet->setCallback([&] {mp += 50; });

		//bullets.push_back(bullet);

		//mciSendString(_T("play sunText from 0"), nullptr, 0, nullptr);
	


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

void newPlayer::onAttackEx() {


	isAttackingEx = true;
	timerAttackEx.reStart();
	isFacingRight ? animationAttackExRight.reset() : animationAttackExLeft.reset();

	mciSendString(_T("play peaShootEx from 0"), nullptr, 0, nullptr);
}

void newPlayer::spawnPeaBullet(float speed) {

	auto bullet = new transBullet;

	Vector2 bulletPosition, bulletVelocity;

	auto bulletSize = bullet->getSize();

	//设置子弹位置为豌豆头部
	bulletPosition.x = isFacingRight ? position.x + size.x - bulletSize.x / 2 + 30:
		position.x - bulletSize.x / 2 + 30;

	bulletPosition.y = position.y + 30;

	//设置子弹速度
	bulletVelocity.x = isFacingRight ? speed : -speed;
	bulletVelocity.y = 0;

	bullet->setPosition(bulletPosition.x, bulletPosition.y);
	bullet->setVelocity(bulletVelocity.x, bulletVelocity.y);

	//设置子弹的碰撞目标
	bullet->setCollideTarget(id == P1 ? P2 : P1);

	//设置子弹回调
	bullet->setCallback([&] {mp += 25; });

	bullets.push_back(bullet);

}



