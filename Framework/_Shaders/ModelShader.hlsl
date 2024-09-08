struct VertexInput
{
    float4 Position : POSITION;
    float2 UV : UV;
    
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float4 Indices : BLENDINDICES;
    float4 Weights : BLENDWEIGHTS;
};

struct VertexOutput
{
    float4 Position : SV_POSITION0;
    float2 UV : UV;
    
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;
};

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

SamplerState Samp : register(s0);
Texture2D DiffuseMap : register(t0);

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    //output.Normal = float3(1.0f, 1.0f, 1.0f);
    //output.Tangent = float3(1.0f, 1.0f, 1.0f);
    //output.Binormal = float3(1.0f, 1.0f, 1.0f);
    
    output.UV = input.UV;
    
    return output;
}

float4 PS(VertexOutput input) : SV_Target0
{
    float4 result = DiffuseMap.Sample(Samp, input.UV);
    
    return result;
}