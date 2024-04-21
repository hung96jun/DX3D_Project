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

Texture2D DiffuseMap : register(t0);

struct VertexInput
{
    float4 Position : Position;
    float2 UV : UV;
    float4 Color : Color;
};

struct VertexOutput
{
    float4 Position : SV_Position;
    float2 UV : UV;
    float4 Color : Color;
};

VertexOutput VS(VertexInput input)
{
    VertexOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);

    output.Color = float4(input.UV.xy * 100, 0.0f, 1.0f);
    output.UV = input.UV;
    
    return output;
}

float4 PS(VertexOutput input) : SV_Target
{
    //if (input.UV.x < 0.5f)
    //    return float4(1.0f, 0.5f, 0.5f, 1.0f);
    
    //return float4(input.UV.x * 2.5, input.UV.y * 2.5, 0.0f, 1.0f);
    //
    //return float4(input.Color.xyz, 1.0f);
    
    return DiffuseMap.Sample(Samp, input.UV);
}