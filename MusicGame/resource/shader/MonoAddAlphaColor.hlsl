//pixel�V�F�[�_
struct PS_INPUT
{
    float4 Diffuse : COLOR0;
    float4 Specular : COLOR1;
    float2 uv : TEXCOORD0;
    float2 subuv : TEXCOORD1;
};

//�F
struct PS_OUTPUT
{
    float4 color : SV_TARGET0;
};

SamplerState sam; //�T���v��
Texture2D mTex : register(t0); //�e�N�X�`��
float4 mulColor:register(b0);

//�h��Ԃ��ۂɌĂ΂��
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