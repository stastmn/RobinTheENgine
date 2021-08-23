
struct VS_INPUT
{
	float3 inPos : POSITION;
	float4 inColor : COLOR;
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
    float3 LightPoint = float3(0.0f, 0.2f, 1.0f);
    float4 BasicCollor = float4(0.8f, 0.8f, 0.8f, 1.0f);
    
    float4 newNormal = mul(input.inColor, mvp);
    newNormal = normalize(newNormal);
    float power = dot(LightPoint, newNormal);
    
    float3 col = BasicCollor * power;
    
	VS_OUTPUT output;
    output.outColor = BasicCollor * power;
    output.outPos = mul(float4(input.inPos,1), mvp);

	return output;
}