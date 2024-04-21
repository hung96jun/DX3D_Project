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
    float4 Position : Position;
    float4 Color : COLOR;
};

struct VertexOutput
{
    float4 Position : SV_Position;
    float4 Color : COLOR;
};

VertexOutput VS(VertexInput Input)
{
    VertexOutput output;
    //output.Position = Input.Position;
    
    output.Position = mul(Input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    output.Color = Input.Color;
    
    return output;
}

float4 PS(VertexOutput Input) : SV_Target
{
    return Input.Color;
}