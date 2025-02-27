#pragma once
#include<GL/glut.h>
#include<cmath>

#define DEG2RAD 0.0174532925f  // π / 180
class Cycle
{
public:
	void draw_cycle(float innerRadius, float outerRadius, int segments);//环内,环外, 粗糙程度
};