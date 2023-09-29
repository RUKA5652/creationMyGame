//pixelシェーダ
struct PS_INPUT
{
    float4 Diffuse : COLOR0;
    float4 Specular : COLOR1;
    float2 uv : TEXCOORD0;
};

//色
struct PS_OUTPUT
{
    float4 color : SV_TARGET0;
};

SamplerState sam; //サンプラ
Texture2D mTex : register(t0); //テクスチャ
Texture2D sTex : register(t1); //テクスチャ

//塗りつぶす際に呼ばれる
PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
    float4 subCol = sTex.Sample(sam, input.uv);
    float4 mainCol = mTex.Sample(sam, input.uv);
    output.color = mainCol;
    if (mainCol.a == 0)
    {
        discard;
    }
    mainCol.rgb += subCol.rgb;
    
    mainCol = saturate(mainCol);
    output.color = mainCol;
    return output;
}