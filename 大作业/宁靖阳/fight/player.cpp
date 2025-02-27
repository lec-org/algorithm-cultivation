#include "player.h"

Player::Player(bool isFacingRight) : isFacingRight(isFacingRight) {

	currentAni = isFacingRight ? &animationIdleRight : &animationIdleLeft;

	timerAttckCd.setCallback([&] {
		isCanAttck = true;
		});
	timerAttckCd.setTimer(attackCd);
	timerAttckCd.setIsOneShot(true);

	//无敌定时器
	timerInvulnerable.setCallback([&] {
		isInvulnerable = false;
		});
	timerInvulnerable.setTimer(750);
	timerInvulnerable.setIsOneShot(true);

	//无敌动画切换
	timerInvulnerableBlink.setCallback([&] {
		isShowSketchFram = !isShowSketchFram;
		});
	timerInvulnerableBlink.setTimer(75);

	//粒子发射
	timerRunEffectGeneration.setTimer(75);
	timerRunEffectGeneration.setCallback([&] {

		Vector2 particlePosition;
		auto frame = atlasRunEffect.getImage(0);

		//粒子位于玩家水平中央
		particlePosition.x = position.x + (size.x - frame->getwidth()) / 2;
		//玩家脚底
		particlePosition.y = position.y + size.y - frame->getheight();

		particles.emplace_back(particlePosition, &atlasRunEffect, 45);

		});

	timerDieEffectGeneration.setTimer(35);
	timerDieEffectGeneration.setCallback([&] {

		Vector2 particlePosition;
		auto frame = atlasRunEffect.getImage(0);

		//粒子位于玩家水平中央
		particlePosition.x = position.x + (size.x - frame->getwidth()) / 2;
		//玩家脚底
		particlePosition.y = position.y + size.y - frame->getheight();

		particles.emplace_back(particlePosition, &atlasRunEffect, 150);

		});

	//跳跃和落地
	animationJumpEffect.setAtlas(&atlasJumpEffect);
	animationJumpEffect.setInterval(25);
	animationJumpEffect.setIsLoop(false);
	animationJumpEffect.setCallback([&] {
		isJumpEffectVisible = false;
		});

	animationLandEffect.setAtlas(&atlasLandEffect);
	animationLandEffect.setInterval(50);
	animationLandEffect.setIsLoop(false);
	animationLandEffect.setCallback([&] {
		isLandEffectVisible = false;
		});

	timerCursorVisibility.setTimer(2500);
	timerCursorVisibility.setIsOneShot(true);
	timerCursorVisibility.setCallback([&] {
		isCursorVisible = false;
		});

}

void Player::setId(const PlayerID& id) {
	this->id = id;
}

void Player::setPosition(float x, float y) {
	position.x = x, position.y = y;
}

const Vector2& Player::getPosition() const {

	return position;
}

const Vector2& Player::getSize() const {

	return size;
}

void Player::makeInvulnerable() {
	isInvulnerable = true;
	timerInvulnerable.reStart();
}

void Player::setHp(int val) {
	hp = val;
}

void Player::setMp(int val) {
	mp = val;
}

const int Player::getHp() const {
	return hp;
}

const int Player::getMp() const {
	return mp;
}

void Player::onRun(float distance) {
	if (isAttackingEx)
		return;
	position.x += distance;
	timerRunEffectGeneration.resume();
}

void Player::onJump() {

	if (velocity.y || isAttackingEx)
		return;

	//仅需更改速度即可
		//位置在moveAndCollide修改
	velocity.y += jumpVelocity;

	//跳跃
	isJumpEffectVisible = true;
	animationJumpEffect.reset();
	auto frame = animationJumpEffect.getFrame();
	//jump位于玩家中央
	positionJumpEffect.x = position.x + (size.x - frame->getwidth()) / 2;
	positionJumpEffect.y = position.y + size.x - frame->getheight();

}

void Player::onLand() {

	//落地
	isLandEffectVisible = true;
	animationLandEffect.reset();
	auto frame = animationLandEffect.getFrame();
	//jump位于玩家中央
	positionLandEffect.x = position.x + (size.x - frame->getwidth()) / 2;
	positionLandEffect.y = position.y + size.x - frame->getheight();
}

void Player::moveAndCollide(int time) {

	auto lastVelocityY = velocity.y;

	velocity.y += gravity * time;

	position += velocity * time;

	if (hp <= 0)
		return;

	//碰撞检测
		//玩家与平台
	if (velocity.y) {

		for (const auto& platform : platforms) {

			const auto& shape = platform.shape;

			bool isCollideX = max(position.x + size.x, shape.right) - min(position.x, shape.left) <= shape.right - shape.left + size.x;
			bool isCollideY = shape.y >= position.y && shape.y <= position.y + size.y;

			//对玩家坐标进行修正
			if (isCollideX && isCollideY) {

				//判断上一帧玩家是否在平台之上
				auto deltaY = velocity.y * time;
				auto lastY = position.y + size.y - deltaY;

				if (lastY <= shape.y) {

					position.y = shape.y - size.y;

					//平台上速度为0
					velocity.y = 0;

					if (lastVelocityY)
						onLand();

					break;
				}

			}
		}
	}
	//玩家与子弹
	if (!isInvulnerable) {
		for (const auto& bullet : bullets) {

			if (!bullet->getValid() || bullet->getCollideTarget() != id)
				continue;

			if (bullet->checkCollision(position, size)) {

				makeInvulnerable();

				bullet->onCollide();

				bullet->setValid(false);

				hp -= bullet->getDamage();

				//玩家到子弹的向量
				lastHurtDirection = bullet->getPosition() - position;

				if (hp <= 0) {

					velocity.x = lastHurtDirection.x < 0 ? 0.35 : -0.35;
					velocity.y = -1.0;
				}
			}
		}
	}


}

void Player::receiveInput(const ExMessage& msg) {
	switch (msg.message) {
	case WM_KEYDOWN:

		switch (id) {
		case P1:
			switch (msg.vkcode) {
				//'A'
			case 0x41:
				isLeftKeyDown = true;
				break;
				//'D'
			case 0x44:
				isRightKeyDown = true;
				break;
				//'W'
			case 0x57:
				onJump();
				break;
				//'J'
			case 0x4a:
				if (isCanAttck) {
					onAttack();
					isCanAttck = !isCanAttck;
					timerAttckCd.reStart();
				}
				break;
				//'K'
			case 0x4b:
				if (mp >= 100) {
					onAttackEx();
					mp = 0;
				}
				break;
				//'E'
				/*case 0x45:
					if (mp >= 100) {
						trans();
						mp = 0;
					}
					break;*/
			default:
				break;
			}
			break;
		case P2:
			switch (msg.vkcode) {
				//<
			case VK_LEFT:
				isLeftKeyDown = true;
				break;
				//>
			case VK_RIGHT:
				isRightKeyDown = true;
				break;
				//'↑'
			case VK_UP:
				onJump();
				break;
				//'.'
			case 0x6e:
				if (isCanAttck ) {
					onAttack();
					isCanAttck = !isCanAttck;
					timerAttckCd.reStart();
				}
				break;
				//'2'
			case 0xd:
				if (mp >= 100) {
					onAttackEx();
					mp = 0;
				}
				break;
				/*case VK_ADD:
					if (mp >= 100) {
						trans();
						mp = 0;
					}
					break;*/
			default:
				break;
			}
			break;
		case P3:
			switch (msg.vkcode) {
				//'A'
			case 0x41:
				isLeftKeyDown = true;
				break;
				//'D'
			case 0x44:
				isRightKeyDown = true;
				break;
				//'W'
			case 0x57:
				onJump();
				break;
				//'J'
			case 0x4a:
				if (isCanAttck) {
					onAttack();
					isCanAttck = !isCanAttck;
					timerAttckCd.reStart();
				}
				break;
				//'K'
			case 0x4b:
				if (mp >= 100) {
					onAttackEx();
					mp = 0;
				}
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:

		switch (id) {
		case P1:
			switch (msg.vkcode) {
				//'A'
			case 0x41:
				isLeftKeyDown = false;
				break;
				//'D'
			case 0x44:
				isRightKeyDown = false;
				break;
			default:
				break;
			}
			break;
		case P2:
			switch (msg.vkcode) {
				//<
			case VK_LEFT:
				isLeftKeyDown = false;
				break;
				//>
			case VK_RIGHT:
				isRightKeyDown = false;
				break;
			default:
				break;
			}
			break;
		case P3:
			switch (msg.vkcode) {
				//'A'
			case 0x41:
				isLeftKeyDown = false;
				break;
				//'D'
			case 0x44:
				isRightKeyDown = false;
				break;
			default:
				break;
			}

			break;
		default:
			break;
		}
	}
}



void Player::update(int time) {

	//direction:——玩家是否按键: 0——没有按键
	int direction = isRightKeyDown - isLeftKeyDown;

	//按键
	if (direction) {
		//特殊攻击时不允许转向
		if (!isAttackingEx)
			isFacingRight = direction > 0;	//根据按键判断当前朝向
		//根据当前朝向 选择 动画
		currentAni = isFacingRight ? &animationRunRight : &animationRunLeft;

		//水平方向移动
		auto distance = direction * runVelocity * time;
		onRun(distance);
	}
	else {
		currentAni = isFacingRight ? &animationIdleRight : &animationIdleLeft;
		timerRunEffectGeneration.pause();
	}


	if (isAttackingEx)
		currentAni = isFacingRight ? &animationAttackExRight : &animationAttackExLeft;

	if (hp <= 0)
		currentAni = lastHurtDirection.x < 0 ? &animationDieLeft : &animationDieRight;

	//更新动画
	currentAni->update(time);
	animationJumpEffect.update(time);
	animationLandEffect.update(time);

	//更新定时器
	timerAttckCd.update(time);

	timerInvulnerable.update(time);

	timerInvulnerableBlink.update(time);

	timerCursorVisibility.update(time);

	//粒子
		//生成粒子
	timerRunEffectGeneration.update(time);
	if (hp <= 0)
		timerDieEffectGeneration.update(time);

	//更新粒子
	particles.erase(std::remove_if(particles.begin(), particles.end(), [](const Particle& particle) {

		return !particle.checkIsValid();
		}), particles.end());

	for (auto& particle : particles)
		particle.update(time);


	//剪影
	if (isShowSketchFram)
		sketchImage(currentAni->getFrame(), &imgSketch);


	//重力模拟 和 碰撞检测
	moveAndCollide(time);
}

void Player::render() {

	if (isJumpEffectVisible)
		animationJumpEffect.render(positionJumpEffect.x, positionJumpEffect.y);

	if (isLandEffectVisible)
		animationLandEffect.render(positionLandEffect.x, positionLandEffect.y);

	//让粒子渲染在玩家身后
	for (const Particle& particle : particles)
		particle.render();

	if (hp > 0 && isInvulnerable && isShowSketchFram)
		putImageAlpha(position.x, position.y, &imgSketch);
	else
		currentAni->render(position.x, position.y);


	if (isCursorVisible) {

		switch (id) {
		case P1:
			//玩家头顶居中
			putImageAlpha(position.x + (size.x - img1PCursor.getwidth()) / 2, position.y - img1PCursor.getheight(),
				&img1PCursor);
			break;
		case P2:
			putImageAlpha(position.x + (size.x - img2PCursor.getwidth()) / 2, position.y - img2PCursor.getheight(),
				&img2PCursor);
			break;
		/*case P3:
			putImageAlpha(position.x + (size.x - img3PCursor.getwidth()) / 2, position.y - img3PCursor.getheight(),
				&img3PCursor);
			break;*/
		default:
			break;
		}

	}

	if (isDebug) {

		setlinecolor(RGB(0, 125, 255));

		rectangle(position.x, position.y, position.x + size.x, position.y + size.y);
	}
}

