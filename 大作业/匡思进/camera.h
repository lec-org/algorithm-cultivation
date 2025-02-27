#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>

#include <GL/glut.h>

class Camera {
public:
    float posX, posY, posZ; // 相机位置
    float centerX, centerY, centerZ; // 目标点
    float upX, upY, upZ; // 上方向

    Camera() : posX(0), posY(12), posZ(25), centerX(0), centerY(0), centerZ(0), upX(0), upY(1), upZ(0) {}

    // 更新相机视角
    void update() {
        gluLookAt(posX, posY, posZ, centerX, centerY, centerZ, upX, upY, upZ);//前三个 表示相机在世界坐标系中的位置
    //中间三个定义相机正对着的世界坐标系中的点的位置坐标，成像后这一点会位于画板的中心位置
    //最后三个数定义相机
    // 本身的朝向。这三个坐标是在世界坐标系中的坐标点，可以理解为人站立在相机处头的朝向。这三个坐标是世界坐标系中的坐标点，不是相机坐标系的，只是用来定义方向，

    }

    // 处理键盘输入
    void moveForward(float distance) { posZ -= distance; }
    void moveBackward(float distance) { posZ += distance; }
    void moveLeft(float distance) { posX -= distance; }
    void moveRight(float distance) { posX += distance; }
    void moveUp(float distance) { posY += distance; }
    void moveDown(float distance) { posY -= distance; }
};
#endif
