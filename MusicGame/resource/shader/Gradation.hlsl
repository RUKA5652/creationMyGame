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
cbuffer inData : register(b0)
{
    float3 color1;
    float3 color2;
    float4 pos;
    float2 resolution;
};

//塗りつぶす際に呼ばれる
PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
    output.color = float4(1, 1, 1, 1);
    // 起点色
    float4 startColor = float4(color1, 1);
    // 終点色
    float4 endColor = float4(color2, 1);
    // グラデーションの方向
    float2 gradDirection = normalize(pos.ba - pos.rg);
    float2 startPos_uv = pos.rg / resolution;
    float2 grad_uv = startPos_uv + gradDirection;
    // UV座標から距離を求める
    float distance = dot(input.uv, grad_uv);
    // 距離に応じて色を決定
    output.color = lerp(startColor, endColor, distance);
    return output;
}