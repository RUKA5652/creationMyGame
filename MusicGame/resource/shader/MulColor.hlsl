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

//定数バッファのスロット0番目
cbuffer buff : register(b0)
{
    int r;
    int g;
    int b;
}

SamplerState sam; //サンプラ
Texture2D tex : register(t0); //テクスチャ


//塗りつぶす際に呼ばれる
PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
    float4 col = tex.Sample(sam, input.uv);
    if (col.a == 0)
    {
        discard;
    }
    
    col.r *= r / 255.0;
    col.g *= g / 255.0;
    col.b *= b / 255.0;
    col = saturate(col);
    output.color = col;
    return output;
}