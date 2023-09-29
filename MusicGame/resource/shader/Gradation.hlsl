//pixel�V�F�[�_
struct PS_INPUT
{
    float4 Diffuse : COLOR0;
    float4 Specular : COLOR1;
    float2 uv : TEXCOORD0;
};

//�F
struct PS_OUTPUT
{
    float4 color : SV_TARGET0;
};

SamplerState sam; //�T���v��
cbuffer inData : register(b0)
{
    float3 color1;
    float3 color2;
    float4 pos;
    float2 resolution;
};

//�h��Ԃ��ۂɌĂ΂��
PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
    output.color = float4(1, 1, 1, 1);
    // �N�_�F
    float4 startColor = float4(color1, 1);
    // �I�_�F
    float4 endColor = float4(color2, 1);
    // �O���f�[�V�����̕���
    float2 gradDirection = normalize(pos.ba - pos.rg);
    float2 startPos_uv = pos.rg / resolution;
    float2 grad_uv = startPos_uv + gradDirection;
    // UV���W���狗�������߂�
    float distance = dot(input.uv, grad_uv);
    // �����ɉ����ĐF������
    output.color = lerp(startColor, endColor, distance);
    return output;
}