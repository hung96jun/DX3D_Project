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