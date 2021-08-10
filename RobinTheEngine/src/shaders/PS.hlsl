

struct PS_INPUT
{
	float4 outPos : SV_POSITION;
	float4 outColor : COLOR;
};

float4 main( PS_INPUT input ) : SV_Target
{
	return input.outColor;
}