#pragma once
struct float3 {
  float x, y, z;
  float3 operator+(float3 rhs);
  float3 operator-(float3 rhs);
  float3(float x, float y, float z);
  friend float3 operator*(float c, float3 rhs);
  float3 operator/(float c);
};

struct float4x4 {
  // c has support for multidimensional arrays
  // the rule is that T a[n] is a new type representing n Ts in a row
  // a[i] is the ith element of the array
  float m[4][4];
  // can't return arrays from fun
  float *operator[](int i);
  // fov = horizontal fov, aspect = width / height
  float4x4(initializer_list<float> list);
  static float4x4 perspective(float fov, float aspect, float near);
  static float4x4 identity;
};