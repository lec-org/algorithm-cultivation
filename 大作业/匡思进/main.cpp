#include <GL/glew.h> 
#include <GL/glut.h>  
#include <GLFW/glfw3.h>  
#include<iostream>
#include<vector>
#include<string>
#include<SOIL.h>
#include "add_music.h" //加载背景音乐
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include<math.h>
#include"init.h"
#include"drawsun.h"
#include"creat_planet.h"
#include"drawcycle.h"
#include"creat_nebula.h"//星云
#include"camera.h"//视角变动
#include"draw_orbit.h"


#define WIDTH 1000
#define HEIGHT 1000
#define M_PI 3.141592

 //调用头文件
Planet creat_planet;
Cycle cycle;
Nebula nebula;
Camera camera;
Orbit orbit;
Music music;


unsigned int texture;
const int sun_texture_count = 5;
unsigned int sunTextures[sun_texture_count];
int currentSunTextureIndex = 0;
int nextSunTextureIndex = 1;
float gatherFactor = 0.0f;//星星聚集
std::vector<float> linePoints;  // 用于存储线段的顶点
float linealpha = 0.8f;// 线条的透明度


// 记录鼠标点击位置
int clickX = 0;
int clickY = 0;
bool isClicked = false;

// 定义天体结构体
struct CelestialBody {
    float radius;  // 天体半径
    float orbitRadius;  // 轨道半径
    float orbitCenterX; // 轨道中心 X 坐标
    float orbitCenterY; // 轨道中心 Y 坐标
    float orbitCenterZ; // 轨道中心 Z 坐标

    bool isSelected;    // 是否被选中
    std::string name;   // 星球名称
    std::string color;     // 星球颜色
   

    std::string description; // 星球描述信息
    float diameter;          // 星球直径
};

// 射线结构体
struct Ray {
    float originX, originY, originZ;
    float directionX, directionY, directionZ;
};

struct Star {
    float x, y, z; // 星星的位置
    bool isGathered; // 是否处于聚集状态
    float targetX, targetY, targetZ; // 聚集目标位置
};
const int STAR_COUNT = 500;  // 星星的数量
Star stars[STAR_COUNT]; // 星星数组

// 初始化天体

// 地球
CelestialBody earth = { 0.32f, 5.4f, 0.0f, 0.0f, 0.0f, false, "Earth\n",
                        "blue\n","our home planet, full of life.\n", 12742.0f };

// 月球
CelestialBody moon = { 0.1f, 0.55f, earth.orbitCenterX, earth.orbitCenterY, earth.orbitCenterZ, false, "Moon\n",
                       "yellow\n",  "Earth's natural satellite.\n", 3474.8f };

// 水星
CelestialBody mercury = { 0.15f, 2.0f, 0.0f, 0.0f, 0.0f, false, "Mercury\n",
                       " blue\n ","The closest planet to the Sun.\n", 4880.0f };

// 金星
CelestialBody venus = { 0.3f, 4.0f, 0.0f, 0.0f, 0.0f, false, "Venus\n",
                       "orange\n","The second planet from the Sun, known for its thick atmosphere.\n", 12103.6f };

// 土星
CelestialBody Saturn = { 0.6f, 9.5f, 0.0f, 0.0f, 0.0f, false, "Saturn\n",
                         "brown\n", "A gas giant with a prominent ring system.\n", 116464.0f };

// 火星
CelestialBody mars = { 0.2f, 6.6f, 0.0f, 0.0f, 0.0f, false, "Mars\n",
                       "red\n","The fourth planet from the Sun, often called the 'Red Planet'.\n", 6779.0f };

// 木星
CelestialBody Jupiter = { 0.7f, 7.9f, 0.0f, 0.0f, 0.0f, false, "Jupiter\n",
                        "oatmeal\n","The largest planet in our solar system.\n", 139822.0f };

// 海王星
CelestialBody Neptune = { 0.5f, 11.9f, 0.0f, 0.0f, 0.0f, false, "Neptune\n",
                         "blue\n","The eighth and farthest known planet from the Sun.\n", 49244.0f };

// 天王星
CelestialBody Uranus = { 0.45f, 10.9f, 0.0f, 0.0f, 0.0f, false, "Uranus\n",
                         "blue-black\n","The seventh planet from the Sun, known for its unique axial tilt.\n", 50724.0f };

// 全局变量
float starX[STAR_COUNT];     // 星星的 x 坐标
float starY[STAR_COUNT];     // 星星的 y 坐标
float starZ[STAR_COUNT];     // 星星的 z 坐标
float mouseX = 0.0f;         // 鼠标的 x 坐标
float mouseY = 0.0f;
float blendFactor = 0.0f;  // 混合因子，范围从 0 到 1
const float blendStep = 0.99f;  // 每次帧更新时混合因子的增量

static GLfloat angle1 = 0.0f, angle4, angle5, angle6, angle7, angle8; // 地球公转角度
static GLfloat angle2 = 0.0f; // 火星公转角度
static GLfloat angle3 = 0.0f; // 月球绕地球公转角度


// 鼠标灵敏度
const float mouseSensitivity = 10.0f;

// 小行星带
const int ASTEROID_COUNT = 200;
float asteroidX[ASTEROID_COUNT];
float asteroidY[ASTEROID_COUNT];
float asteroidZ[ASTEROID_COUNT];
float asteroidSize[ASTEROID_COUNT];
float asteroidAngle[ASTEROID_COUNT];

//当前显示信息的星球和计时器
CelestialBody* currentDisplayPlanet = NULL;
int displayTimer = 0;

//绘制跟随鼠标移动的线条
void drawLine() {
    if (linePoints.size() >= 4) { //2个点构成一条线段

        glDisable(GL_DEPTH_TEST);

        glMatrixMode(GL_PROJECTION);
        glPushMatrix(); // 保存当前矩阵状态
        glLoadIdentity();
        gluOrtho2D(-5.0, 5.0, -5.0, 5.0); // 设置正交投影
        
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glLineWidth(0.8f);
        glColor4f(0.2f, 0.6f, 1.0f, linealpha);  // 设置线段颜色为紫色
        glBegin(GL_LINE_STRIP);

        for (size_t i = 0; i < linePoints.size(); i += 2) {
            if (i + 2 < linePoints.size())
                glVertex2f(linePoints[i], linePoints[i + 1]);

        }

        glEnd();

        glPopMatrix(); 
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);

        glEnable(GL_DEPTH_TEST);

        if (linealpha >= 0.2f) linealpha -= 0.05f;
    }
}


////聚集成蒲公英(平面)
//void gatherStars(float centerX, float centerY, float centerZ) {
//
//    const int layers = 5; // 蒲公英的层数
//    const float radius = 0.2f; // 每层的半径
//    const float angleStep = 2.0f * M_PI / (STAR_COUNT / layers); // 每层的角度步长
//
//    int starIndex = 0;
//    for (int layer = 0; layer < layers; ++layer) {
//        float currentRadius = radius * (layer + 1);
//        for (float angle = 0; angle < 2.0f * M_PI; angle += angleStep) {
//            if (starIndex >= STAR_COUNT) break;
//
//            stars[starIndex].targetX = centerX + currentRadius * cos(angle);
//            stars[starIndex].targetY = centerY + currentRadius * sin(angle);
//            stars[starIndex].targetZ = centerZ + currentRadius * sin(angle);
//
//            starIndex++;
//        }
//    }
//}
//聚集成球状蒲公英(立体)
void gatherStars(float centerX, float centerY, float centerZ) {

    const int layers = 10; // 蒲公英的层数
    const float radius = 0.1f; // 每层的半径

    int starIndex = 0;
    for (int layer =1; layer <= layers; ++layer) {
        float currentRadius = radius * layer;
        // 每层的星星数量
        int starsPerLayer = STAR_COUNT / layers;

        for (int i = 0; i < starsPerLayer; ++i) {
            if (starIndex >= STAR_COUNT) break;

            // 生成均匀分布的极角和方位角
            float theta = acos(1 - 2 * (float)i / starsPerLayer); // 极角，范围从 0 到 π
            float phi = 2 * M_PI * (float)(rand() % 1000) / 1000.0f; // 方位角，范围从 0 到 2π

            // 将球坐标转换为笛卡尔坐标
            float x = currentRadius * sin(theta) * cos(phi);
            float y = currentRadius * sin(theta) * sin(phi);
            float z = currentRadius * cos(theta);

            // 设置星星的目标位置
            stars[starIndex].targetX = centerX + x;
            stars[starIndex].targetY = centerY + y;
            stars[starIndex].targetZ = centerZ + z;

            starIndex++;
        }
    }
}


//控制星星聚散
void mouse(int button, int state, int x, int y) {

    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
          
            // 记录鼠标点击位置
            clickX = x;
            clickY = y;
            isClicked = true;

            // 切换星星的聚集状态
            for (int i = 0; i < STAR_COUNT; ++i) {

                stars[i].isGathered = !stars[i].isGathered;

                if (stars[i].isGathered) {
                    // 设置聚集目标位置
                    stars[i].targetX = (2.0f * x / WIDTH - 1.0f) * 5.0f; // 转换为 OpenGL 坐标,让鼠标位置与实际对齐
                    stars[i].targetY = (1.0f - 2.0f * y / HEIGHT) * 5.0f;
                    stars[i].targetZ = (float)(rand() % 5) / 1.0f * 5.0f;
                    gatherStars(stars[i].targetX, stars[i].targetY, stars[i].targetZ);

                }
                else {
                    // 设置分散目标位置（随机位置）
                    stars[i].targetX = (float)(rand() % 200 - 100) / 100.0f * 10.0f;
                    stars[i].targetY = (float)(rand() % 200 - 100) / 100.0f * 10.0f;
                    stars[i].targetZ = (float)(rand() % 200 - 100) / 100.0f * 10.0f;
                }

            }
            // 初始化线段的起点
            linePoints.clear();
            linePoints.push_back((2.0f * x / WIDTH - 1.0f) * 5.0f);
            linePoints.push_back((1.0f - 2.0f * y / HEIGHT) * 5.0f);
        }
        else if (state == GLUT_UP) {
            isClicked = false;
            //鼠标松开,清除线条
            linePoints.clear();
            linealpha = 1.0f;
        }
    }
}


//鼠标动态
void mouseMotion(int x, int y) {

    if (isClicked) {
        // 鼠标按下并移动时，更新线段的终点
        linePoints.push_back((2.0f * x / WIDTH - 1.0f) * 5.0f);
        linePoints.push_back((1.0f - 2.0f * y / HEIGHT )* 5.0f);
        if (linePoints.size() > 70) {
            // 保持线段长度不变，移除最早的顶点
            linePoints.erase(linePoints.begin(), linePoints.begin() + 2);
        }
        glutPostRedisplay();  // 标记窗口需要重绘
    }
}

// 绘制方框和信息
void drawInfoBox(const CelestialBody& body) {
    if (!body.isSelected && &body != currentDisplayPlanet && displayTimer < 300) return;

    // 保存当前的投影矩阵和模型视图矩阵
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    // 设置正交投影，范围从 (0, 0) 到 (WIDTH, HEIGHT)
    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // 信息框的位置(左上角)
    float infoBoxX = WIDTH * 0.2f;
    float infoBoxY = HEIGHT * 0.7f;


    // 设置边框颜色
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(infoBoxX, infoBoxY);
    glVertex2f(infoBoxX + 550, infoBoxY);
    glVertex2f(infoBoxX + 550, infoBoxY + 100);
    glVertex2f(infoBoxX, infoBoxY + 100);
    glEnd();

    // 显示星球信息
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(infoBoxX, infoBoxY + 80);
    for (char c : body.name) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2f(infoBoxX, infoBoxY + 50);
    for (char c : body.color) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glRasterPos2f(infoBoxX, infoBoxY + 20);
    for (char c : body.description) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    // 恢复之前保存的投影矩阵和模型视图矩阵
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// 绘制混合太阳
void drawBlendedSun(float x, float y, float width, float height) {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // 绘制当前纹理
    glBindTexture(GL_TEXTURE_2D, sunTextures[currentSunTextureIndex]);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f - blendFactor);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(x, y);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(x + width, y);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(x + width, y + height);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(x, y + height);
    glEnd();

    // 绘制下一纹理
    glBindTexture(GL_TEXTURE_2D, sunTextures[nextSunTextureIndex]);
    glColor4f(1.0f, 1.0f, 1.0f, blendFactor);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(x, y);
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(x + width, y);
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(x + width, y + height);
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(x, y + height);
    glEnd();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void initTextures() {
    glGenTextures(sun_texture_count, sunTextures);

    const char* filenames[sun_texture_count] = { "4.jpg",  "5.jpg", "6.png","7.jpg" ,"3.jpg" };

    for (int i = 0; i < sun_texture_count; ++i) {
        glBindTexture(GL_TEXTURE_2D, sunTextures[i]);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // 加载并生成纹理
        int sun_width, sun_height, nrChannels;
        // stbi_set_flip_vertically_on_load(true); // 翻转纹理的Y轴
        unsigned char* data = stbi_load(filenames[i], &sun_width, &sun_height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sun_width, sun_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
           
            std::cout << "Failed to load texture: " << filenames[i] << std::endl;

            exit(1); // 退出程序
        }
        stbi_image_free(data);
    }
}

// 贴图位置
void drawTexturedSquare(float x, float y, float width, float height, unsigned int texId) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);

    glBegin(GL_QUADS);
    // 左下角
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(x, y);
    // 右下角
    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(x + width, y);
    // 右上角
    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(x + width, y + height);
    // 左上角
    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(x, y + height);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}


// 键盘回调函数
void keyboard(unsigned char key, int x, int y) {
    float moveSpeed = 0.5f; // 移动速度

    switch (key) {
    case 'w': // 向前移动
        camera.moveForward(moveSpeed);
        break;
    case 's': // 向后移动
        camera.moveBackward(moveSpeed);
        break;
    case 'a': // 向左移动
        camera.moveLeft(moveSpeed);
        break;
    case 'd': // 向右移动
        camera.moveRight(moveSpeed);
        break;
    case 'q': // 向上移动
        camera.moveUp(moveSpeed);
        break;
    case 'e': // 向下移动
        camera.moveDown(moveSpeed);
        break;

    case '1':
        currentDisplayPlanet = &mercury;
        displayTimer = 0;
        break;
    case '2':
        currentDisplayPlanet = &venus;
        displayTimer = 0;
        break;
    case '3':
        currentDisplayPlanet = &earth;
        displayTimer = 0;
        break;
    case '4':
        currentDisplayPlanet = &mars;
        displayTimer = 0;
        break;
    case '5':
        currentDisplayPlanet = &Jupiter;
        displayTimer = 0;
        break;
    case '6':
        currentDisplayPlanet = &Saturn;
        displayTimer = 0;
        break;
    case '7':
        currentDisplayPlanet = &Uranus;
        displayTimer = 0;
        break;
    case '8':
        currentDisplayPlanet = &Neptune;
        displayTimer = 0;
        break;
    }

    glutPostRedisplay(); // 请求重绘
}

//显示行星轨道
// radius: 轨道的半径
//segments: 轨道的分段数，分段数越多，轨道越平滑


// 绘制文本函数
void drawText(std::string text, int x, int y) {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(0.5f, 0.5f, 1.0f); // 设置文本颜色为紫色
    glRasterPos2i(x, y);
    for (char c : text) {
       
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

void myDisplay(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST); // 启用深度测试
    // 创建透视效果视图
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // 重置模型视图矩阵
    gluPerspective(120.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 1.0f, 20.0f); // 将所有数据数以 1e6
    // 1可视角大小;    2定义物体显示在画板上的x和y方向上的比例 ，会按实际反应长宽比
    //3这个值越大，表示观测点距离物体距离越远
    //4定义可观测到的物体的最远处截面相距相机的距离
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // 设置相机
    camera.update();

    glPushMatrix();
    //绘制太阳
    drawsun();

    // 绘制太阳光线
    drawSunRays();

    //光晕
    drawSunHalo();
    glPopMatrix();

    // 绘制太阳(贴图方式)
    //glPushMatrix();
    //glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, sunTextures[currentSunTextureIndex]);
    //float x = -1.15f;
    //float y = -1.15f;
    //float squareWidth = 2.38f;
    //float squareHeight = 2.38f;

    //drawBlendedSun(x, y, squareWidth, squareHeight);
    ////drawTexturedSquare(x, y, squareWidth, squareHeight, sunTextures[currentSunTextureIndex]);
    ////drawsun();

    //glDisable(GL_TEXTURE_2D);
    //glPopMatrix();

    // 定义地球的材质并绘制地球
    GLfloat earth_mat_ambient[] = { 0.2f, 0.2f, 0.8f, 1.0f };
    GLfloat earth_mat_diffuse[] = { 0.2f, 0.2f, 0.5f, 1.0f };
    GLfloat earth_mat_specular[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    GLfloat earth_mat_emission[] = { 0.0f, 0.0f, 1.0f, 1.0f };
    GLfloat earth_mat_shininess = 10.0f;

    // 开始保存地球的变换状态
        glPushMatrix();
        creat_planet.drawPlanet(0.32f, 5.4f, angle3, earth_mat_ambient, earth_mat_diffuse, earth_mat_specular, earth_mat_emission, earth_mat_shininess);
        glPopMatrix();

        // 绘制地球轨道
        glPushMatrix();
        glColor3f(0.0f, 0.1f, 0.9f);
        orbit.drawOrbit(earth.orbitRadius, 100);

        glPopMatrix();


        // 定义月球的材质并绘制月球
        GLfloat moon_mat_ambient[] = { 0.5f, 0.5f, 0.0f, 1.0f };
        GLfloat moon_mat_diffuse[] = { 0.72f, 0.73f, 0.47f, 1.0f };
        GLfloat moon_mat_specular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        GLfloat moon_mat_emission[] = { 0.72f, 0.73f, 0.47f, 1.0f };
        GLfloat moon_mat_shininess = 10.0f;

        // 地球自转的同时，让月球绕地球公转
        glPushMatrix(); // 保存当前变换矩阵，即地球的变换矩阵
        {
            glRotatef(angle3, 0.0f, 1.0f, 0.0f);
            glTranslatef(5.4f, 0.0f, 0.0f);
            glRotatef(angle2, 0.0f, 1.0f, 0.0f);
            glTranslatef(0.55f, 0.0f, 0.0f);
            glMaterialfv(GL_FRONT, GL_AMBIENT, moon_mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, moon_mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, moon_mat_specular);
            glMaterialfv(GL_FRONT, GL_EMISSION, moon_mat_emission);
            glMaterialf(GL_FRONT, GL_SHININESS, moon_mat_shininess);
            glutSolidSphere(0.06f, 40, 32);
        }
        glPopMatrix(); // 恢复地球的变换矩阵

        // 绘制月球轨道
        glPushMatrix();

        glColor3f(0.72f, 0.73f, 0.47f);

        float moonOrbitCenterX = earth.orbitRadius * cos(angle3 * M_PI / 180.0f);
        float moonOrbitCenterZ = earth.orbitRadius * sin(angle3 * M_PI / 180.0f);
        glTranslatef(moonOrbitCenterX, 0.0f, -moonOrbitCenterZ);
        orbit.drawOrbit(moon.orbitRadius, 100);
        glPopMatrix();

        // 定义火星的材质并绘制火星
        GLfloat mars_mat_ambient[] = { 0.3f, 0.1f, 0.0f, 1.0f };
        GLfloat mars_mat_diffuse[] = { 0.8f, 0.4f, 0.2f, 1.0f };
        GLfloat mars_mat_specular[] = { 0.3f, 0.1f, 0.05f, 1.0f };
        GLfloat mars_mat_emission[] = { 0.05f, 0.02f, 0.01f, 1.0f };
        GLfloat mars_mat_shininess = 15.0f;

        creat_planet.drawPlanet(0.3f, 6.6f, angle4, mars_mat_ambient, mars_mat_diffuse, mars_mat_specular, mars_mat_emission, mars_mat_shininess);

        // 绘制火星轨道
        glPushMatrix();

        glColor3f(0.3f, 0.1f, 0.0f);
        orbit.drawOrbit(mars.orbitRadius, 100);
        glPopMatrix();

        //绘制水星
        GLfloat mercury_mat_ambient[] = { 0.25f, 0.25f, 0.25f, 1.0f };//没有光照的时候: 浅灰色
        GLfloat mercury_mat_diffuse[] = { 0.4f, 0.4f, 0.35f, 1.0f };//漫反射: 浅灰色
        GLfloat mercury_mat_specular[] = { 0.0f, 0.1f, 0.1f, 1.0f };//镜面反色较弱
        GLfloat mercury_mat_emission[] = { 0.2f, 0.2f, 0.2f, 0.1f };//本身不发光
        GLfloat mercury_mat_shininess = 5.0f;//光泽度低

        creat_planet.drawPlanet(0.15f, 2.8f, angle1, mercury_mat_ambient, mercury_mat_diffuse, mercury_mat_specular, mercury_mat_emission, mercury_mat_shininess);

        // 绘制水星轨道
        glPushMatrix();
        glColor3f(0.25f, 0.25f, 0.25f);
        
        glColor3f(0.0f, 0.0f, 1.0f); // 未选中时轨道颜色为蓝色
        orbit.drawOrbit(mercury.orbitRadius, 100);
        glPopMatrix();
        //drawInfoBox(mercury);

        //绘制金星
        GLfloat venus_mat_ambient[] = { 0.8f, 0.7f, 0.4f, 1.0f };//柔和黄色
        GLfloat venus_mat_diffuse[] = { 0.8f, 0.65f, 0.4f, 1.0f };//反射成为亮黄色
        GLfloat venus_mat_specular[] = { 0.3f, 0.2f, 0.1f, 1.0f };
        GLfloat venus_mat_emission[] = { 0.2f, 0.16f, 0.1f, 1.0f };
        GLfloat venus_mat_shininess = 10.0f;

        creat_planet.drawPlanet(0.19f, 4.0f, angle2, venus_mat_ambient, venus_mat_diffuse, venus_mat_specular, venus_mat_emission, venus_mat_shininess);

        // 绘制金星轨道
        glPushMatrix();
        glColor3f( 0.8f, 0.7f, 0.4f);
        orbit.drawOrbit(venus.orbitRadius, 100);
        glPopMatrix();
        //drawInfoBox(venus);

        // 绘制土星
        GLfloat Saturn_mat_ambient[] = { 0.5f, 0.5f, 0.0f, 1.0f };
        GLfloat Saturn_mat_diffuse[] = { 0.8f, 0.81f, 0.27f, 1.0f };
        GLfloat Saturn_mat_specular[] = { 0.2f, 0.15f, 0.1f, 1.0f };
        GLfloat Saturn_mat_emission[] = { 0.1f, 0.1f, 0.0f, 1.0f };
        GLfloat Saturn_mat_shininess = 5.0f;

        creat_planet.drawPlanet(0.47f, 9.5f, angle6, Saturn_mat_ambient, Saturn_mat_diffuse, Saturn_mat_specular, Saturn_mat_emission, Saturn_mat_shininess);

        // 绘制土星轨道
        glPushMatrix();
         glColor3f(0.0f, 0.0f, 1.0f); // 未选中时轨道颜色为蓝色
        orbit.drawOrbit(Saturn.orbitRadius, 100);
        glPopMatrix();
       // drawInfoBox(Saturn);

        // 土星的环
        glPushMatrix();
        glRotatef(angle6, 0.0f, 1.0f, 0.0f);
        glTranslatef(9.5f, 0.0f, 0.0f);
        cycle.draw_cycle(0.6f, 0.9f, 100);//圈内, 圈外
        glPopMatrix();

        // 绘制木星
        GLfloat Jupiter_mat_ambient[] = { 0.6f, 0.6f, 0.0f, 1.0f };
        GLfloat Jupiter_mat_diffuse[] = { 0.82f, 0.87f, 0.27f, 1.0f };
        GLfloat Jupiter_mat_specular[] = { 0.2f, 0.15f, 0.1f, 1.0f };
        GLfloat Jupiter_mat_emission[] = { 0.1f, 0.1f, 0.0f, 1.0f };
        GLfloat Jupiter_mat_shininess = 5.0f;

        creat_planet.drawPlanet(0.5f, 7.9f, angle5, Jupiter_mat_ambient, Jupiter_mat_diffuse, Jupiter_mat_specular, Jupiter_mat_emission, Jupiter_mat_shininess);

        // 绘制木星轨道
        glColor3f(0.6f, 0.6f, 0.0f);
        orbit.drawOrbit(Jupiter.orbitRadius, 100);
        //drawInfoBox(Jupiter);

        // 绘制天王星
        GLfloat Uranus_mat_ambient[] = { 0.488f, 0.95f, 0.786f, 1.0f };
        GLfloat Uranus_mat_diffuse[] = { 0.388f, 0.9f, 0.686f, 1.0f };
        GLfloat Uranus_mat_specular[] = { 0.088f, 0.2f, 0.186f, 1.0f };
        GLfloat Uranus_mat_emission[] = { 0.1f, 0.2f, 0.15f, 1.0f };
        GLfloat Uranus_mat_shininess = 5.0f;

        creat_planet.drawPlanet(0.35f, 10.9f, angle7, Uranus_mat_ambient, Uranus_mat_diffuse, Uranus_mat_specular, Uranus_mat_emission, Uranus_mat_shininess);

        //// 绘制天王星轨道
         glColor3f(0.488f, 0.95f, 0.786f);
        orbit.drawOrbit (Uranus.orbitRadius, 100);

        //绘制海王星
        GLfloat Neptune_mat_ambient[] = { 0.5f, 0.8f, 0.95f, 1.0f };
        GLfloat Neptune_mat_diffuse[] = { 0.458f, 0.756f, 0.921f, 1.0f };
        GLfloat Neptune_mat_specular[] = { 0.1f, 0.15f, 0.2f, 1.0f };
        GLfloat Neptune_mat_emission[] = { 0.1f, 0.1f, 0.2f, 1.0f };
        GLfloat Neptune_mat_shininess = 5.0f;

        creat_planet.drawPlanet(0.3f, 11.9f, angle8, Neptune_mat_ambient, Neptune_mat_diffuse, Neptune_mat_specular, Neptune_mat_emission, Neptune_mat_shininess);

        // 绘制sea王星轨道
        glPushMatrix();
          glColor3f(0.5f, 0.8f, 0.95f);
          orbit.drawOrbit(Neptune.orbitRadius, 100);
        glPopMatrix();
        //drawInfoBox(Neptune);


    // 绘制星云
    glPushMatrix();
    nebula.initnebula();
    nebula.drawnebula();
    glPopMatrix();

    // 绘制说明文本
    std::string instructions1 = "W: front";
    drawText(instructions1, 10, glutGet(GLUT_WINDOW_HEIGHT) - 20);
    std::string instructions2 = "S: back";
    drawText(instructions2, 10, glutGet(GLUT_WINDOW_HEIGHT) - 45);

    std::string instructions3 = "A: left";
    drawText(instructions3, 10, glutGet(GLUT_WINDOW_HEIGHT) - 70);
    std::string instructions4 = "D: right";
    drawText(instructions4, 10, glutGet(GLUT_WINDOW_HEIGHT) - 95);

    std::string instructions5 = "Q : up\n";
    drawText(instructions5, 10, glutGet(GLUT_WINDOW_HEIGHT) - 120);
    std::string instructions6 = "E : down";
    drawText(instructions6, 10, glutGet(GLUT_WINDOW_HEIGHT) - 145);

    //星球按键说明
    std::string one = "Press the '1' key : Mercury";
    drawText(one, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) - 22);

    std::string two = "Press the '2' key : Venus";
    drawText(two, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) - 44);

    std::string three = "Press the '3' key : Earth";
    drawText(three, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) - 66);

    std::string four = "Press the '4' key : Mars";
    drawText(four, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) - 88);

    std::string five = "Press the '5' key : Jupiter";
    drawText(five, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) - 110);

    std::string six = "Press the '6' key : Saturn";
    drawText(six, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) - 132);

    std::string seven = "Press the '7' key : Uranus";
    drawText(seven, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) - 154);

    std::string eight = "Press the '8' key : Neptune";
    drawText(eight, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) - 176);

    // 最后绘制信息框，确保在最上层
    if (currentDisplayPlanet != NULL)
    {
        drawInfoBox(earth);
        drawInfoBox(moon);
        drawInfoBox(mercury);
        drawInfoBox(venus);
        drawInfoBox(Saturn);
        drawInfoBox(mars);
        drawInfoBox(Jupiter);
        drawInfoBox(Neptune);
    }
    drawInfoBox(Uranus);

    // 绘制小行星带
    glColor3f(0.6f, 0.6f, 0.6f); // 设置小行星的颜色为灰色
    for (int i = 0; i < ASTEROID_COUNT; ++i) {
        glPushMatrix();
        glTranslatef(asteroidX[i], asteroidY[i], asteroidZ[i]);
        glRotatef(asteroidAngle[i], 0.0f, 1.0f, 0.0f); // 绕 Y 轴旋转
        glutSolidSphere(asteroidSize[i], 10, 10); // 绘制小行星
        glPopMatrix();
    }

    // 绘制星星
    glColor3f(1.0f, 1.0f, 1.0f); // 设置星星颜色为白色
    glPointSize(2.0f); // 设置星星大小
    glBegin(GL_POINTS);
    for (int i = 0; i < STAR_COUNT; ++i) {
        float size = stars[i].isGathered ? 5.0f : 2.0f; // 聚集时星星变大
        glPointSize(size);
        glVertex3f(stars[i].x, stars[i].y, stars[i].z);
    }
    glEnd();

    drawLine();//绘制线条
    glutSwapBuffers();

}

void myIdle(void) {
    angle1 += 0.04f;
    angle2 += 0.0292f;
    angle3 += 0.0248f;
    angle4 += 0.02f;
    angle5 += 0.0108f;
    angle6 += 0.008f;
    angle7 += 0.0056f;
    angle8 += 0.0044f;

    if (angle1 >= 360.0f - 0.000001f) angle1 = 0.0f;
    if (angle2 >= 360.0f) angle2 = 0.0f;
    if (angle3 >= 360.0f) angle3 = 0.0f;

    // 更新星星的位置
    for (int i = 0; i < STAR_COUNT; ++i) {
        float speed = 0.01f; // 移动速度
        stars[i].x += (stars[i].targetX - stars[i].x) * speed;
        stars[i].y += (stars[i].targetY - stars[i].y) * speed;
        stars[i].z += (stars[i].targetZ - stars[i].z) * speed;
    }

    // 更新小行星带的旋转角度
    for (int i = 0; i < ASTEROID_COUNT; ++i) {
        asteroidAngle[i] += 5.0f; // 调整旋转速度
        if (asteroidAngle[i] >= 360.0f) asteroidAngle[i] = 0.0f;
    }

    // 更新太阳纹理索引
    //currentSunTextureIndex = (currentSunTextureIndex + 1) % sun_texture_count;
    // 更新混合因子
    blendFactor += blendStep;
    if (blendFactor >= 1.0f) {
        blendFactor = 0.0f;
        currentSunTextureIndex = nextSunTextureIndex;
        nextSunTextureIndex = (nextSunTextureIndex + 1) % sun_texture_count;
    }

    // 更新计时器
    
        displayTimer++;
        if (displayTimer >= 300) { // 假设帧率为 60fps，五秒为 300 帧
            currentDisplayPlanet = NULL;
            displayTimer = 0;
        }
    
    glutPostRedisplay(); // 发送重绘请求
}

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowPosition(400, 200);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenGL光照演示");

    glewInit();
    
    //播放背景音乐
    music.initializeAudio();
    music.play_wav();

    init();//创造光源
   // initTextures();
   
    // 初始化小行星带
    for (int i = 0; i < ASTEROID_COUNT; ++i) {
        // 随机生成小行星的角度
        float angle = (float)(rand() % 360) * M_PI / 180.0f;
        // 随机生成小行星到中心的距离，模拟环形分布
        float distance = (float)(rand() % 100) / 100.0f * 1.0f + 6.7f; // 距离范围在 6.6到 7.9 之间,火星与木星
        asteroidX[i] = cos(angle) * distance;
        asteroidY[i] = 0.0f; // 假设小行星带在 XY 平面上
        asteroidZ[i] = sin(angle) * distance;

        // 随机生成小行星的大小
        asteroidSize[i] = (float)(rand() % 10) / 1000.0f * 5.0f + 0.001f; // 大小范围在 0.001 到 0.006 之间

        // 初始化旋转角度
        asteroidAngle[i] = 0.0f;
    }

    // 初始化星星的位置
    for (int i = 0; i < STAR_COUNT; ++i) {
        stars[i].x = (float)(rand() % 200 - 100) / 100.0f * 10.0f;
        stars[i].y = (float)(rand() % 200 - 100) / 100.0f * 10.0f;
        stars[i].z = (float)(rand() % 200 - 100) / 100.0f * 10.0f;
        stars[i].isGathered = false; // 初始状态为分散
        stars[i].targetX = stars[i].x;
        stars[i].targetY = stars[i].y;
        stars[i].targetZ = stars[i].z;
    }

    glutDisplayFunc(&myDisplay);
    glutIdleFunc(&myIdle);

    //星星在鼠标附近聚集
    glutMotionFunc(mouseMotion);//鼠标的主动移动事件

    //跟随鼠标移动查看轨道
    //glutPassiveMotionFunc(mouseMotion);//当鼠标在窗口内移动但没有按下任何鼠标按键时，该回调函数会被调用
       glutMouseFunc(mouse);

    glutKeyboardFunc(keyboard); // 注册键盘回调函数

    glGetString(GL_VERSION);
    const char* version = (const char*)glGetString(GL_VERSION);
    std::cout << "OpenGL Version: " << version << std::endl;


    glutMainLoop(); 
    music.deinit();
    return 0;
}
