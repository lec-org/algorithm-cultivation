#ifndef CREAT_PLANET_H
#define CREAT_PLANET_H

#include<GL/glut.h>
#include<algorithm>

class Planet
{
public:

    void drawPlanet(GLfloat radius, GLfloat distance, GLfloat angle, GLfloat mat_ambient[], GLfloat mat_diffuse[], GLfloat mat_specular[], GLfloat mat_emission[], GLfloat mat_shininess);
    //半径,  运行距离,  角度
    //光反射, 漫反射, 镜面反射, 自发光属性, 光泽度
};

#endif