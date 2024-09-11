///////////////////////////////////////////////////////////////////////////////
// Structs
///////////////////////////////////////////////////////////////////////////////
struct VertexColorOutput
{
    float4 Position : SV_Position;
    float4 Color : COLOR0;
    float4 wvpPosition : POSITION0;
};

struct VertexUVOutput
{
    float4 Position : SV_Position;
    float2 UV : TEXCOORD0;
    float4 wvpPosition : POSITION0;
};

struct VertexMeshOutput
{
    float4 Position : SV_POSITION;
    float2 UV : UV;
    
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;
};

//struct MaterialDesc
//{
//    float4 Ambient;
//    float4 Diffuse;
//    float4 Specular;
//    float4 Emissive;
//};

//struct LightDesc
//{
//    float4 Ambient;
//    float4 Specular;
//    float3 Direction;
//    float Padding;
//    float3 Position;
//};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// SamplerStates
///////////////////////////////////////////////////////////////////////////////
SamplerState Samp : register(s0);

SamplerState LinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Warp;
};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Textures
///////////////////////////////////////////////////////////////////////////////
Texture2D DiffuseMap : register(t0);
///////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////
//// Functions
/////////////////////////////////////////////////////////////////////////////////
//void Texture(inout float4 color, Texture2D t, float2 uv, SamplerState samp)
//{
//    float4 sampling = t.Sample(samp, uv);
    
//    [flatten]
//    if(any(sampling.rgb))
//        color = color * sampling;
//}

//void Texture(inout float4 color, Texture2D t, float2 uv)
//{
//    Texture(color, t, uv, LinearSampler);

//}

//void ComputeLight(out MaterialDesc output, float3 normal, float3 wPosition)
//{
//    output = (MaterialDesc) 0;
    
//    output.Ambient = GlobalLight.Ambient * Material.
//}
/////////////////////////////////////////////////////////////////////////////////