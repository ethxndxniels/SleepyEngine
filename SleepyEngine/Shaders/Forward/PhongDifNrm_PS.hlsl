#include "../Common/ShaderOps.hlsl"
#include "../Common/LightVectorData.hlsl"
#include "../Common/PointLight.hlsl"
#include "../Common/DefaultLightSettings.hlsl"
#include "../Common/SpotLight.hlsl"
#include "../Common/CameraData.hlsl"

cbuffer ObjectCBuf
{
    float3 specularColor;
    float specularWeight;
    float specularGloss;
    bool useNormalMap;
    float normalMapWeight;
};

Texture2D tex;
Texture2D nmap : register(t2);

SamplerState splr;


float4 main(float3 viewFragPos : Position, float3 viewNormal : Normal, float3 viewTan : Tangent, float3 viewBitan : Bitangent, float2 tc : Texcoord) : SV_Target
{
    // normalize the mesh normal
    viewNormal = normalize(viewNormal);
    // replace normal with mapped if normal mapping enabled
    if (useNormalMap)
    {
        const float3 mappedNormal = MapNormal(normalize(viewTan), normalize(viewBitan), viewNormal, tc, nmap, splr);
        viewNormal = lerp(viewNormal, mappedNormal, normalMapWeight);
    }
	// fragment to light vector data
    const LightVectorData lv = CalculateLightVectorData(pointLightData[0].pos, viewFragPos);
	// attenuation
    float pointLightAtt = saturate((1 - (lv.distToL / pointLightData[index].radius)));
    pointLightAtt *= pointLightAtt;
	// diffuse
    const float3 diffuse = Diffuse(pointLightData[0].color, defaultLightIntensity, pointLightAtt, lv.dirToL, viewNormal);
    // TODO: Figure out why using specularGloss instead of defaultSpecularPower breaks
    // specular
    const float3 specular = Speculate(
        pointLightData[0].color * defaultLightIntensity * specularColor, specularWeight, viewNormal,
        lv.vToL, viewFragPos, pointLightAtt, defaultSpecularPower
    );
    
    const float3 camToFrag = viewFragPos - camPos.xyz;

    // spot light
    float3 spotToFrag = spotLightData[0].pos - viewFragPos;
    float att = saturate((1 - (length(spotToFrag) / spotLightData[0].range)));
    att *= att;
    float angularAttFactor = max(0.0f, dot(normalize(-spotLightData[0].lightDirection), normalize(spotToFrag)));
    float3 spotDiffuse = float3(0.0f, 0.0f, 0.0f);
    float3 spotSpecular = float3(0.0f, 0.0f, 0.0f);
    if (angularAttFactor > spotLightData[0].outerRadius && att > 0.0f)
    {
        float conAtt = saturate((angularAttFactor - spotLightData[0].outerRadius) / (spotLightData[0].innerRadius - spotLightData[0].outerRadius));
        
        //float4 fragPositionInLightView = mul(float4(viewFragPos, 1.0f), spotLightData[0].spotViewProjectionMatrix);
        float spotLightShadow = 1.0f; //CalculateSpotLightShadow(fragPositionInLightView, splr);
        spotDiffuse = Diffuse(spotLightData[0].color.rgb, defaultLightIntensity, att * conAtt, -normalize(spotLightData[0].lightDirection), viewNormal) * spotLightShadow;
        spotSpecular = Speculate(
            spotLightData[0].color.rgb, defaultLightIntensity, viewNormal, -normalize(spotLightData[0].lightDirection),
            camToFrag, att * conAtt, defaultSpecularPower
        ) * spotLightShadow;
    }
    
    float3 combinedColor = diffuse + spotDiffuse + specular + spotSpecular + defaultAmbientLight;
	// final color
    return float4((combinedColor * tex.Sample(splr, tc).rgb), 1.0f);
}