struct VertexInput
{
    float3 position : POSITION;
    float3 color : COLOR;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
    float2 uv : TEXCOORD;
};

cbuffer Transform : register(b0)
{
    matrix worldMatrix;
};

//Padding is required.
cbuffer Camera : register(b1)
{
    matrix viewMatrix;
    matrix projectionMatrix;
    float3 cameraPosition;
    float padding;
};

struct VertexOutput
{
    float4 position : SV_Position;
    float3 color : COLOR;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 bitangent : BITANGENT;
    float2 uv : TEXCOORD;
    float3 cameraDirection : COLOR1;
};

VertexOutput main(VertexInput input)
{
    VertexOutput output;
    output.position = mul(float4(input.position, 1), worldMatrix);
    float3 worldPosition = output.position.xyz;
    output.cameraDirection = normalize(worldPosition - cameraPosition);
    
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    output.color = input.color;
    output.normal = normalize(mul(input.normal, (float3x3) worldMatrix));
    output.tangent = normalize(mul(input.tangent, (float3x3) worldMatrix));
    output.bitangent = normalize(mul(input.bitangent, (float3x3) worldMatrix));
    output.uv = input.uv;
    return output;
}