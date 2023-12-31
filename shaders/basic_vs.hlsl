#include "basic.hlsli"

cbuffer scene : register(b0) {
  float4x4 view_projection;
}

vertex basic_vs(float3 position : POSITION, float3 normal : NORMAL) {
  vertex result;
  result.clip = mul(view_projection, float4(position, 1.0));
  result.normal = normal;
  return result;
}