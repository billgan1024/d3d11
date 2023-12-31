#include "common.hlsli"

cbuffer scene : register(b0) {
  float4x4 view_projection;
}

struct vertex {
  float4 clip : SV_POSITION;
  float3 normal : NORMAL;
};

#define LIGHT spherical(0.0, radians(-45))
#define COLOR float3(1.0, 0.0, 0.0)

float4 basic_ps(vertex input) : SV_TARGET {
  return saturate(dot(input.normal, LIGHT)) * float4(COLOR, 1.0);
}

vertex basic_vs(float3 position : POSITION, float3 normal : NORMAL) {
  vertex result;
  result.clip = mul(view_projection, float4(position, 1.0));
  result.normal = normal;
  return result;
}a