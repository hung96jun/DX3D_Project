#include "Global/Global.hlsli"

//VertexUVOutput VS(VertexUVInput input)
//{
//    VertexUVOutput output;
//    output.Position = mul(input.Position, World);
//    output.Position = mul(output.Position, View);
//    output.Position = mul(output.Position, Projection);
    
//    output.UV = input.UV;
    
//    output.wvpPosition = float4(0.0f, 0.0f, 0.0f, 0.0f);
    
//    return output;
//}

//float4 PS(VertexUVOutput input) : SV_Target0
//{
//    //float4 result = DiffuseMap.Sample(Samp, input.UV);

//    return input.wvpPosition;
//}

VertexTestOutput VS(VertexTestInput input)
{
    VertexTestOutput output;
    //output.Position = mul(input.Position, World);
    //output.WPosition = output.Position.xyz;
    //output.Position = mul(output.Position, View);
    //output.Position = mul(output.Position, Projection);
    
    //output.Normal = mul(input.Normal, (float3x3) World);
    //output.Tangent = mul(input.Tangent, (float3x3) World);
    
    //output.UV = input.UV;
    //output.Color = input.Color;
    
    output.Position = mul(input.Position, World);
    output.WPosition = output.Position.xyz;

    output.Position = mul(output.Position, View);
    output.Position = mul(output.Position, Projection);
    output.wvpPosition = output.Position;
    
    output.Normal = mul(input.Normal, (float3x3)World);
    output.Tangent = mul(input.Tangent, (float3x3)World);
    output.UV = input.UV;
    output.Color = input.Color;
    
    return output;
}

float4 PS(VertexTestOutput input) : SV_Target0
{
    Texture2D diffuseMap = DiffuseMap;
    Texture2D specularMap = SpecularMap;
    
    float4 diffuse = Material.Diffuse;
    float4 specular = Material.Specular;
    diffuse = Texture(diffuse, diffuseMap, input.UV);
    specular = Texture(specular, specularMap, input.UV);
    
    //MaterialDesc desc = ComputeLight(input.Normal, input.UV, input.WPosition);
    MaterialDesc desc = ComputeLight(input.Normal, input.WPosition);

    //return float4(MaterialToColor(output), 1.0f);
    return float4(MaterialToColor(desc, diffuse.rgb, specular.rgb), 1.0f);
        
    //float4 result = DiffuseMap.Sample(Samp, input.UV);
    //return result;
}

//float4 PS(VertexTestOutput input) : SV_Target0
//{
//    float4 color = DiffuseMap.Sample(Samp, input.UV);
//    float4 sampling = SpecularMap.Sample(Samp, input.UV);
    
//    [flatten]
//    if (any(sampling.rgb))
//        color = color * sampling;
    
//    MaterialDesc result;
//    {
//        result = (MaterialDesc) 0;
//        result.Ambient = GlobalLight.Ambient * Material.Ambient;
        
//        float3 direction = -GlobalLight.Direction;
//        float NdotL = dot(normalize(input.Normal), direction);
        
//        float3 E = normalize(ViewPosition() - input.WPosition);
        
//        [flatten]
//        if (NdotL > 0.0f)
//        {
//            result.Diffuse = Material.Diffuse * NdotL;
            
//            [flatten]
//            if (Material.Specular.a > 0.0f)
//            {
//                float3 R = normalize(reflect(-direction, input.Normal));
//                float RdotE = saturate(dot(R, E));
                
//                float specular = pow(RdotE, Material.Specular.a);
//                result.Specular = Material.Specular * specular * GlobalLight.Specular;
//            }
//        }
        
//        [flatten]
//        if (Material.Emissive.a > 0.0f)
//        {
//            float NdotE = dot(normalize(input.Normal), E);
//            float emissive = smoothstep(1.0f - Material.Emissive.a, 1.0f, 1.0f - saturate(NdotE));
            
//            result.Emissive = Material.Emissive * emissive;
//        }
//    }
    
//    float3 output;
//    output = (result.Ambient + result.Diffuse + result.Specular + result.Emissive).rgb;
    
//    return float4(output, 1.0f);
//}