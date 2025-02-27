#ifndef CREAT_NEBULA_H
#define CREAT_NEBULA_H

#include <GL/glut.h>
#include <cstdlib>
#include <ctime>

// 定义星云粒子结构体
struct NebulaParticle {
    float x, y, z;  // 粒子位置
    float r, g, b;  // 粒子颜色
    float alpha;    // 粒子透明度
};

// 星云类
class Nebula {
public:
    static const int NUM_PARTICLES = 200;  // 粒子数量
    NebulaParticle particles[NUM_PARTICLES];

    // 初始化星云粒子
    void initnebula() {
        srand(static_cast<unsigned int>(time(nullptr)));
        for (int i = 0; i < NUM_PARTICLES; ++i) {
            // 随机生成粒子位置
            particles[i].x = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 10.0f;
            particles[i].y = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 10.0f;
            particles[i].z = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * 10.0f;

            // 随机生成粒子颜色（以紫色调为主模拟星云）
            particles[i].r = 0.5f + static_cast<float>(rand()) / RAND_MAX * 0.5f;
            particles[i].g = 0.0f + static_cast<float>(rand()) / RAND_MAX * 0.2f;
            particles[i].b = 0.5f + static_cast<float>(rand()) / RAND_MAX * 0.5f;

            // 随机生成粒子透明度
            particles[i].alpha = static_cast<float>(rand()) / RAND_MAX * 0.3f;
        }
    }

    // 绘制星云
    void drawnebula() {

        glBegin(GL_POINTS);
        for (int i = 0; i < NUM_PARTICLES; ++i) {
            glColor4f(particles[i].r, particles[i].g, particles[i].b, particles[i].alpha);
            glVertex3f(particles[i].x, particles[i].y, particles[i].z);
        }
        glEnd();

    }
};

#endif