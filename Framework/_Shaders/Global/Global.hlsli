///////////////////////////////////////////////////////////////////////////////
// VS Structs
///////////////////////////////////////////////////////////////////////////////
struct VertexColorInput
{
    float4 Position : POSITION0;
    float4 Color : COLOR0;
};

struct VertexUVInput
{
    float4 Position : POSITION0;
    float2 UV : UV;
};

struct VertexTestInput
{
    float4 Position : POSITION;
    float2 UV : UV;
    
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    
    float4 Color : COLOR;
};

struct VertexMeshInput
{
    float4 Position : POSITION;
    float2 UV : UV;
    
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    
    float4 Indices : BLENDINDICES;
    float4 Weights : BLENDWEIGHTS;
};
///////////////////////////////////////////////////////////////////////////////
// PS Structs
///////////////////////////////////////////////////////////////////////////////
struct VertexColorOutput
{
    float4 Position : SV_Position;
    float4 Color : COLOR0;
    float4 wvpPosition : POSITION0;
};

struct VertexUVOutput
{
    float4 Position : SV_Position;
    float2 UV : TEXCOORD0;
    float4 wvpPosition : POSITION0;
};

struct VertexTestOutput
{
    float4 Position : SV_Position;
    float2 UV : TEXCOORD0;
    float4 wvpPosition : POSITION0;
    float3 WPosition : POSITION1;
    
    float3 Normal : Normal;
    float3 Tangent : Tangent;
    float4 Color : Color;
};

struct VertexMeshOutput
{
///////////////////////////////////////////////////////////////////////////////
    float4 Position : SV_POSITION;
    float2 UV : UV;
    
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 Binormal : BINORMAL;
///////////////////////////////////////////////////////////////////////////////    
    //float4 Position : SV_Position;
    //float3 OPosition : POSITION0;
    //float3 WPosition : POSITION1;
    //float4 WVPPosition : POSITION2;
    //float4 WVPPosition_Sub : POSITION3;
    //float4 SPositoin : POSITION4;
    
    //float3 Normal : NORMAL;
    //float3 Tangent : TANGENT;
    //float2 UV : UV;
    //float4 Color : COLOR;
    
    //uint TargetIndex : SV_RenderTargetArrayIndex;
    
    //float4 Culling : SV_CullDistance;
    //float4 Cliping : SV_ClipDistance;
///////////////////////////////////////////////////////////////////////////////
};
///////////////////////////////////////////////////////////////////////////////
// Structs
///////////////////////////////////////////////////////////////////////////////
struct MaterialDesc
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float4 Emissive;
};

struct LightDesc
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float3 Direction;
    float Padding;
    float3 Position;
};

struct ShadowDesc
{
    matrix View;
    matrix Projection;
    
    float2 MapSize;
    float Bias;
    
    uint Quality;
};
///////////////////////////////////////////////////////////////////////////////
// Constant Buffers
///////////////////////////////////////////////////////////////////////////////
//#include "Structs.hlsli"

cbuffer WorldBuffer : register(b0)
{
    matrix World;
}

cbuffer ViewProjectionBuffer : register(b1)
{
    matrix View;
    matrix InvView;
    matrix Projection;
}

cbuffer MaterialBuffer : register(b2)
{
    MaterialDesc Material;
}

cbuffer LightBuffer : register(b3)
{
    LightDesc GlobalLight;
}

cbuffer ShadowBuffer : register(b4)
{
    ShadowDesc Shadow;
}
///////////////////////////////////////////////////////////////////////////////
// SamplerStates
///////////////////////////////////////////////////////////////////////////////
SamplerState Samp : register(s0);

SamplerState LinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Warp;
};
///////////////////////////////////////////////////////////////////////////////
// Textures
///////////////////////////////////////////////////////////////////////////////
Texture2D DiffuseMap : register(t0);
Texture2D SpecularMap : register(t1);
Texture2D NormalMap : register(t2);
Texture2D ProjectionMap : register(t3);
Texture2D ShadowMap : register(t4);
///////////////////////////////////////////////////////////////////////////////
// Functions
///////////////////////////////////////////////////////////////////////////////
//#include "ConstantBuffers.hlsli"
//#include "SamplerStates.hlsli"
//#include "Textures.hlsli"

float4 Texture(float4 color, Texture2D t, float2 uv, SamplerState samp)
{
    float4 sampling = t.Sample(samp, uv);
    
    [flatten]
    if (any(sampling.rgb))
        color = color * sampling;
    
    return color;
}

float4 Texture(float4 color, Texture2D t, float2 uv)
{
    return Texture(color, t, uv, LinearSampler);
}
///////////////////////////////////////////////////////////////////////////////
float4 WorldPosition(float4 pos)
{
    return mul(pos, World);
}

float4 ViewProjection(float4 pos)
{
    return mul(pos, (View * Projection));
}

float3 WorldNormal(float3 normal)
{
    return mul(normal, (float3x3) World);
}

float3 WorldTangent(float3 tangent)
{
    return mul(tangent, (float3x3) World);
}

float3 ViewPosition()
{
    return InvView._41_42_43;
}
///////////////////////////////////////////////////////////////////////////////
//void ComputeLight(out MaterialDesc output, float3 normal, float3 wPosition)
//{
//    output = (MaterialDesc) 0;
    
//    output.Ambient = GlobalLight.Ambient * Material.Ambient;
    
//    float3 direction = -GlobalLight.Direction;
//    float NdotL = dot(normalize(normal), direction);
    
//    float3 e = normalize(ViewPosition() - wPosition);
    
//    [flatten]
//    if (NdotL > 0.0f)
//    {
//        output.Diffuse = Material.Diffuse * NdotL;
        
//        [flatten]
//        if (Material.Specular.a > 0.0f)
//        {
//            float3 r = normalize(reflect(-direction, normal));
//            float RdotE = saturate(dot(r, e));

//            float specular = pow(RdotE, Material.Specular.a);
//            output.Specular = Material.Specular * specular * GlobalLight.Specular;
//        }
//    }
    
//    [flatten]
//    if (Material.Emissive.a > 0.0f)
//    {
//        float NdotE = dot(normalize(normal), e);
//        float emissive = smoothstep(1.0f - Material.Emissive.a, 1.0f, 1.0f - saturate(NdotE));
        
//        output.Emissive = Material.Emissive * emissive;
//    }
//}

MaterialDesc ComputeLight(float3 normal, float3 wPosition)
{
    MaterialDesc output = (MaterialDesc) 0;

    output.Ambient = GlobalLight.Ambient * Material.Ambient;
    
    float3 direction = -GlobalLight.Direction;
    float NdotL = dot(normalize(normal), direction);
    //float direction = normalize(GlobalLight.Position - wPosition);
    //float NdotL = dot(normalize(normal), direction);
    float3 E = normalize(ViewPosition() - wPosition);
    
    if (NdotL > 0.0f)
    {
        output.Diffuse = Material.Diffuse * NdotL;
        //output.Diffuse = float4(1.0f, 1.0f, 1.0f, 1.0f);
        
        if (Material.Specular.a > 0.0f)
        {
            float3 R = reflect(-direction, normal);
            float RdotE = saturate(dot(R, E));

            float specular = pow(RdotE, Material.Specular.a);
            output.Specular = Material.Specular * specular * GlobalLight.Specular;
        }
    }
    
    if (Material.Emissive.a > 0.0f)
    {
        float NdotE = dot(normalize(normal), E);
        float emissive = smoothstep(1.0f - Material.Emissive.a, 1.0f, 1.0f - saturate(NdotE));
        
        output.Emissive = Material.Emissive * emissive;
    }
    
    return output;
}
///////////////////////////////////////////////////////////////////////////////
float3 MaterialToColor(MaterialDesc result)
{
    return float4(result.Ambient + result.Diffuse + result.Specular + result.Emissive).rgb;
}

float3 MaterialToColor(MaterialDesc result, float3 DiffuseMap, float3 SpecularMap)
{
    // 가중치 조정을 통해 조명 성분을 균형 있게 만듭니다.
    float3 ambient = result.Ambient.rgb * 0.1;
    float3 diffuse = result.Diffuse.rgb * DiffuseMap * 0.8;
    float3 specular = result.Specular.rgb * SpecularMap * 0.5;
    float3 emissive = result.Emissive.rgb * 0.2;

    // 조명 성분을 조합하여 최종 색상 반환
    return ambient + diffuse + specular + emissive;
}

float3 TestColor(MaterialDesc result, float3 DiffuseMap)
{
    float3 ambient = result.Ambient.rgb;
    float3 diffuse = result.Diffuse.rgb * DiffuseMap;
    
    return ambient + diffuse;
}
///////////////////////////////////////////////////////////////////////////////

//#include "InStructs.hlsli"
//#include "OutStructs.hlsli"
//#include "Functions.hlsli"