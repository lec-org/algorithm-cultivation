#include "vector2.h"

Vector2&& Vector2::operator+(const Vector2& other) const {

    return { x + other.x, y + other.y };

}

Vector2&& Vector2::operator-(const Vector2& other) const {

    return { x - other.x, y - other.y };
}

void Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
}

void Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
}

float Vector2::operator*(const Vector2& other) const {

    return x * other.x + y * other.y;
}

Vector2&& Vector2::operator*(const float val) const {

    return { x * val, y * val };
}

void Vector2::operator*=(const float val) {
    x *= val;
    y *= val;
}

float Vector2::lenth() {

    return sqrt(x * x + y * y);
}

Vector2&& Vector2::normalize() {

    auto lenth = this->lenth();

    if (lenth == 0)
        return Vector2(0, 0);

    return { x / lenth, y / lenth };
}

Vector2::Vector2(float x, float y) :x(x), y(y) {
}

