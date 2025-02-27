#ifndef VEC3_H
#define VEC3_H

#define M_PI 3.141592
struct vec3 {
    float x, y, z;

    // 构造函数
    vec3(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) : x(_x), y(_y), z(_z) {}
};

// 自定义 mix 函数
vec3 mix(const vec3& a, const vec3& b, float factor);

#endif // VEC3_H