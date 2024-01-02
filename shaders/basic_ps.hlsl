#include "basic.hlsl"
#include "utils.hlsl"

cbuffer PerFramePS : register(b0) {
  float3 light;
}

// material = per-mesh parameters
cbuffer Material : register(b1) {
  float3 color;
}

// #define LIGHT spherical(0.0, radians(-45))
// #define COLOR float3(1.0, 0.0, 0.0)

float4 basic_ps(vertex input) : SV_Target {
  // float3 light = spherical(0.0, radians(-45));

  return saturate(dot(input.normal, light)) * float4(color, 1.0);
}