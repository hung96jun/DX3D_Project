cbuffer WorldBuffer : register(b0)
{
    matrix World;
}

//cbuffer ViewBuffer : register(b1)
//{
//    matrix View;
//    matrix InvView;
//}

//cbuffer ProjectionBuffer : register(b2)
//{
//    matrix Projection;
//}

cbuffer ViewProjectionBuffer : register(b1)
{
    matrix View;
    matrix InvView;
    matrix Projection;
}

cbuffer MaterialBuffer : register(b3)
{
    float4 Diffuse;
    float4 Specular;
    float4 Ambient;
    float4 Emissive;
    
    float Shininess;
}

SamplerState Samp : register(s0);
Texture2D DiffuseMap : register(t0);

struct VertexInput
{
    float4 Position : POSITION0;
    float2 UV : TEXCOORD0;
};

struct VertexOutput
{
    float4 Position : SV_POSITION0;
    float2 UV : TEXCOORD0;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    output.UV = input.UV;
    
    return output;
}

float4 PS(VertexOutput input) : SV_Target0
{
    float4 result = DiffuseMap.Sample(Samp, input.UV);
    //result = (result * Diffuse) + Ambient + Emissive;
    //result = Emissive;
    
    return result;
}