//POSITION, SV_POSITION�� �ø�ƽ
//SV = system value
float4 main( float3 pos : POSITION ) : SV_POSITION
{
    return float4(pos, 1);
}