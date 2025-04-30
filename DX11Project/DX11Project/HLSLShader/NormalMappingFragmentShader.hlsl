#include "Common.hlsli"

struct FragmentInput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
    float2 uv : TEXCOORD;
    float3 cameraDirection : TEXCOORD1;
};

//Shader can get few Texture
//DX11 max count is 12
//If not named register, register named def order
//Front alphabet = DataType
Texture2D diffuseMap : register(t0);
Texture2D normalMap : register(t1);
SamplerState diffuseSampler : register(s0);

//oren-nayer - diffuse + roughness

float4 main(FragmentInput input) : SV_TARGET
{
    //Sampling
    float4 texColor = diffuseMap.Sample(diffuseSampler, input.uv);
    
    float3 tangentNormal = normalMap.Sample(diffuseSampler, input.uv);
    tangentNormal = tangentNormal * 2 - 1;
    
    float3x3 tangentToWorld = float3x3(
        normalize(input.tangent),
        normalize(input.bitangent),
        normalize(input.normal)
    );
    
    float3 lightDir = -float3(500.f, 500.f, -500.f);
    lightDir = normalize(lightDir);
    
    float3 worldNormal = mul(tangentNormal, tangentToWorld);
    float nDotl = CalcHalfLambert(worldNormal, lightDir);
    //Same
    //saturate(dot(worldNormal, -lightDirection)) = max(0, dot(worldNormal, -lightDir));
    
    float specular = CalcBlinnPhong(worldNormal, lightDir, input.cameraDirection);
    
    float4 result = texColor * nDotl + specular;
    
    return texColor;
    //return float4(input.uv, 0, 1);
}