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

    return result;    
}