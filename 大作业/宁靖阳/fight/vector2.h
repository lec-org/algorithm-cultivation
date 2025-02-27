#pragma once
#include <cmath>

class Vector2 {
public:
	Vector2&& operator+(const Vector2& other) const;
	Vector2&& operator-(const Vector2& other) const;
	void operator+=(const Vector2& other);
	void operator-=(const Vector2& other);

	float operator*(const Vector2& other) const;
	Vector2&& operator*(const float val) const;
	void operator*=(const float val);

public:
	float lenth();
	Vector2&& normalize();
public:
	float x = 0, y = 0;

public:
	Vector2() = default;
	Vector2(float x, float y);
};
