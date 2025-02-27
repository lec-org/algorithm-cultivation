#include"vec3.h"

vec3 mix(const vec3& a, const vec3& b, float factor) {
    return vec3(
        a.x + (b.x - a.x) * factor,
        a.y + (b.y - a.y) * factor,
        a.z + (b.z - a.z) * factor
    );
}