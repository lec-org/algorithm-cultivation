#ifndef DRAW_ORBIT_H
#define DRAW_ORBIT_H
#define M_PI 3.141592
#include<GL/glut.h>
#include<iostream>

class Orbit {
public:
    void drawOrbit(float radius, int segments);
};
#endif