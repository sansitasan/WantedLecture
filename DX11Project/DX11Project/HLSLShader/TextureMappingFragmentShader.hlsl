struct FragmentInput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

//Shader can get few Texture
//DX11 max count is 12
//If not named register, register named def order
//Front alphabet = DataType
Texture2D diffuseMap : register(t0);
SamplerState diffuseSampler : register(s0);

float4 main(FragmentInput input) : SV_TARGET
{
    //Sampling
    float4 texColor = diffuseMap.Sample(diffuseSampler, input.uv);
    
    return texColor;
    //return float4(input.uv, 0, 1);
}