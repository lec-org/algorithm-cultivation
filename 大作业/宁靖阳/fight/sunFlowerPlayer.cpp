#include "sunFlowerPlayer.h"

SunFlowerPlayer::SunFlowerPlayer(bool isFacingRight) :Player(isFacingRight) {

	//初始化动画
	animationIdleLeft.setAtlas(&atlasSunFlowerIdleLeft);
	animationIdleRight.setAtlas(&atlasSunFlowerIdleRight);
	animationRunLeft.setAtlas(&atlasSunFlowerRunLeft);
	animationRunRight.setAtlas(&atlasSunFlowerRunRight);

	animationAttackExLeft.setAtlas(&atlasSunFlowerAttackExLeft);
	animationAttackExRight.setAtlas(&atlasSunFlowerAttackExRight);
	animationSunText.setAtlas(&atlasSunText);

	animationDieLeft.setAtlas(&atlasSunFlowerDieLeft);
	animationDieRight.setAtlas(&atlasSunFlowerDieRight);

	animationIdleLeft.setInterval(75);
	animationIdleRight.setInterval(75);
	animationRunLeft.setInterval(75);
	animationRunRight.setInterval(75);

	animationAttackExLeft.setInterval(100);
	animationAttackExRight.setInterval(100);
	animationSunText.setInterval(100);

	animationDieLeft.setInterval(150);
	animationDieRight.setInterval(150);

	animationAttackExLeft.setIsLoop(false);
	animationAttackExRight.setIsLoop(false);
	animationSunText.setIsLoop(false);

	animationDieLeft.setIsLoop(false);
	animationDieRight.setIsLoop(false);

	//设置动画回调
	animationAttackExLeft.setCallback([&] {
		isAttackingEx = false;
		isSunTextVisible = false;
		});
	animationAttackExRight.setCallback([&] {
		isAttackingEx = false;
		isSunTextVisible = false;
		});

	size.x = 96, size.y = 96;

	attackCd = 250;
}

void SunFlowerPlayer::update(int time) {
	Player::update(time);

	if (isSunTextVisible)
		animationSunText.update(time);

}


void SunFlowerPlayer::render() {
	Player::render();

	if (isSunTextVisible) {

		Vector2 textPosition;

		auto frame = animationSunText.getFrame();

		textPosition.x = position.x - (size.x - frame->getwidth()) / 2;
		textPosition.y = position.y - frame->getheight();

		animationSunText.render(textPosition.x, textPosition.y);
	}
}

void SunFlowerPlayer::onAttack() {
	auto bullet = new SunBullet;

	Vector2 bulletPosition;

	auto bulletSize = bullet->getSize();

	//设置子弹位置为向日葵头部
	bulletPosition.x = position.x + (size.x - bulletSize.x) / 2;
	bulletPosition.y = position.y;

	//设置子弹速度
	bullet->setPosition(bulletPosition.x, bulletPosition.y);
	bullet->setVelocity(isFacingRight ? velocitySun.x : -velocitySun.x, velocitySun.y);

	//设置子弹的碰撞目标
	bullet->setCollideTarget(id == P1 ? P2 : P1);

	//设置子弹回调
	bullet->setCallback([&] {mp += 35; });

	bullets.push_back(bullet);
}

//void SunFlowerPlayer::trans() {
//
//	//if (mp > 100) {
//	//	// 创建 TransPlayer 实例
//	//	TransPlayer* transPlayer = new TransPlayer(isFacingRight);
//	//	transPlayer ->setId(id);
//	//	transPlayer ->setPosition(position.x, position.y);
//
//	//	// 更新全局指针
//	//	if (this == player1) {
//	//		player1 = transPlayer;
//	//	}
//	//	else if (this == player2) {
//	//		player2= transPlayer;
//	//	}
//
//	//	// 释放当前实例
//	//	delete this;
//	//}
//}

//void SunFlowerPlayer::trans() {
//	if (mp >= 100) {
//		std::cout << "Transformin";
//		// 创建 TransPlayer 实例
//		TransPlayer* transPlayer = new TransPlayer(isFacingRight);
//		transPlayer->setId(id);
//		transPlayer->setPosition(position.x, position.y);
//		transPlayer->setHp(hp);
//
//		// 更新全局指针
//		if (this == player1) {
//			player1 = transPlayer;
//		}
//		else if (this == player2) {
//			player2 = transPlayer;
//		}
//
//		// 释放当前实例
//		delete this;
//		std::cout << 1;
//	}
//}

//void SunFlowerPlayer::trans()
//{	
//	/*if (this == player1) {
//		player1->setPosition(-100, -100);
//	}
//	else if (this == player2) {
//		player2->setPosition(-100, -100);
//	}
//	TransPlayer* transPlayer = new TransPlayer(isFacingRight);
//	transPlayer->setId(id);
//	transPlayer->setPosition(position.x, position.y);
//	transPlayer->setHp(hp);*/
//}

void SunFlowerPlayer::onAttackEx() {
	isAttackingEx = true;
	isSunTextVisible = true;

	animationSunText.reset();

	isFacingRight ? animationAttackExRight.reset() : animationAttackExLeft.reset();

	auto bullet = new SunBulletEx;
	auto targetPlayer = id == P1 ? player2 : player1;

	Vector2 bulletPosition, bulletVelocity;

	auto bulletSize = bullet->getSize();
	auto targetSize = targetPlayer->getSize();
	auto targetPosition = targetPlayer->getPosition();


	//子弹位于玩家头顶中心
	bulletPosition.x = targetPosition.x + (targetSize.x - bulletSize.x) / 2;
	bulletPosition.y = -size.y;
	bulletVelocity.x = 0;
	bulletVelocity.y = speedSunEx;

	bullet->setPosition(bulletPosition.x, bulletPosition.y);
	bullet->setVelocity(bulletVelocity.x, bulletVelocity.y);

	//设置子弹的碰撞目标
	bullet->setCollideTarget(id == P1 ? P2 : P1);

	//设置子弹回调
	bullet->setCallback([&] {mp += 50; });

	bullets.push_back(bullet);

	mciSendString(_T("play sunText from 0"), nullptr, 0, nullptr);
}



