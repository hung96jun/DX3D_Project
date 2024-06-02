#include "Headers/VertexHeader.hlsli"
#include "Headers/PixelHeader.hlsli"

VertexUVOutput VS(VertexUVInput input)
{
    VertexUVOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    output.wvpPosition = output.Position;
    
    output.UV = input.UV;
    
    return output;
}

float4 PS(VertexUVOutput input) : SV_Target0
{
    float4 result = DiffuseMap.Sample(Samp, input.UV);
    
    return result;    
}