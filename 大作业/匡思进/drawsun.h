#ifndef DRAWSUN_H
#define DRAWSUN_H
#include<iostream>
#include"vec3.h"
float rayAnimationTime = 0.0f;
const float ANIMATION_SPEED = 0.01f;


//绘制光晕
void drawSunHalo() {
    const int numCircles = 3;
    const float radii[] = { 1.1, 1.2, 1.3 }; // 光晕半径
    const float alphas[] = { 0.5, 0.3, 0.1 }; // 透明度
    const float colors[][3] = {
        {1.0, 0.6, 0.5}, // 颜色
        {1.0, 0.7, 0.5},
        {1.0, 0.8, 0.5}
    };

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //GL_SRC_ALPHA：源颜色的混合因子是源颜色的 Alpha 值。也就是说，源颜色的每个分量（红、绿、蓝）都会乘以其对应的 Alpha 值。
   // GL_ONE_MINUS_SRC_ALPHA：目标颜色的混合因子是 1 - 源颜色的 Alpha 值。即目标颜色的每个分量会乘以 1 - 源颜色的 Alpha 值。

    for (int i = 0; i < numCircles; ++i) {
        glColor4f(colors[i][0], colors[i][1], colors[i][2], alphas[i]);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
        for (int j = 0; j <= 100; ++j) {
            float theta = (float)j / 100.0 * 2.0f * 3.1415926f;
            float x = radii[i] * cos(theta);
            float y = radii[i] * sin(theta);
            glVertex2f(x, y);
        }
        glEnd();
    }
    glDisable(GL_BLEND);
}

void drawSunRays() {
    const int RAY_COUNT = 1000;//光线数量
    const int SUB_RAY_COUNT = 30;//光线簇数量
    const float MIN_LENGTH = 1.0f;
    const float MAX_LENGTH = 2.3f;
    const float RANDOM_OFFSET = 0.6f; // 长度变化范围
    const float SUB_ANGLE_VARIATION = 0.8f;

    rayAnimationTime += ANIMATION_SPEED;

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLineWidth(1.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < RAY_COUNT; ++i) {

        // 生成随机的球坐标角度
        float theta = (float)rand() / RAND_MAX * 2.0f * M_PI; // 绕 z 轴的角度
        float phi = (float)rand() / RAND_MAX * M_PI; // 与 z 轴的夹角

        float angle = 2.0f * M_PI * (float)i / (float)RAY_COUNT;
        float length = MIN_LENGTH + (MAX_LENGTH - MIN_LENGTH) * (0.5f + 0.5f * std::sin(rayAnimationTime + (float)i)); // 动态长度
        float offsetX = (float)rand() / RAND_MAX * RANDOM_OFFSET - RANDOM_OFFSET / 2.0f;
        float offsetY = (float)rand() / RAND_MAX * RANDOM_OFFSET - RANDOM_OFFSET / 2.0f;
        float offsetZ = (float)rand() / RAND_MAX * RANDOM_OFFSET - RANDOM_OFFSET / 2.0f;

        float x = std::sin(phi) * std::cos(theta);
        float y = std::sin(phi) * std::sin(theta);
        float z = std::cos(phi);

        // 从中心到边缘透明度渐变
        glBegin(GL_LINE_STRIP);
        glColor4f(1.0f, 1.0f, 0.0f, 0.8f); // 中心不透明
        glVertex3f(0.0f, 0.0f, 0.0f);
        glColor4f(1.0f, 1.0f, 0.5f, 0.1f); // 边缘半透明
        glVertex3f((x + offsetX) * length, (y + offsetY) * length, (z + offsetZ) * length);
        glEnd();

        // 绘制辅助光线
        for (int j = 0; j < SUB_RAY_COUNT; ++j) {
            // 随机改变球坐标角度
            float subTheta = theta + (float)rand() / RAND_MAX * SUB_ANGLE_VARIATION - SUB_ANGLE_VARIATION / 2.0f;
            float subPhi = phi + (float)rand() / RAND_MAX * SUB_ANGLE_VARIATION - SUB_ANGLE_VARIATION / 2.0f;

            float subLength = length * 0.5f + (float)rand() / RAND_MAX * (length * 0.2f);

            // 将球坐标转换为笛卡尔坐标
            float subX = std::sin(subPhi) * std::cos(subTheta);
            float subY = std::sin(subPhi) * std::sin(subTheta);
            float subZ = std::cos(subPhi);

            glBegin(GL_LINES);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(subX * subLength, subY * subLength, subZ * subLength);
            glEnd();
        }
    }
    glDisable(GL_BLEND);
}


void drawsun()
{
    // 设置透视投影
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.33, 1.0, 100.0);  // 设置透视投影
    glMatrixMode(GL_MODELVIEW);

    //设置多个不同颜色的物体
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    // 定义太阳的材质并绘制太阳
    GLfloat sun_mat_ambient[] = { 0.6f, 0.5f, 0.0f, 1.0f }; // 环境光，偏黄的暖色调
    GLfloat sun_mat_diffuse[] = { 1.0f, 1.0f, 0.0f, 1.0f }; // 漫反射，明亮的黄色
    GLfloat sun_mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f }; // 镜面反射，白色
    GLfloat sun_mat_emission[] = { 0.8f, 0.5f, 0.0f, 1.0f }; // 发射光，偏黄的暖色调，模拟太阳自身发光
    GLfloat sun_mat_shininess = 100.0f; // 光泽度

    glMaterialfv(GL_FRONT, GL_AMBIENT, sun_mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sun_mat_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, sun_mat_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, sun_mat_shininess);

    // 在绘制太阳球体时应用颜色渐变
    glPushMatrix();
    const int numSlices = 80;//都是值越大越光滑,遍历球体的经线方向
    const int numStacks = 32;//遍历球体的纬线方向
    for (int i = 0; i < numStacks; ++i) {
        float phi1 = (float)i / (float)numStacks * M_PI;
        float phi2 = (float)(i + 1) / (float)numStacks * M_PI;
        float sinPhi1 = sin(phi1);
        float cosPhi1 = cos(phi1);
        float sinPhi2 = sin(phi2);
        float cosPhi2 = cos(phi2);

        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= numSlices; ++j) {
            float theta = (float)j / (float)numSlices * 2.0f * M_PI;
            float sinTheta = sin(theta);
            float cosTheta = cos(theta);

            // 计算顶点坐标
            vec3 vertex1(sinPhi1 * cosTheta, cosPhi1, sinPhi1 * sinTheta);
            vec3 vertex2(sinPhi2 * cosTheta, cosPhi2, sinPhi2 * sinTheta);

            // 根据顶点位置计算颜色渐变
            float distanceFromCenter = sqrt(vertex1.x * vertex1.x + vertex1.y * vertex1.y + vertex1.z * vertex1.z);
            float colorFactor = distanceFromCenter / 1.0f; // 球体半径为1 // 只会在-1.0和1.0之间处理,计算比例
            vec3 color = mix(vec3(1.0f, 0.8f, 0.0f), vec3(0.5f, 0.4f, 0.0f), colorFactor); // 从中心的黄色到边缘的暗黄色渐变

            glColor3f(color.x, color.y, color.z);
            glVertex3f(vertex1.x, vertex1.y, vertex1.z);
            glVertex3f(vertex2.x, vertex2.y, vertex2.z);
        }
        glEnd();
    }
    glPopMatrix();


    // 绘制太阳球体
    glPushMatrix();
    glutSolidSphere(1.0f, 40, 32);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST); // 启用深度测试

}
#endif