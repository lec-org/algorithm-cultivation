#pragma once
#include <graphics.h>
#include <vector>
class Atlas {
private:
	std::vector<IMAGE> imgs;
public:
	void loadImages(LPCTSTR path, int num);
	void addImage(const IMAGE& img);
public:
	int getSize() const;
	IMAGE* getImage(int i);
public:
	void clear();
};
