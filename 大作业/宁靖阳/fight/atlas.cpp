#include "atlas.h"

void Atlas::loadImages(LPCTSTR path, int num) {

	imgs.clear();
	imgs.resize(num);

	TCHAR tPath[128];
	for (int i = 0; i < num; i++) {

		_stprintf_s(tPath, path, i + 1);
		loadimage(&imgs[i], tPath);
	}
}

void Atlas::addImage(const IMAGE& img) {
	imgs.push_back(img);
}

int Atlas::getSize() const {

	return imgs.size();
}

IMAGE* Atlas::getImage(int i) {

	return &imgs[i];
}

void Atlas::clear() {
	imgs.clear();
}

