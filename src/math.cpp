#include "math.h"

float3 float3::operator+(float3 rhs) {
  return {x + rhs.x, y + rhs.y, z + rhs.z};
}

float3 float3::operator-(float3 rhs) {
  return {x - rhs.x, y - rhs.y, z - rhs.z};
}

float3 operator*(float c, float3 rhs) {
  return {c * rhs.x, c * rhs.y, c * rhs.z};
}

float3 float3::operator/(float c) {
  return {x / c, y / c, z / c};
}

float *float4x4::operator[](int i) {
  return m[i];
}

float4x4 float4x4::identity{1, 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            0, 0, 0, 1};

float4x4 float4x4::perspective(float fov, float aspect, float near) {
  // z -> n/z for reverse + infinite far plane
  // need to scale x, y by some constants, then divide by z
  // the function x -> x/z implies at z, the extents in view space are [-z, z].
  // at z = near, the horizontal extents are [-h, h] where h = near * tan(fov/2)
  // ch/near = 1
  // c = 1/tan(fov/2)
  // at z = near, the vertical extents are [-v, v] where v = near * tan(fov/2) / aspect
  // cv/near = 1
  // c = near/v = aspect/tan(fov/2)
  return {
    1 / tan(fov / 2), 0, 0, 0,
    0, aspect / tan(fov / 2), 0, 0,
    0, 0, near, 0,
    0, 0, 1, 0};
}