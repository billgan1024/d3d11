


// Some very barebones but fast atmosphere approximation
float3 extra_cheap_atmosphere(float3 raydir, float3 sundir) {
  sundir.y = max(sundir.y, -0.07);
  float special_trick = 1.0 / (raydir.y * 1.0 + 0.1);
  float special_trick2 = 1.0 / (sundir.y * 11.0 + 1.0);
  float raysundt = pow(abs(dot(sundir, raydir)), 2.0);
  float sundt = pow(max(0.0, dot(sundir, raydir)), 8.0);
  float mymie = sundt * special_trick * 0.2;
  float3 suncolor = lerp(float3(1.0), max(float3(0.0), float3(1.0) - float3(5.5, 13.0, 22.4) / 22.4), special_trick2);
  float3 bluesky= float3(5.5, 13.0, 22.4) / 22.4 * suncolor;
  float3 bluesky2 = max(float3(0.0), bluesky - float3(5.5, 13.0, 22.4) * 0.002 * (special_trick + -6.0 * sundir.y * sundir.y));
  bluesky2 *= special_trick * (0.24 + raysundt * 0.24);
  return bluesky2 * (1.0 + 1.0 * pow(1.0 - raydir.y, 3.0)) + mymie * suncolor;
} 

float3 dir_from_spherical(float theta, float phi) {
  return float3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));
}

// Calculate where the sun should be, it will be moving around the sky
float3 getSunDirection() {
  return normalize(float3(sin(iTime * 0.1), 1.0, cos(iTime * 0.1)));
}

// Get atmosphere color for given direction
float3 getAtmosphere(float3 dir) {
   return extra_cheap_atmosphere(dir, getSunDirection()) * 0.5;
}

// Get sun color for given direction
float getSun(float3 dir) { 
  return pow(max(0.0, dot(dir, getSunDirection())), 720.0) * 210.0;
}

// only need to pass rotation obtained from view matrix

cbuffer Scene : register(b1) {
  float3 sun_direction;
}

cbuffer Camera : register(b0) {
  float3x3 rotation;
}

