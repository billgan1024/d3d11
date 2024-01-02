#pragma once
#include "pch.h"
struct float3 {
  float x, y, z;
  float3 operator+(float3);
  float3 operator-(float3);
  float3(float, float, float);
  friend float3 operator*(float, float3);
  float3 operator/(float);
};

struct float4x4 {
  float m[4][4];
  float *operator[](int);
  float4x4(float, float, float, float,
           float, float, float, float,
           float, float, float, float,
           float, float, float, float);
  static float4x4 perspective(float, float, float);
  static float4x4 identity;
};
