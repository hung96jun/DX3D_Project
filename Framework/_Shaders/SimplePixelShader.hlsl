struct VertexOutput
{
    float4 Position : SV_Position;
    float4 Color : COLOR;
};

float4 PS(VertexOutput Input) : SV_Target
{
    return Input.Color;
}