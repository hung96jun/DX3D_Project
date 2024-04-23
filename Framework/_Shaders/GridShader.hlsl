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

struct VertexInput
{
    float4 Position : POSITION0;
};

struct VertexOutput
{
    float4 Position : SV_POSITION0;
};

VertexOutput VS(VertexInput Input)
{
    VertexOutput output;
    output.Position = mul(Input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    return output;
}

float PS(VertexOutput Input) : SV_Target
{
    return float4(0.2f, 0.2f, 0.2f, 1.0f);
}

RasterizerState RS
{
    FillMode = WireFrame;
};