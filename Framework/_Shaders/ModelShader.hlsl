#include "Global/VertexHeader.hlsli"
#include "Global/PixelHeader.hlsli"

VertexMeshOutput VS(VertexMeshInput input)
{
    VertexMeshOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    //output.Normal = float3(1.0f, 1.0f, 1.0f);
    //output.Tangent = float3(1.0f, 1.0f, 1.0f);
    //output.Binormal = float3(1.0f, 1.0f, 1.0f);
    
    output.UV = input.UV;
    
    return output;
}

float4 PS(VertexMeshOutput input) : SV_Target0
{
    float4 result = DiffuseMap.Sample(Samp, input.UV);
    
    return result;
}