
struct VS_INPUT
{
    float2 inTexCoord : TEXCOORD;
    float4 inNormalCoord : NORMALCOORD;
    float3 inPos : POSITION;
};

struct VS_OUTPUT
{
    float4 outColor : COLOR;
    float4 outPos : SV_POSITION;
	
};

cbuffer cByffer : register(b0)
{
    float4x4 mvp;
}

VS_OUTPUT main(VS_INPUT input)
{
    float3 LightPoint = float3(0.0f, 0.f, 3.0f);
    float4 BasicCollor = float4(0.f, 0.8f, 0.5f, 1.0f);
    
    VS_OUTPUT output;
    output.outColor = BasicCollor;
    output.outPos = mul(float4(input.inPos, 1), mvp);

    return output;
}