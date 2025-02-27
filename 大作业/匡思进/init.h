#ifndef INIT_H
#define INIT_H

void init() {

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // ���ñ���Ϊ��ɫ
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST); // ������Ȳ���

    glEnable(GL_COLOR_MATERIAL); // ������ɫ����
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE); // ����ɫ������

    //���û�Ϲ���
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // ����̫����Դ������һ�ְ�ɫ�Ĺ�Դ
    GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat sun_light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat sun_light_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };//������
    GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);

    glDisable(GL_CULL_FACE);

 
}

#endif
