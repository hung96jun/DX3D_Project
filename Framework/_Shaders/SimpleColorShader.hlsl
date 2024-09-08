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

struct VertexInput
{
    float4 Position : POSITION0;
    float4 Color : COLOR;
};

struct VertexOutput
{
    float4 Position : SV_POSITION0;
    float4 Color : COLOR;
};

VertexOutput VS(VertexInput Input)
{
    VertexOutput output;
    output.Position = mul(Input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    output.Color = Input.Color;
    
    return output;
}

float4 PS(VertexOutput Input) : SV_Target
{
    return float4(1.0f, 1.0f, 1.0f, 1.0f);
}

RasterizerState RS
{
    FillMode = WireFrame;
};