
//pixel�V�F�[�_
struct PS_INPUT
{
    float4 Diffuse : COLOR0;
    float4 Specular : COLOR1;
    float2 uv : TEXCOORD0;
    float2 suv : TEXCOORD1;
};

//�F
struct PS_OUTPUT
{
    float4 color : SV_TARGET0;
};

SamplerState sam; //�T���v��
Texture2D tex : register(t0); //�e�N�X�`��
Texture2D stex : register(t1); //�e�N�X�`��

PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
    float4 col = tex.Sample(sam, input.uv);
    if (col.a == 0)
    {
        discard;
    }
    float4 subCol = stex.Sample(sam, input.suv);
    output.color = saturate(col * subCol);
    return output;
}