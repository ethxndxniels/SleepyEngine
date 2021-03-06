cbuffer CameraData : register(b6)
{
    float4 camPos;
    row_major float4x4 viewInvMatrix;
    row_major float4x4 projInvMatrix;
};

float4 CalculateWorldPosition( float4 worldDepth )
{
    float4 worldPosition = mul(worldDepth, projInvMatrix);
    worldPosition /= worldPosition.w;
    return mul(worldPosition, viewInvMatrix);
}