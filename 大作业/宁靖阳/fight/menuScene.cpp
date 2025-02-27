#include "menuScene.h"
#include <iostream>

void MenuScene::enter() {

	mciSendString(_T("play bgmMenu repeat from 0"), nullptr, 0, nullptr);

}

void MenuScene::exit() {

}

void MenuScene::receiveInput(const ExMessage& msg) {

	if (msg.message == WM_KEYUP) {
		mciSendString(_T("play uiConfirm from 0"), nullptr, 0, nullptr);
		sceneManager.switchTo(SceneManager::Selector);
	}

}

void MenuScene::update(int runTimeMs) {

}

void MenuScene::render() {
	putimage(0, 0, &imgMenuBackground);
}

