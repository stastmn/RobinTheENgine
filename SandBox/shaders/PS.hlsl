

struct PS_INPUT
{
	float4 outColor : COLOR;
};

float4 main( PS_INPUT input ) : SV_Target
{
	return input.outColor;
}