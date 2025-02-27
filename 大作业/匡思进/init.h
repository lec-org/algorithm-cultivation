#ifndef INIT_H
#define INIT_H

void init() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 设置背景为黑色
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST); // 启用深度测试

    glEnable(GL_COLOR_MATERIAL); // 启用颜色材质
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); // 绑定颜色到材质

    //启用混合功能
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // 定义太阳光源，它是一种白色的光源
    GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat sun_light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat sun_light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };//漫反射
    GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

    glDisable(GL_CULL_FACE);

 
}

#endif
