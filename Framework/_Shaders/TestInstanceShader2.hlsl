struct VertexInstancing
{
    float4 Position : POSITION0;
    float2 UV : UV;
    
    float4 Matrix1 : INST_POSITION0;
    float4 Matrix2 : INST_POSITION1;
    float4 Matrix3 : INST_POSITION2;
    float4 Matrix4 : INST_POSITION3;
};

struct VertexOutput
{
    float4 Position : SV_POSITION;
    float2 UV : TEXCOORD0;
    float4 wvpPosition : POSITION0;
};

cbuffer MaterialBuffer : register(b2)
{
    float4 Diffuse;
    float4 Specular;
    float4 Ambient;
    float4 Emissive;
    
    float Shininess;
}

cbuffer ViewProjectionBuffer : register(b1)
{
    matrix View;
    matrix InvView;
    matrix Projection;
}

cbuffer WorldBuffer : register(b0)
{
    matrix World;
}

SamplerState Samp : register(s0);
Texture2D DiffuseMap : register(t0);

VertexOutput VS(VertexInstancing input)
{
    VertexOutput output;
    matrix world;
    world._11_12_13_14 = input.Matrix1;
    world._21_22_23_24 = input.Matrix2;
    world._31_32_33_34 = input.Matrix3;
    world._41_42_43_44 = input.Matrix4;
    
    output.Position = mul(input.Position, world);
    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    output.wvpPosition = output.Position;
    
    output.UV = input.UV;
    
    return output;
}

float4 PS(VertexOutput input) : SV_Target0
{
    float4 result = DiffuseMap.Sample(Samp, input.UV);
    
    return result;
}