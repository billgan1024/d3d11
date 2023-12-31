#include "basic.hlsli"
#include "utils.hlsli"

// #define LIGHT spherical(0.0, radians(-45))
// #define COLOR float3(1.0, 0.0, 0.0)

float4 basic_ps(vertex input) : SV_TARGET {
  float3 light = spherical(0.0, radians(-45));
  float3 color = float3(1.0, 0.0, 0.0);

  return saturate(dot(input.normal, light)) * float4(color, 1.0);
}