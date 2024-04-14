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
    
    //output.Position = mul(Input.Position, mul(World, mul(View, Projection)));
    
    //output.Color = float4(Projection._11, Projection._12, Projection._13, 1.0f);
    //output.Color = float4(Projection._21, Projection._22, Projection._23, 1.0f);
    //output.Color = float4(Projection._31, Projection._32, Projection._33, 1.0f);
    output.Color = Input.Color;
    
    return output;
}

float4 PS(VertexOutput Input) : SV_Target
{
    return Input.Color;
}