#include "ConstantBuffers.hlsli"
#include "SamplerStates.hlsli"
#include "Textures.hlsli"

void Texture(inout float4 color, Texture2D t, float2 uv, SamplerState samp)
{
    float4 sampling = t.Sample(samp, uv);
    
    [flatten]
    if (any(sampling.rgb))
        color = color * sampling;
}

void Texture(inout float4 color, Texture2D t, float2 uv)
{
    Texture(color, t, uv, LinearSampler);
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
void ComputeLight(out MaterialDesc output, float3 normal, float3 wPosition)
{
    output = (MaterialDesc) 0;
    
    output.Ambient = GlobalLight.Ambient * Material.Ambient;
    
    float3 direction = -GlobalLight.Direction;
    float NdotL = dot(normalize(normal), direction);
    
    float3 e = normalize(ViewPosition() - wPosition);
    
    [flatten]
    if (NdotL > 0.0f)
    {
        output.Diffuse = Material.Diffuse * NdotL;
        
        [flatten]
        if (Material.Specular.a > 0.0f)
        {
            float3 r = normalize(reflect(-direction, normal));
            float RdotE = saturate(dot(r, e));

            float specular = pow(RdotE, Material.Specular.a);
            output.Specular = Material.Specular * specular * GlobalLight.Specular;
        }
    }
    
    [flatten]
    if (Material.Emissive.a > 0.0f)
    {
        float NdotE = dot(normalize(normal), e);
        float emissive = smoothstep(1.0f - Material.Emissive.a, 1.0f, 1.0f - saturate(NdotE));
        
        output.Emissive = Material.Emissive * emissive;

    }
}
///////////////////////////////////////////////////////////////////////////////
float3 MaterialToColor(MaterialDesc result)
{
    return float4(result.Ambient + result.Diffuse + result.Specular + result.Emissive).rgb;

}
///////////////////////////////////////////////////////////////////////////////