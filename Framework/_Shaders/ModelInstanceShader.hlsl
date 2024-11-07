#include "Global/Global.hlsli"

struct VertexMeshInstancingInput
{
    float4 Position : POSITION;
    float2 UV : UV;
    
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    
    float4 Indices : BLENDINDICES;
    float4 Weights : BLENDWEIGHTS;
    
    float4 Matrix1 : INST_POSITION0;
    float4 Matrix2 : INST_POSITION1;
    float4 Matrix3 : INST_POSITION2;
    float4 Matrix4 : INST_POSITION3;
};

VertexMeshOutput VS(VertexMeshInstancingInput input)
{
    VertexMeshOutput output;
    matrix world;
    world = matrix(input.Matrix1, input.Matrix2, input.Matrix3, input.Matrix4);
    
    output.Position = mul(input.Position, World);
    
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    
    output.Normal = mul(input.Normal, (float3x3) World);
    output.Tangent = mul(input.Tangent, (float3x3) World);
    output.Binormal = float3(1.0f, 1.0f, 1.0f);
  
    output.UV = input.UV;
  
    return output;
}

float4 PS(VertexMeshOutput input) : SV_Target0
{
    return float4(1.0f, 0.2f, 0.2f, 1.0f);
}
