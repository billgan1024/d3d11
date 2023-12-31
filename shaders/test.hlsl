struct VS_INPUT
{
    float4 Pos : POSITION;
    float3 Normal : NORMAL;
};

struct GS_INPUT
{
    float4 Pos : POSITION;
};

struct GS_OUTPUT
{
    float4 Pos : SV_POSITION;
};


//--------------------------------------------------------------------------------------
// Name: PassThroughVS
// Desc: VS that simply passes the position to the GS
//--------------------------------------------------------------------------------------
GS_INPUT PassThroughVS(VS_INPUT In)
{
    GS_INPUT Out;
    Out.Pos = In.Pos;
    return Out;
}
[maxvertexcount(2)]
void normals(triangle GS_INPUT In[3], inout LineStream<GS_OUTPUT> stream)
{
    // // Get the local positions of the vertices of the input triangle
    // float4 v0 = In[0].Pos;
    // float4 v1 = In[1].Pos;
    // float4 v2 = In[2].Pos;
    
    // // Sides of the input triangle
    // float3 e1 = normalize(v1 - v0).xyz;
    // float3 e2 = normalize(v2 - v0).xyz;
    
    // // The normal is the cross product of the sides.
    // // v0, v1 and v2 in clockwise order so it's e1 x e2
    // float3 normal = normalize(cross(e1, e2));
    
    // // Show the normal at the center of the triangle
    // float4 center = (v0 + v1 + v2) / 3.0;
	
    // // We need to transform the line segment (two points) representing
    // // the normal from local to clip space.
    // float4x4 mVP = mul(mWorld, mul(mView, mProjection));
    
    // // Emit the two points of a line segment representing the normal to the input triangle
    // for (int i = 0; i < 2; ++i)
    // {
    //     GS_OUTPUT v;
    //     center.xyz += normal * 0.3 * i;
    //     v.Pos = mul(center, mVP);
    //     stream.Append(v);
    // }
}