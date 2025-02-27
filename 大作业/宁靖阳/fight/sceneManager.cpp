#include "sceneManager.h"

void SceneManager::setSceneManager(Scene* scene) {

	currentScene = scene;

	currentScene->enter();
}

void SceneManager::switchTo(SceneType type) {

	currentScene->exit();

	switch (type) {
	case SceneManager::Menu:
		currentScene = menuScene;
		break;
	case SceneManager::Game:
		currentScene = gameScene;
		break;
	case SceneManager::Selector:
		currentScene = selectorScene;
		break;
	default:
		break;
	}

	currentScene->enter();
}

void SceneManager::receiveInput(const ExMessage& msg) {
	currentScene->receiveInput(msg);
}

void SceneManager::update(int runTimeMs) {
	currentScene->update(runTimeMs);
}

void SceneManager::render() {
	currentScene->render();
}
