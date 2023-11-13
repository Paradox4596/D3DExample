Texture2D ShaderTexture;

SamplerState Sampler
{
    AddressU = Wrap;
    AddressV = Wrap;
    Filter = MIN_MAG_MIP_LINEAR;
};

float4 main(float4 position : SV_POSITION, float2 tex : TEXCOORD0) : SV_TARGET
{
    return ShaderTexture.Sample(Sampler, tex);
}