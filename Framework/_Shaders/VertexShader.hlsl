//struct VertexInput
//{
//    float4 Position : Position;
//};

//struct VertexOutput
//{
//    float4 Position : SV_Position;
//};

//VertexOutput VS(VertexInput Input)
//{
//    VertexOutput output;
//    output.Position = Input.Position;
    
    
    
//    return output;
//}

////float4 PS(VertexOutput Input) : SV_Target
////{
////    return float4(1, 0, 0, 1);
////}

// ¡§¡° Ω¶¿Ã¥ı
struct VS_INPUT
{
    float3 position : POSITION;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.position = float4(input.position, 1.0f);
    return output;
}

// «»ºø Ω¶¿Ã¥ı
float4 PS() : SV_Target
{
    return float4(1.0f, 1.0f, 1.0f, 1.0f); // »Úªˆ
}