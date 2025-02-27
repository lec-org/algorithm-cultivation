#include "animation.h"
#include "util.h"

//让动画播放的时间
void Animation::update(int playTime) {

    time += playTime;

    if (time > interval) {

        time = 0;
        index++;

        if (index == atlas->getSize()) {

            index = isLoop ? 0 : atlas->getSize() - 1;

            if (!isLoop && callback)
                callback();
        }

    }
}

void Animation::render(int x, int y) {
    putImageAlpha(x, y, atlas->getImage(index));
}


void Animation::reset() {
    time = 0;
    index = 0;
}

void Animation::setAtlas(Atlas* atlas) {
    //reset();
    this->atlas = atlas;
}

void Animation::setIsLoop(bool isLoop) {
    this->isLoop = isLoop;
}

void Animation::setInterval(int ms) {
    interval = ms;
}

void Animation::setCallback(const std::function<void()>& cb) {
    callback = cb;
}

int Animation::getFrameIndex() {
    return index;
}

IMAGE* Animation::getFrame() {
    return atlas->getImage(index);
}

bool Animation::checkFinish() {

    if (isLoop)
        return false;

    return index == atlas->getSize() - 1;
}

