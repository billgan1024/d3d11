struct vertex {
  float4 clip_position : SV_POSITION;
	float4 color : COLOR;
};

float4 default_ps(vertex input) : SV_TARGET {
  // everything in input (except clip_position) is an interpolated value
  return input.color;
}

vertex default_vs(float3 clip_position : POSITION, float4 color : COLOR) {
  vertex result;
  result.clip_position = float4(clip_position, 1.0f);
  result.color = color;
  return result;
}