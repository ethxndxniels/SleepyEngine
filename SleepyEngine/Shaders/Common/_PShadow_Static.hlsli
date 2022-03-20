TextureCube smapPL : register(t3);
Texture2D smapSL : register(t4);
Texture2D smapDL : register(t5);

SamplerComparisonState ssam : register(s1);

static const float zf = 100.0f;
static const float zn = 0.5f;
static const float c1 = zf / (zf - zn);
static const float c0 = -zn * zf / (zf - zn);

float CalculateShadowDepth(const in float4 shadowPos)
{
    // get magnitudes for each basis component
    const float3 m = abs(shadowPos).xyz;
    // get the length in the dominant axis
    // (this correlates with shadow map face and derives comparison depth)
    const float major = max(m.x, max(m.y, m.z));
    // converting from distance in shadow light space to projected depth
    return (c1 * major + c0) / major;
}

float ShadowPL(const in float4 shadowPos)
{
    return smapPL.SampleCmpLevelZero(ssam, shadowPos.xyz, CalculateShadowDepth(shadowPos));
}

// TODO: Not sure if these work
float ShadowSL(const in float4 shadowPos)
{
    return smapSL.SampleCmpLevelZero(ssam, shadowPos.xy, CalculateShadowDepth(shadowPos));
}

float ShadowDL(const in float4 shadowPos)
{
    return smapDL.SampleCmpLevelZero(ssam, shadowPos.xy, CalculateShadowDepth(shadowPos));
}