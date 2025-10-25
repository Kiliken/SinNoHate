//
//	Textures
//
Texture2D g_texture0 : register(t0);
Texture2D g_texture1 : register(t1);
SamplerState g_sampler0 : register(s0);
SamplerState g_sampler1 : register(s1);

namespace s3d
{
	//
	//	VS Output / PS Input
	//
	struct PSInput
	{
		float4 position : SV_POSITION;
		float4 color : COLOR0;
		float2 uv : TEXCOORD0;
	};
}

cbuffer PSConstants2D : register(b0)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
	float4 g_sdfOutlineColor;
	float4 g_sdfShadowColor;
	float4 g_internal;
}

cbuffer PaletteSettings : register(b1)
{
	uint currentPalette;
}

//
//	Functions
//


float absf(float x)
{
    return (x < 0.0f) ? -x : x;
}

float4 PS_PaletteSwap(s3d::PSInput input) : SV_TARGET
{
    float4 texColor = g_texture0.Sample(g_sampler0, input.uv);

    uint paletteWidth, paletteHeight;
    g_texture1.GetDimensions(paletteWidth, paletteHeight);

    float stepX = 1.0f / paletteWidth;
    float stepY = 1.0f / paletteHeight;
	//uint i = 3;
    for (uint i = 0; i < paletteWidth; i++)
    {
        float2 sourceUV = float2((i + 0.5f) * stepX, 0.5f * stepY);
        float4 sourceColor = g_texture1.Sample(g_sampler1, sourceUV);

        float3 diff = texColor.rgb - sourceColor.rgb;
		
        if (absf(diff.r) < 0.01f && absf(diff.g) < 0.01f && absf(diff.b) < 0.01f && texColor.a > 0.01f)
        {
            float2 targetUV = float2((i + 0.5f) * stepX, (currentPalette + 0.5f) * stepY);
            float4 targetColor = g_texture1.Sample(g_sampler1, targetUV);
            //return (targetColor * input.color) + g_colorAdd;
			//return float4(1, 0, 1, 1);
			texColor = targetColor;
        }
    }

    // No match found — return fallback color or original
    return (texColor * input.color) + g_colorAdd;
	//return float4(1, 1, 0, 1);
}


