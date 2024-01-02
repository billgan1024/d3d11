#include "math.h"

float3 float3::operator+(float3 rhs) {
  return float3(x + rhs.x, y + rhs.y, z + rhs.z);
}

float3 float3::operator-(float3 rhs) {
  return float3(x - rhs.x, y - rhs.y, z - rhs.z);
}

float3::float3(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

float3 operator*(float c, float3 rhs) {
  return float3(c * rhs.x, c * rhs.y, c * rhs.z);
}

float3 float3::operator/(float c) {
  return float3(x / c, y / c, z / c);
}

float *float4x4::operator[](int i) {
  return m[i];
}


float4x4 float4x4::identity = float4x4(1, 0, 0, 0,
                                       0, 1, 0, 0,
                                       0, 0, 1, 0,
                                       0, 0, 0, 1);


float4x4 float4x4::perspective(float fov, float aspect, float near) {
  // in 3d space i prefer x right, y forward
  // however, in clip/NDC space, x is right, y is up

  // analyzing perspective matrices, assuming y is forward:
  // clip z = near / view y
  // clip x, clip y = scale1 * view x, scale2 * view z
  // remember that a 4x4 matrix M represents the function (x, y, z) -> M * (x, y, z, 1) / w
  return float4x4(
    1 / tan(fov / 2), 0, 0, 0,
    0, 0, aspect / tan(fov / 2), 0,
    0, 0, 0, near,
    0, 1, 0, 0);
}


float4x4::float4x4(float m00, float m01, float m02, float m03,
                   float m10, float m11, float m12, float m13,
                   float m20, float m21, float m22, float m23,
                   float m30, float m31, float m32, float m33) {
  m[0][0] = m00;
  m[0][1] = m01;
  m[0][2] = m02;
  m[0][3] = m03;
  m[1][0] = m10;
  m[1][1] = m11;
  m[1][2] = m12;
  m[1][3] = m13;
  m[2][0] = m20;
  m[2][1] = m21;
  m[2][2] = m22;
  m[2][3] = m23;
  m[3][0] = m30;
  m[3][1] = m31;
  m[3][2] = m32;
  m[3][3] = m33;
}