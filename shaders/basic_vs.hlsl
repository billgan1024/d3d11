#include "basic.hlsl"

cbuffer PerFrameVS : register(b0) {
  float4x4 view_projection;
}

vertex basic_vs(float3 position : Position, float3 normal : Normal) {
  vertex result;
  result.clip = mul(view_projection, float4(position, 1.0));
  result.normal = normal;
  return result;
}