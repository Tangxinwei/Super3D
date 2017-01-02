struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

float4 ps_main(VS_OUTPUT input) : SV_TARGET
{
	return input.color;
}