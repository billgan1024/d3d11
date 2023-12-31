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

float4x4 float4x4::identity = float4x4{1, 0, 0, 0,
                                       0, 1, 0, 0,
                                       0, 0, 1, 0,
                                       0, 0, 0, 1};

float4x4::float4x4(initializer_list<float> list) {
  for (int i = 0; i < list.size(); i++) {
    m[i / 4][i % 4] = *(list.begin() + i);
  }
}

float4x4 float4x4::perspective(float fov, float aspect, float near) {
  // in 3d space i prefer x right, y forward
  // however, in clip/NDC space, x is right, y is up

  // analyzing perspective matrices, assuming y is forward:
  // clip z = near / view y
  // clip x, clip y = scale1 * view x, scale2 * view z
  // remember that a 4x4 matrix M represents the function (x, y, z) -> M * (x, y, z, 1) / w
  return float4x4{
    1 / tan(fov / 2), 0, 0, 0,
    0, 0, aspect / tan(fov / 2), 0,
    0, 0, 0, near,
    0, 1, 0, 0};
}