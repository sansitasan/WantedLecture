//Lambert cosine law
float CalcLambert(float3 worldNormal, float3 lightDirection)
{
    return saturate(dot(worldNormal, -lightDirection));
}

float CalcHalfLambert(float3 worldNormal, float3 lightDirection, float size = .5f)
{
    float nDotl = CalcLambert(worldNormal, lightDirection);
    return pow(nDotl * size + (1 - size), 2);
}

float CalcPhong(float3 worldNormal, float3 lightDirection, float3 cameraDirection, float shineness = 16.f)
{
    float nDotl = CalcLambert(worldNormal, lightDirection);
    
    float3 reflection = reflect(lightDirection, worldNormal);
    float3 viewDirection = normalize(cameraDirection);
    
    float rDotv = saturate(dot(reflection, -viewDirection));
    
    float specular = pow(rDotv, shineness);
    return specular;
}

float CalcBlinnPhong(float3 worldNormal, float3 lightDirection, float3 cameraDirection, float shineness = 32.f)
{
    float3 viewDirection = normalize(cameraDirection);
    float3 halfVector = -normalize(lightDirection + viewDirection);
    
    float nDoth = saturate(dot(worldNormal, halfVector));
    float specular = pow(nDoth, shineness);
    return specular;
}