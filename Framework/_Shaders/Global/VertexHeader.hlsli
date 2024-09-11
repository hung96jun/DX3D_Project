///////////////////////////////////////////////////////////////////////////////
// Structs
///////////////////////////////////////////////////////////////////////////////
struct VertexColorInput
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
};

struct VertexUVInput
{
    float4 Position : POSITION0;
    float2 UV : UV;
};

struct VertexMeshInput
{
    float4 Position : POSITION;
    float2 UV : UV;
    
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    
    float4 Indices : BLENDINDICES;
    float4 Weights : BLENDWEIGHTS;
};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Constant Buffers
///////////////////////////////////////////////////////////////////////////////
cbuffer WorldBuffer : register(b0)
{
    matrix World;
}

cbuffer ViewProjectionBuffer : register(b1)
{
    matrix View;
    matrix InvView;
    matrix Projection;
}

cbuffer MaterialBuffer : register(b2)
{
    float4 Diffuse;
    float4 Specular;
    float4 Ambient;
    float4 Emissive;
    
    float Shininess;
}
///////////////////////////////////////////////////////////////////////////////
