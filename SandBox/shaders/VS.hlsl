
struct VS_INPUT
{
    float2 inTexCoord : TEXCOORD;
    float3 inNormal : NORMAL;
    float3 inPos : POSITION;
};



struct VS_OUTPUT
{
    float4 outPos : SV_POSITION;
    float2 outTexCoord : TEXCOORD;
    float3 outNormal : NORMAL;
    float3 outWorldPos : WORLD_POS;
};

cbuffer cByffer : register(b0)
{
    float4x4 mvp;
    float4x4 world;
}

VS_OUTPUT main(VS_INPUT input)
{
    float3 LightPoint = float3(0.0f, 0.f, 3.0f);
    float4 BasicCollor = float4(0.f, 0.8f, 0.5f, 1.0f);
    
    VS_OUTPUT output;
    output.outTexCoord = input.inTexCoord;
    output.outPos = mul(float4(input.inPos, 1), mvp);
    output.outNormal = normalize(mul(float4(input.inNormal, 0.0f), world));
    output.outWorldPos = mul(float4(input.inPos, 1), world);

    return output;
}