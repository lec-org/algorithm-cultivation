#include "camera.h"

void Camera::reset() {

    pos.x = 0;
    pos.y = 0;
}

void Camera::update(int runTimeMs) {

    shakeTimer.update(runTimeMs);

    //设置以抖动幅度为半径的圆进行抖动
    if (isShaking) {
        pos.x = shakingAmplitude * ((rand() % 100 - 50) / 50.0f);
        pos.y = shakingAmplitude * ((rand() % 100 - 50) / 50.0f);
    }

}

void Camera::shake(float shakingAmplitude, int shakingTimeMs) {

    isShaking = true;
    this->shakingAmplitude = shakingAmplitude;

    //重启计时
    shakeTimer.setTimer(shakingTimeMs);
    shakeTimer.reStart();
}

Camera& Camera::getCamera() {
    static Camera camera;
    return camera;
}


Camera::Camera() {
    shakeTimer.setIsOneShot(true);

    shakeTimer.setCallback([&] {

        //取消抖动
        this->isShaking = false;
        //重置摄像机位置
        this->reset();

        });
}

const Vector2& Camera::getPostion() const {

    return pos;
}

