
float3 spherical(float theta, float phi) {
  // returns
  return float3(cos(theta) * cos(phi), sin(theta) * cos(phi), sin(phi));
  // return float3(cos(theta) * sin(phi), cos(phi), sin(theta) * sin(phi));
}