#include "gameScene.h"
#include <iostream>
#include "sceneManager.h"
#include "newPlayer.h"
#include "peaShooterPlayer.h"

void GameScene::enter() {
	
	//结算初始化
	isGameOver = false, isSlideOutStarted = true;

	posImgWinnerBar.x = -imgWinnerBar.getwidth();
	posImgWinnerBar.y = (getheight() - imgWinnerBar.getheight()) / 2;
	posXImgWinnerBarDst = (getwidth() - imgWinnerBar.getwidth()) / 2;

	posImgWinnerText.x = posImgWinnerBar.x;
	posImgWinnerText.y = (getheight() - img1PWinner.getheight()) / 2;
	posXImgWinnerTextDst = (getwidth() - img1PWinner.getwidth()) / 2;

	timerWinnerSlideIn.reStart();
	timerWinnerSlideIn.setIsOneShot(true);
	timerWinnerSlideIn.setTimer(2500);
	timerWinnerSlideIn.setCallback([&] {
		isSlideOutStarted = true;
		});

	timerWinnerSlideOut.reStart();
	timerWinnerSlideOut.setIsOneShot(true);
	timerWinnerSlideOut.setTimer(1000);
	timerWinnerSlideOut.setCallback([&] {
		sceneManager.switchTo(SceneManager::Menu);
		});

	//// 初始化新人物出现时间定时器
	//timerNewPlayerDuration.setIsOneShot(true);
	//timerNewPlayerDuration.setTimer(30000); // 30 秒
	//timerNewPlayerDuration.setCallback([&] {
	//	if (!isGameOver) {
	//		//newplayer->die(); // 触发新人物死亡动画
	//		//winner = player1 == newplayer ? P2 : P1; // 判定对方赢
	//		//isGameOver = true;
	//	}
	//	});

	//设置状态条头像
	statusBar1P.setAvatar(imgPlayer1Avatar);
	statusBar2P.setAvatar(imgPlayer2Avatar);

	statusBar1P.setPosition(235, 625);
	statusBar2P.setPosition(675, 625);

	//初始化玩家位置
	player1->setPosition(200, 50);
	player2->setPosition(975, 50);
	newplayer->setPosition(-100, -100);

	int xWindow = getwidth(), yWindow = getheight();

	

	//窗口居中
	posImgSky.x = (xWindow - imgSky.getwidth()) / 2,
		posImgSky.y = (yWindow - imgSky.getheight()) / 2;

	posImgHills.x = (xWindow - imgHills.getwidth()) / 2,
		posImgHills.y = (yWindow - imgHills.getheight()) / 2;

	//初始化平台
	platforms.resize(4);

	//large
	auto& largePlatform = platforms[0];

	largePlatform.img = &imgLargePlatform;
	largePlatform.renderPos.x = 122, largePlatform.renderPos.y = 455;

	//碰撞箱 一般 位于 渲染图内部偏上
	largePlatform.shape.left = largePlatform.renderPos.x + 30,
		largePlatform.shape.right = largePlatform.renderPos.x + largePlatform.img->getwidth() - 30,
		largePlatform.shape.y = largePlatform.renderPos.y + 60;

	//small1
	auto& smallPlatform1 = platforms[1];

	smallPlatform1.img = &imgSmallPlatform;
	smallPlatform1.renderPos.x = 175, smallPlatform1.renderPos.y = 360;

	smallPlatform1.shape.left = smallPlatform1.renderPos.x + 40,
		smallPlatform1.shape.right = smallPlatform1.renderPos.x + smallPlatform1.img->getwidth() - 40,
		smallPlatform1.shape.y = smallPlatform1.renderPos.y + smallPlatform1.img->getheight() / 2;

	//small2
	auto& smallPlatform2 = platforms[2];

	smallPlatform2.img = &imgSmallPlatform;
	smallPlatform2.renderPos.x = 855, smallPlatform2.renderPos.y = 360;

	smallPlatform2.shape.left = smallPlatform2.renderPos.x + 40,
		smallPlatform2.shape.right = smallPlatform2.renderPos.x + smallPlatform2.img->getwidth() - 40,
		smallPlatform2.shape.y = smallPlatform2.renderPos.y + smallPlatform2.img->getheight() / 2;

	//small3
	auto& smallPlatform3 = platforms[3];

	smallPlatform3.img = &imgSmallPlatform;
	smallPlatform3.renderPos.x = 515, smallPlatform3.renderPos.y = 225;

	smallPlatform3.shape.left = smallPlatform3.renderPos.x + 40,
		smallPlatform3.shape.right = smallPlatform3.renderPos.x + smallPlatform3.img->getwidth() - 40,
		smallPlatform3.shape.y = smallPlatform3.renderPos.y + smallPlatform3.img->getheight() / 2;

	mciSendString(_T("play bgmGame repeat from 0"), nullptr, 0, nullptr);
}

void GameScene::exit() {
	delete player1;
	delete player2;
	delete newplayer;

	player1 = nullptr, player2 = nullptr;
	newplayer = nullptr;

	//不确定是否需要delete
	bullets.clear();

	Camera::getCamera().reset();
}

void GameScene::receiveInput(const ExMessage& msg) {

	player1->receiveInput(msg);
	player2->receiveInput(msg);
	newplayer->receiveInput(msg);
	switch (msg.message) {
	case WM_KEYUP:
		//q
		if (msg.vkcode == 0x51)
			isDebug = !isDebug;

		break;
	default:
		break;
	}
}

//void GameScene::receiveInput(const ExMessage& msg) {
//	if (msg.message == WM_KEYDOWN) {
//		if (msg.vkcode == VK_SPACE) {
//			PeaShooterPlayer* peaShooter = dynamic_cast<PeaShooterPlayer*>(player1); // 假设 player1 是 PeaShooterPlayer
//			if (peaShooter && peaShooter->getMp() > 100 && !isCharacterSwitched) {
//				// 保存原角色位置
//				Vector2 originalPosition = peaShooter->getPosition();
//				bool isFacingRight = peaShooter->isFacingRight();
//
//				// 将原角色移动到地图外
//				peaShooter->setPosition(-200, -200);
//
//				// 将新角色移动到原角色位置
//				newPlayer->setPosition(originalPosition.x, originalPosition.y);
//				newPlayer->setFacingRight(isFacingRight);
//
//				// 标记角色已切换
//				isCharacterSwitched = true;
//
//				// 消耗 MP
//				peaShooter->setMp(peaShooter->getMp() - 100);
//
//				// 启动新人物出现时间定时器
//				timerNewPlayerDuration.reStart();
//			}
//		}
//	}

void GameScene::update(int runTimeMs) {

	player1->update(runTimeMs);
	player2->update(runTimeMs);
	newplayer->update(runTimeMs);

	Camera::getCamera().update(runTimeMs);

	bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet* bullet) {

		auto deletable = bullet->checkCanRemove();
		if (deletable)
			delete bullet;
		//是否删除指针
		return deletable;
		}), bullets.end());

	for (auto& bullet : bullets)
		bullet->update(runTimeMs);
	/*newplayer->reduceInvincibleTime(runTimeMs);*/

	//判断玩家是否掉下
	const auto& positionPlayer1 = player1->getPosition();
	const auto& positionPlayer2 = player2->getPosition();
	const auto& positionNewPlayer = newplayer->getPosition();
	if (isSlideOutStarted ) {
		if (positionPlayer1.y >= getheight())
			player1->setHp(0);
		if (positionPlayer2.y >= getheight())
			player2->setHp(0);
	}
	/*if (positionPlayer1.y >= getheight())
		player1->setHp(0);
	if (positionPlayer2.y >= getheight())
		player2->setHp(0);*/
	if (!isSlideOutStarted) {
		if (positionNewPlayer.y >= getheight()/* && newplayer->getInvincibleTime() <= 0*/)
			player1->setHp(0);
	}
	

	if (player1->getHp() <= 0 || player2->getHp() <= 0) {
		if (!isGameOver) {

			mciSendString(_T("stop bgmGame"), nullptr, 0, nullptr);
			mciSendString(_T("play uiWin from 0"), nullptr, 0, nullptr);

		}
		isGameOver = true;
	}

	//更新状态栏
	statusBar1P.setHp(player1->getHp());
	statusBar1P.setMp(player1->getMp());

	statusBar2P.setHp(player2->getHp());
	statusBar2P.setMp(player2->getMp());

	//结算
	if (isGameOver) {

		posImgWinnerBar.x += speedWinnerBar * runTimeMs;
		posImgWinnerText.x += speedWinnerText * runTimeMs;

		if (!isSlideOutStarted) {

			timerWinnerSlideIn.update(runTimeMs);

			if (posImgWinnerBar.x > posXImgWinnerBarDst)
				posImgWinnerBar.x = posXImgWinnerBarDst;

			if (posImgWinnerText.x > posXImgWinnerTextDst)
				posImgWinnerText.x = posXImgWinnerTextDst;
		}
		else
			timerWinnerSlideOut.update(runTimeMs);

	}

}

void GameScene::render() {

	putImageAlpha(posImgSky.x, posImgSky.y, &imgSky);

	putImageAlpha(posImgHills.x, posImgHills.y, &imgHills);

	for (const auto& platform : platforms)
		platform.render();

	if (isDebug) {

		settextcolor(RGB(255, 0, 0));
		outtextxy(15, 15, _T("调试模式已开启，按q关闭"));
	}

	player1->render();
	player2->render();
	newplayer->render(); // 渲染新角色

	for (const auto& bullet : bullets)
		bullet->render();

	if (isGameOver) {

		putImageAlpha(posImgWinnerBar.x, posImgWinnerBar.y, &imgWinnerBar);
		putImageAlpha(posImgWinnerText.x, posImgWinnerText.y, player1->getHp() > 0 ? &img1PWinner : &img2PWinner);
	}
	else {
		statusBar1P.render();
		statusBar2P.render();
	}
}



