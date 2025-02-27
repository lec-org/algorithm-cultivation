#include"draw_orbit.h"

void Orbit::drawOrbit(float radius, int segments) {
    glLineWidth(1.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < segments; ++i) {
        // 计算当前分段的角度
        float angle = 2.0f * M_PI * (float)i / (float)segments;
        // 计算当前分段的 z 坐标
        float x = radius * std::cos(angle);
        // 计算当前分段的 z 坐标
        float z = radius * std::sin(angle);
        // 指定当前顶点的坐标
        glVertex3f(x, 0.0f, z);
    }
    glEnd();
}