struct VertexInstancing
{
    float4 Position : POSITION0;
    float2 UV : UV;
    
    float4 Vec1 : INST_POSITIONT1;
    float4 Vec2 : INST_POSITIONT2;
    float4 Vec3 : INST_POSITIONT3;
    float4 Vec4 : INST_POSITIONT4;
    
    matrix World : Transform;
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
    input.World._11_12_13_14 = input.Vec1;
    input.World._21_22_23_24 = input.Vec2;
    input.World._31_32_33_34 = input.Vec3;
    input.World._41_42_43_44 = input.Vec4;
    
    output.Position = mul(input.Position, input.World);
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