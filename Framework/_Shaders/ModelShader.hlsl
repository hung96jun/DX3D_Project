#include "Global/Global.hlsli"

//VertexMeshOutput VS(VertexMeshInput input)
//{
//    VertexMeshOutput output;
//    output.OPosition = input.Position.xyz;
    
//    output.Position = mul(input.Position, World);
//    output.WPosition = output.Position.xyz;
    
//    output.Position = mul(output.Position, View);
//    output.Position = mul(output.Position, Projection);
//    output.WVPPosition = output.Position;
//    output.WVPPosition_Sub = output.Position;
    
//    output.SPositoin = mul(input.Position, World);
//    output.SPositoin = mul(output.SPositoin, Shadow.View);
//    output.SPositoin = mul(output.SPositoin, Shadow.Projection);
    
//    output.Normal = mul(input.Normal, (float3x3) World);
//    output.Tangent = mul(input.Tangent, (float3x3) World);
    
//    output.UV = input.UV;
//    //output.Color = input.Color;
    
//    //output.Culling.x = dot(float4(output.wPosition, 1), Culling[0]);
//    //output.Culling.y = dot(float4(output.wPosition, 1), Culling[1]);
//    //output.Culling.z = dot(float4(output.wPosition, 1), Culling[2]);
//    //output.Culling.w = dot(float4(output.wPosition, 1), Culling[3]);
//    //
//    //output.Clipping = float4(0, 0, 0, 0);
//    //output.Clipping.x = dot(float4(output.wPosition, 1), Clipping);
    
//    return output;
//}

//float4 PS(VertexMeshOutput input) : SV_Target0
//{
//    MaterialDesc material;
//    Texture(material.Diffuse, DiffuseMap, input.UV);
//    Texture(material.Specular, SpecularMap, input.UV);
    
//    MaterialDesc result;
//    ComputeLight(result, input.Normal, input.WPosition);
    
//    return float4(MaterialToColor(result), 1.0f);
//}

VertexMeshOutput VS(VertexMeshInput input)
{
    VertexMeshOutput output;
    output.Position = mul(input.Position, World);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    output.Normal = float3(1.0f, 1.0f, 1.0f);
    output.Tangent = float3(1.0f, 1.0f, 1.0f);
    output.Binormal = float3(1.0f, 1.0f, 1.0f);
    
    output.UV = input.UV;
    
    return output;
}

float4 PS(VertexMeshOutput input) : SV_Target0
{
    //float4 result = DiffuseMap.Sample(Samp, input.UV);
    
    return float4(1.0f, 0.0f, 0.0f, 0.0f);
}