#include "selectorScene.h"

#include <iostream>

void SelectorScene::enter() {
	static const int OFFSET_X = 50;

	animationPeaShooter.setAtlas(&atlasPeaShooterIdleRight);
	animationPeaShooter.setInterval(100);

	animationSunFlower.setAtlas(&atlasSunFlowerIdleRight);
	animationSunFlower.setInterval(100);

	//getwidth:窗口width
		//图片窗口居中 = (窗口 - 图片) / 2
	posImgVS.x = (getwidth() - imgVS.getwidth()) / 2;
	posImgVS.y = (getheight() - imgVS.getheight()) / 2;
	posImgTip.x = (getwidth() - imgSelectorTip.getwidth()) / 2;
	posImgTip.y = getheight() - 125;
	posImg1P.x = (getwidth() / 2 - img1P.getwidth()) / 2 - OFFSET_X;
	posImg1P.y = 35;
	posImg2P.x = getwidth() / 2 + (getwidth() / 2 - img2P.getwidth()) / 2 + OFFSET_X;
	posImg2P.y = posImg1P.y;
	posImg1PDesc.x = (getwidth() / 2 - img1PDesc.getwidth()) / 2 - OFFSET_X;
	posImg1PDesc.y = getheight() - 150;
	posImg2PDesc.x = getwidth() / 2 + (getwidth() / 2 - img2PDesc.getwidth()) / 2 + OFFSET_X;
	posImg2PDesc.y = posImg1PDesc.y;
	posImg1PGravestone.x = (getwidth() / 2 - imgGraveStoneRight.getwidth()) / 2 - OFFSET_X;
	posImg1PGravestone.y = posImg1P.y + img1P.getheight() + 35;
	posImg2PGravestone.x = getwidth() / 2 + (getwidth() / 2 - imgGraveStoneLeft.getwidth()) / 2 + OFFSET_X;
	posImg2PGravestone.y = posImg1PGravestone.y;
	posAnimation1P.x = (getwidth() / 2 - atlasPeaShooterIdleRight.getImage(0)->getwidth()) / 2 - OFFSET_X;
	posAnimation1P.y = posImg1PGravestone.y + 80;
	posAnimation2P.x = getwidth() / 2 + (getwidth() / 2 - atlasPeaShooterIdleRight.getImage(0)->getwidth()) / 2 + OFFSET_X;
	posAnimation2P.y = posAnimation1P.y;
	posImg1PName.y = posAnimation1P.y + 155;
	posImg2PName.y = posImg1PName.y;
	pos1PSelectorButtonLeft.x = posImg1PGravestone.x - img1PSelectorButtonIdleLeft.getwidth();
	pos1PSelectorButtonLeft.y = posImg1PGravestone.y + (imgGraveStoneRight.getheight() - img1PSelectorButtonIdleLeft.getheight()) / 2;
	pos1PSelectorButtonRight.x = posImg1PGravestone.x + imgGraveStoneRight.getwidth();
	pos1PSelectorButtonRight.y = pos1PSelectorButtonLeft.y;
	pos2PSelectorButtonLeft.x = posImg2PGravestone.x - img2PSelectorButtonIdleLeft.getwidth();
	pos2PSelectorButtonLeft.y = pos1PSelectorButtonLeft.y;
	pos2PSelectorButtonRight.x = posImg2PGravestone.x + imgGraveStoneLeft.getwidth();
	pos2PSelectorButtonRight.y = pos1PSelectorButtonLeft.y;

}

void SelectorScene::exit() {

	//实例化玩家
	switch (playerType1P) {
	case SelectorScene::peaShooter:
		player1 = new PeaShooterPlayer;
		imgPlayer1Avatar = &imgPeaShooterAvatar;
		break;
	case SelectorScene::sunFlower:
		player1 = new SunFlowerPlayer;
		imgPlayer1Avatar = &imgSunFlowerAvatar;
		break;
	default:
		break;
	}

	player1->setId(P1);

	switch (playerType2P) {
	case SelectorScene::peaShooter:
		player2 = new PeaShooterPlayer(false);
		imgPlayer2Avatar = &imgPeaShooterAvatar;
		break;
	case SelectorScene::sunFlower:
		player2 = new SunFlowerPlayer(false);
		imgPlayer2Avatar = &imgSunFlowerAvatar;
		break;
	default:
		break;
	}
	player2->setId(P2);
	newplayer = new newPlayer(false);
	newplayer->setId(P3);
	mciSendString(_T("stop bgmMenu"), nullptr, 0, nullptr);
}

void SelectorScene::receiveInput(const ExMessage& msg) {

	switch (msg.message) {
	case WM_KEYDOWN:
		switch (msg.vkcode) {
			//A
		case 0x41:

			isButton1PDownLeft = true;
			break;
			//D
		case 0x44:
			isButton1PDownRight = true;
			break;
		case VK_LEFT:
			isButton2PDownLeft = true;
			break;
		case VK_RIGHT:
			isButton2PDownRight = true;
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (msg.vkcode) {
			//A
		case 0x41:
			isButton1PDownLeft = false;
			//使玩家 在 [peaShooter, inlvalid)切换
				//Enum 类 默认是由0开始的int变量
			playerType1P = PlayerType((playerType1P - 1 + PlayerType::invalid) % PlayerType::invalid);
			mciSendString(_T("play uiSwitch from 0"), NULL, 0, NULL);
			break;
			//D
		case 0x44:
			isButton1PDownRight = false;
			playerType1P = PlayerType((playerType1P + 1) % PlayerType::invalid);
			mciSendString(_T("play uiSwitch from 0"), NULL, 0, NULL);
			break;
		case VK_LEFT:
			isButton2PDownLeft = false;
			playerType2P = PlayerType((playerType2P - 1 + PlayerType::invalid) % PlayerType::invalid);
			mciSendString(_T("play uiSwitch from 0"), NULL, 0, NULL);
			break;
		case VK_RIGHT:
			isButton2PDownRight = false;
			playerType2P = PlayerType((playerType2P + 1) % PlayerType::invalid);
			mciSendString(_T("play uiSwitch from 0"), NULL, 0, NULL);
			break;

		case VK_RETURN:
			sceneManager.switchTo(SceneManager::Game);
			mciSendString(_T("play uiSwitch from 0"), NULL, 0, NULL);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

}

void SelectorScene::update(int runTimeMs) {

	//动画更新 runTimeMs
	animationPeaShooter.update(runTimeMs);
	animationSunFlower.update(runTimeMs);

	//背景线
	selectorBackgroundScrollX += 5;
	if (selectorBackgroundScrollX >= imgPeaShooterSelectorBackgroundLeft.getwidth())
		selectorBackgroundScrollX = 0;
}

void SelectorScene::render() {

	IMAGE* img1PselectorBackground = nullptr;
	IMAGE* img2PselectorBackground = nullptr;

	switch (playerType1P) {
	case SelectorScene::peaShooter:
		img1PselectorBackground = &imgPeaShooterSelectorBackgroundRight;
		break;
	case SelectorScene::sunFlower:
		img1PselectorBackground = &imgSunFlowerSelectorBackgroundRight;
		break;
	default:
		break;
	}
	switch (playerType2P) {
	case SelectorScene::peaShooter:
		img2PselectorBackground = &imgPeaShooterSelectorBackgroundLeft;
		break;
	case SelectorScene::sunFlower:
		img2PselectorBackground = &imgSunFlowerSelectorBackgroundLeft;
		break;
	default:
		break;
	}

	putimage(0, 0, &imgSelectorBackground);

	//渲染滚动背景
	int w = img1PselectorBackground->getwidth();
	int h = img1PselectorBackground->getheight();
	int x = selectorBackgroundScrollX;
	//两种实现
	//putImageAlpha(x - w, 0, img1PselectorBackground);				//图像可以负轴显示
	putImageAlpha(0, 0, x, h, img1PselectorBackground, w - x, 0);
	putImageAlpha(x, 0, w - x, h, img1PselectorBackground, 0, 0);

	w = img2PselectorBackground->getwidth();
	h = img2PselectorBackground->getheight();
	putImageAlpha(getwidth() - w, 0, w - x, h, img2PselectorBackground, x, 0);
	putImageAlpha(getwidth() - x, 0, img2PselectorBackground);


	putImageAlpha(posImgVS.x, posImgVS.y, &imgVS);

	putImageAlpha(posImg1P.x, posImg1P.y, &img1P);
	putImageAlpha(posImg2P.x, posImg2P.y, &img2P);

	//动画在墓碑之上——需要先渲染墓碑
	putImageAlpha(posImg1PGravestone.x, posImg1PGravestone.y, &imgGraveStoneRight);
	putImageAlpha(posImg2PGravestone.x, posImg2PGravestone.y, &imgGraveStoneLeft);

	switch (playerType1P) {
	case SelectorScene::peaShooter:
		//渲染动画
		animationPeaShooter.render(posAnimation1P.x, posAnimation1P.y);
		//渲染文本
		posImg1PName.x = posImg1PGravestone.x + (imgGraveStoneRight.getwidth() - textwidth(strPeaShooterName)) / 2;
		outTextXYShaded(posImg1PName.x, posImg1PName.y, strPeaShooterName);
		break;
	case SelectorScene::sunFlower:
		animationSunFlower.render(posAnimation1P.x, posAnimation1P.y);
		posImg1PName.x = posImg1PGravestone.x + (imgGraveStoneRight.getwidth() - textwidth(strSunFlowerName)) / 2;
		outTextXYShaded(posImg1PName.x, posImg1PName.y, strPeaShooterName);
		break;
	default:
		break;
	}

	switch (playerType2P) {
	case SelectorScene::peaShooter:
		animationPeaShooter.render(posAnimation2P.x, posAnimation2P.y);
		posImg2PName.x = posImg2PGravestone.x + (imgGraveStoneLeft.getwidth() - textwidth(strPeaShooterName)) / 2;
		outTextXYShaded(posImg2PName.x, posImg2PName.y, strPeaShooterName);
		break;
	case SelectorScene::sunFlower:
		animationSunFlower.render(posAnimation2P.x, posAnimation2P.y);
		posImg2PName.x = posImg2PGravestone.x + (imgGraveStoneLeft.getwidth() - textwidth(strSunFlowerName)) / 2;
		outTextXYShaded(posImg2PName.x, posImg2PName.y, strSunFlowerName);
		break;
	default:
		break;
	}

	//按钮
	putImageAlpha(pos1PSelectorButtonLeft.x, pos1PSelectorButtonLeft.y,
		isButton1PDownLeft ? &img1PSelectorButtonDownLeft : &img1PSelectorButtonIdleLeft);
	putImageAlpha(pos1PSelectorButtonRight.x, pos1PSelectorButtonRight.y,
		isButton1PDownRight ? &img1PSelectorButtonDownRight : &img1PSelectorButtonIdleRight);

	putImageAlpha(pos2PSelectorButtonLeft.x, pos2PSelectorButtonLeft.y,
		isButton2PDownLeft ? &img2PSelectorButtonDownLeft : &img2PSelectorButtonIdleLeft);
	putImageAlpha(pos2PSelectorButtonRight.x, pos2PSelectorButtonRight.y,
		isButton2PDownRight ? &img2PSelectorButtonDownRight : &img2PSelectorButtonIdleRight);

	//辅助信息
	putImageAlpha(posImg1PDesc.x, posImg1PDesc.y, &img1PDesc);
	putImageAlpha(posImg2PDesc.x, posImg2PDesc.y, &img2PDesc);
	putImageAlpha(posImgTip.x, posImgTip.y, &imgSelectorTip);
}

void SelectorScene::outTextXYShaded(int x, int y, LPCTSTR text) {
	//深灰色
	settextcolor(RGB(45, 45, 45));
	outtextxy(x + 3, y + 3, text);

	settextcolor(RGB(255, 255, 255));
	outtextxy(x, y, text);
}


