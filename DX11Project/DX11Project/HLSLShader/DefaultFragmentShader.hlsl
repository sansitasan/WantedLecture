struct FragmentInput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

float4 main(FragmentInput input) : SV_TARGET
{
    //return float4(input.color, 1);
    return float4(1, 1, 1, 1);

}