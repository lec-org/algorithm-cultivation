#include"creat_planet.h"
#include"vec3.h"
//Planet drawPlanet;

void Planet::drawPlanet(GLfloat radius, GLfloat distance, GLfloat angle, GLfloat mat_ambient[], GLfloat mat_diffuse[], GLfloat mat_specular[], GLfloat mat_emission[], GLfloat mat_shininess) {

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glPushMatrix();
    {
        glRotatef(angle, 0.0f, 1.0f, 0.0f); // ��Y��������ת
        glTranslatef(distance, 0.0f, 0.0f);
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
        glMaterialf(GL_FRONT, GL_SHININESS, mat_shininess);

        glPushMatrix();
        {
            const int numSlices = 80;//����ֵԽ��Խ�⻬,��������ľ��߷���
            const int numStacks = 32;//���������γ�߷���
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

                    // ���㶥������
                    vec3 vertex1(radius * sinPhi1 * cosTheta, radius * cosPhi1, radius * sinPhi1 * sinTheta);
                    vec3 vertex2(radius * sinPhi2 * cosTheta, radius * cosPhi2, radius * sinPhi2 * sinTheta);

                    // ���ݶ���λ�ü�����ɫ����
                    float distanceFromCenter = sqrt((vertex1.x) * (vertex1.x) + vertex1.y * vertex1.y + vertex1.z * vertex1.z);
                    float colorFactor = distanceFromCenter / radius; // ��������뾶,�����
                    vec3 color = mix(vec3(mat_ambient[0], mat_ambient[1], mat_ambient[2]), vec3(mat_diffuse[0], mat_diffuse[1], mat_diffuse[2]), colorFactor);

                    glColor3f(color.x, color.y, color.z);
                    glVertex3f(vertex1.x , vertex1.y, vertex1.z);
                    glVertex3f(vertex2.x , vertex2.y, vertex2.z);
                }
                glEnd();
            }
            glPopMatrix();
            glutSolidSphere(radius, 40, 32);
        }
        glPopMatrix();
    }
}

