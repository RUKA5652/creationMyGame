//pixelシェーダ
struct PS_INPUT
{
    float4 Diffuse : COLOR0;
    float4 Specular : COLOR1;
    float2 uv : TEXCOORD0;
    float2 uv2 : TEXCOORD0;
};

//色
struct PS_OUTPUT
{
    float4 color : SV_TARGET0;
};
cbuffer buff : register(b0)
{
    float4 mulColor;
    float4 checkColor;
}

SamplerState sam : register(s0); //サンプラ
Texture2D mTex : register(t0); //テクスチャ
Texture2D sTex : register(t1); //テクスチャ
Texture2D drawScreenTex : register(t2); //テクスチャ

//塗りつぶす際に呼ばれる
PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;

    float4 mainCol = mTex.Sample(sam, input.uv); // mTexを使って色を取得
    float4 screen = drawScreenTex.Sample(sam, input.uv);
    if (mainCol.a == 0)
    {
        output.color = screen;
        return output;
    }
    float4 subCol = sTex.Sample(sam, input.uv);
    //if (checkColor.r == subCol.r && checkColor.g == subCol.g && checkColor.b == subCol.b) // checkColorとsTexが同じ色の場合
    //{
    //    mainCol.rgb = saturate(mulColor.rgb); // mulColorとmTexを乗算ブレンド
    //}
    mainCol.rgb = (checkColor.r == subCol.r && 
                    checkColor.g == subCol.g && 
                    checkColor.b == subCol.b &&
                    checkColor.a == 1 ?
    saturate(mulColor.rgb) : mainCol.rgb);
    mainCol.rgb = saturate(mainCol.rgb * mainCol.a + screen.rgb * (1 - mainCol.a));

    output.color = float4(mainCol.r, mainCol.g, mainCol.b, mainCol.a);
    return output;
    return output;
}