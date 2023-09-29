//pixelシェーダ
struct PS_INPUT
{
    float4 Diffuse : COLOR0;
    float4 Specular : COLOR1;
    float2 uv : TEXCOORD0;
    float2 subuv : TEXCOORD1;
};

//色
struct PS_OUTPUT
{
    float4 color : SV_TARGET0;
};

SamplerState sam; //サンプラ
Texture2D mTex : register(t0); //テクスチャ
float4 mulColor:register(b0);

//塗りつぶす際に呼ばれる
PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
    float4 mainCol = mTex.Sample(sam, input.uv);
    if (mainCol.a == 0)
    {
        discard;
    }
    
    
    mainCol.rgb = saturate(mulColor.rgb * mulColor.a + mainCol.rgb * (1 - mulColor.a));
    output.color = float4(mainCol.r, mainCol.g, mainCol.b, mainCol.a);
    return output;
}