//POSITION, SV_POSITION¿∫ Ω√∏‡∆Ω
//SV = system value

struct VertexInput
{
    float3 position : POSITION;
    float3 color : COLOR;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

cbuffer Transform : register(b0)
{
    matrix worldMatrix;
};

cbuffer Camera : register(b1)
{
    matrix viewMatrix;
};

struct VertexOutput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

VertexOutput main(VertexInput input)
{
    VertexOutput output;
    //output.position = float4(input.position, 1);
    output.position = mul(float4(input.position, 1), worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.color = input.color;
    output.normal = input.normal;
    output.uv = input.uv;
    return output;
}