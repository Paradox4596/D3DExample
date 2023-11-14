﻿texture2D ShaderTexture;

SamplerState Sampler;


float4 main(float4 position : SV_POSITION, float2 tex : TEXCOORD0) : SV_TARGET
{
    float4 result = ShaderTexture.Sample(Sampler, tex);
              
    //result[0] = result[1] = result[2] = result[0] * 0.21f + result[1] * 0.72f + result[2] * 0.07f;  // grayscale1
    //result[0] = result[1] = result[2] = (result[0] + result[1] + result[2]) / 3;    // grayscale2
    
    //if ( result[0] > 0.6f)                          // ¸ð³ëÅæ
    //{
    //    result[0] = result[1] = result[2] = 1.0f;
    //}
    //else
    //{
    //    result[0] = result[1] = result[2] = 0.0f;
    //}
    
    return result;
}