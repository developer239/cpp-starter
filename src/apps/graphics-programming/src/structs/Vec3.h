#pragma once

#include <cmath>

struct Vec3 {
  float x;
  float y;
  float z;

  Vec3(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

  float Length() { return sqrt(x * x + y * y + z * z); }

  Vec3 rotateX(float angle) {
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    float y1 = y * cosAngle - z * sinAngle;
    float z1 = y * sinAngle + z * cosAngle;

    return {x, y1, z1};
  }

  Vec3 rotateY(float angle) {
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    float x1 = x * cosAngle - z * sinAngle;
    float z1 = x * sinAngle + z * cosAngle;
    x = x1;
    z = z1;

    return {x1, y, z1};
  }

  Vec3 rotateZ(float angle) {
    float cosAngle = cos(angle);
    float sinAngle = sin(angle);
    float x1 = x * cosAngle - y * sinAngle;
    float y1 = x * sinAngle + y * cosAngle;
    x = x1;
    y = y1;

    return {x1, y1, z};
  }

  Vec3 Normalize() {
    float length = Length();
    return {x / length, y / length, z / length};
  }

  Vec3 CrossProduct(Vec3 other) {
    return {
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x};
  }

  float DotProduct(Vec3 other) {
    return x * other.x + y * other.y + z * other.z;
  }

  Vec3 operator+(const Vec3& other) const {
    return {x + other.x, y + other.y, z + other.z};
  }

  Vec3 operator-(const Vec3& other) const {
    return {x - other.x, y - other.y, z - other.z};
  }

  Vec3 operator*(const Vec3& other) const {
    return {x * other.x, y * other.y, z * other.z};
  }

  Vec3 operator/(const Vec3& other) const {
    return {x / other.x, y / other.y, z / other.z};
  }
};
