
struct VS_INPUT
{
	float3 inPos : POSITIONT;
	float4 inColor : COLOR;
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
	output.outPos = float4(input.inPos, 1);

	return output;
}