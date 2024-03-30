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
    output.Position = Input.Position;
    output.Color = Input.Color;    
    
    return output;
}

//float4 PS(VertexOutput Input) : SV_Target
//{
//    return float4(1, 0, 0, 1);
//}