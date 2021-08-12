
struct VS_INPUT
{
	float3 inPos : POSITION;
	float4 inColor : COLOR;
};

cbuffer cbuff : register(b0)
{
    float4x4 mat;
};

struct VS_OUTPUT
{
	float4 outPos : SV_POSITION;
	float4 outColor : COLOR;
};



VS_OUTPUT main(VS_INPUT input) 
{
	VS_OUTPUT output;
    output.outColor = input.inColor;
    output.outPos = mul(mat, float4(input.inPos, 1));
    
	return output;
}