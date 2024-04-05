matrix World, View, Projection;

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
    output.Position = mul(Input.Position, World);
    output.Position = mul(Input.Position, View);
    output.Position = mul(Input.Position, Projection);
    
    output.Color = Input.Color;
    
    return output;
}

float4 PS(VertexOutput Input) : SV_Target
{
    return Input.Color;
}