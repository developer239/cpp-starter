#pragma once

#include <cmath>

struct Vec2 {
  float x;
  float y;

  Vec2(float x = 0, float y = 0) : x(x), y(y) {}

  Vec2 ScaleAndTranslate(int windowWidth, int windowHeight) const {
    return {x + windowWidth / 2, y + windowHeight / 2};
  }

  float Length() const { return sqrt(x * x + y * y); }

  Vec2 operator+(const Vec2& other) const { return {x + other.x, y + other.y}; }

  Vec2 operator-(const Vec2& other) const { return {x - other.x, y - other.y}; }

  Vec2 operator*(float scalar) const { return {x * scalar, y * scalar}; }

  Vec2 operator/(float scalar) const { return {x / scalar, y / scalar}; }
};
