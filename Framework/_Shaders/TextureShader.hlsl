cbuffer WorldBuffer : register(b0)
{
    matrix World;
}

cbuffer ViewBuffer : register(b1)
{
    matrix View;
    matrix InvView;
}

cbuffer ProjectionBuffer : register(b2)
{
    matrix Projection;
}

SamplerState Samp : register(s0);
//SamplerState LinearSampler
//{
//    Filter = MIN_MAG_MIP_LINEAR;
//};

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
    //if (input.UV.x < 0.5f)
    //    return float4(1.0f, 0.5f, 0.5f, 1.0f);
    
    //return float4(input.UV.x, input.UV.y, 0.0f, 1.0f);
    //
    //return float4(input.Color.xyz, 1.0f);
    
    //return float4(0.5f, 0.5f, 1.0f, 1.0f);
    //return float4(input.UV, 1.0f);
    return DiffuseMap.Sample(Samp, input.UV);
}