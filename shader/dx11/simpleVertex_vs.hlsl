cbuffer cbPerObject
{
	matrix g_worldViewProjection;
	matrix g_world;
}

struct VS_INPUT
{
	float4 position : POSITION;
	float4 color : COLOR;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

VS_OUTPUT vs_main(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position = input.position;//mul(input.position, g_worldViewProjection);
	output.color = input.color;
	return output;
}