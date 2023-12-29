#pragma once
struct float3 {
  float x, y, z;
  float3 operator+(float3 rhs);
  float3 operator-(float3 rhs);
  friend float3 operator*(float c, float3 rhs);
  float3 operator/(float c);
};

struct float4x4 {
  float m[4][4];

  // note that arrays are just pointers
  float *operator[](int i);
  // fov = horizontal fov, aspect = width / height
  static float4x4 perspective(float fov, float aspect, float near);
  static float4x4 identity;
};