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
Texture2D thickTex : register(t1); //�e�N�X�`��
float4 repThickness : register(b0) ;



//�h��Ԃ��ۂɌĂ΂��
PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
    float4 mainCol = mTex.Sample(sam, input.uv);
    float4 thickCol = thickTex.Sample(sam, input.uv);
    if (mainCol.a == 0 || 
       repThickness.x >= repThickness.y ? (!(repThickness.x > thickCol.r && repThickness.y < thickCol.r)) : //min[ ] max
           (repThickness.x < thickCol.r && repThickness.y > thickCol.r) //max] [min
        )
    { 
        discard;
    }
    
    output.color = float4(mainCol.r, mainCol.g, mainCol.b, mainCol.a);
    return output;
}