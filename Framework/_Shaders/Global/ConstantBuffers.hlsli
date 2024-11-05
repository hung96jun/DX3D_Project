#include "Structs.hlsli"

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

//cbuffer MaterialBuffer : register(b2)
//{
//    float4 Diffuse;
//    float4 Specular;
//    float4 Ambient;
//    float4 Emissive;
    
//    float Shininess;
//}

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