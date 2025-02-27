#include "camera.h"

void Camera::reset() {

    pos.x = 0;
    pos.y = 0;
}

void Camera::update(int runTimeMs) {

    shakeTimer.update(runTimeMs);

    //�����Զ�������Ϊ�뾶��Բ���ж���
    if (isShaking) {
        pos.x = shakingAmplitude * ((rand() % 100 - 50) / 50.0f);
        pos.y = shakingAmplitude * ((rand() % 100 - 50) / 50.0f);
    }

}

void Camera::shake(float shakingAmplitude, int shakingTimeMs) {

    isShaking = true;
    this->shakingAmplitude = shakingAmplitude;

    //������ʱ
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

        //ȡ������
        this->isShaking = false;
        //���������λ��
        this->reset();

        });
}

const Vector2& Camera::getPostion() const {

    return pos;
}

