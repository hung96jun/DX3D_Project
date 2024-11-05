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
///////////////////////////////////////////////////////////////////////////////
    float4 Position : SV_POSITION;
    float2 UV : UV;
    
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;
///////////////////////////////////////////////////////////////////////////////    
    //float4 Position : SV_Position;
    //float3 OPosition : POSITION0;
    //float3 WPosition : POSITION1;
    //float4 WVPPosition : POSITION2;
    //float4 WVPPosition_Sub : POSITION3;
    //float4 SPositoin : POSITION4;
    
    //float3 Normal : NORMAL;
    //float3 Tangent : TANGENT;
    //float2 UV : UV;
    //float4 Color : COLOR;
    
    //uint TargetIndex : SV_RenderTargetArrayIndex;
    
    //float4 Culling : SV_CullDistance;
    //float4 Cliping : SV_ClipDistance;
///////////////////////////////////////////////////////////////////////////////
};