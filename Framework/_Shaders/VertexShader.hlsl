struct VertexInput
{
    float4 Position : Position;
};

struct VertexOutput
{
    float4 Position : SV_Position;
};

VertexOutput VS(VertexInput Input)
{
    VertexOutput output;
    output.Position = Input.Position;
    
    return output;
}

//float4 PS(VertexOutput Input) : SV_Target
//{
//    return float4(1, 0, 0, 1);
//}