#include "skybox.hlsl"

// from nvidia: minimize number of cbuffer updates
// but split them and use "map_discard" whenever possible for performance (ok this is pretty contradictory)
cbuffer SceneMatrices : register(b0) {
  float4x4 view_projection;
}

vertex skybox_vs(float3 position : Position) {
  vertex result;
  result.clip = mul(float4(position, 1.0));
  result.position = mul(world, float4(position, 1.0)).xyz;
  return result;
}
