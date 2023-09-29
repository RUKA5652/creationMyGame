#include "DxShDraw.h"
#include"../Manager/ImageMng.h"
#include<DxLib.h>
#include <array>
#include <algorithm>

//static int RtHSheder = -1;

////�萔�o�b�t�@�쐬
//static int cbuff = CreateShaderConstantBuffer(sizeof(float) * 4);
////�萔�o�b�t�@�̃A�h���X�����炤
//static auto threshold = static_cast<float*>(GetBufferShaderConstantBuffer(cbuff));

namespace 
{
	inline std::array<VERTEX2DSHADER, 4> Create(int x, int y,  int image)
	{
		int w, h;
		GetGraphSize(image, &w, &h);
		auto [uv1, uv2] = lpImageMng.GetUV(image);
		std::array<VERTEX2DSHADER, 4> verts = {};

		for (auto& v : verts) {
			v.rhw = 1.0f; //�QD�����̂܂܎����Ă��邽��
			v.dif = GetColorU8(0xff, 0xff, 0xff, 0xff);//�f�B�t�[�Y
			v.u = 0.0f;//�G�̂ǂ��H0~1�̒l�Ő�߂��� �� X
			v.v = 0.0f;//�G�̂ǂ��H0~1�̒l�Ő�߂��� �c Y
			v.su = 0.0f;//�T�uUV
			v.sv = 0.0f;//�T�uUV
			v.pos.z = 0.0f;
			v.spc = GetColorU8(0x00, 0x00, 0x00, 0x00);//�X�y�L����
		}
		//���W�̏��Ԃ��d�v�@TRIANGLE_STRIP�Ȃ̂ō��ォ��Z������`�������œ����
		//�摜�̂ǂ����g���̂���UV�ɓ����
		verts[0].pos.x = static_cast<float>(x);
		verts[0].pos.y = static_cast<float>(y);
		verts[0].u = uv1.x;
		verts[0].v = uv1.y;
		verts[0].u = uv1.x;
		verts[0].v = uv1.y;

		verts[1].pos.x = verts[0].pos.x + w;
		verts[1].pos.y = verts[0].pos.y;
		verts[1].u = uv2.x;
		verts[1].v = uv1.y;
		verts[1].u = uv2.x;
		verts[1].v = uv1.y;

		verts[2].pos.x = verts[0].pos.x;
		verts[2].pos.y = verts[0].pos.y + h;
		verts[2].u = uv1.x;
		verts[2].v = uv2.y;
		verts[2].u = uv1.x;
		verts[2].v = uv2.y;

		verts[3].pos.x = verts[0].pos.x + w;
		verts[3].pos.y = verts[0].pos.y + h;
		verts[3].u = uv2.x;
		verts[3].v = uv2.y;
		verts[3].u = uv2.x;
		verts[3].v = uv2.y;

		return verts;
	};

	inline std::array<VERTEX2DSHADER, 4> Create(int x, int y, double ExRate, int image)
	{
		int w, h;
		GetGraphSize(image, &w, &h);
		w *= static_cast<int>(ExRate);
		h *= static_cast<int>(ExRate);
		auto [uv1, uv2] = lpImageMng.GetUV(image);

		std::array<VERTEX2DSHADER, 4> verts = {};

		for (auto& v : verts) {
			v.rhw = 1.0f; //�QD�����̂܂܎����Ă��邽��
			v.dif = GetColorU8(0xff, 0xff, 0xff, 0xff);//�f�B�t�[�Y
			v.u = 0.0f;//�G�̂ǂ��H0~1�̒l�Ő�߂��� �� X
			v.v = 0.0f;//�G�̂ǂ��H0~1�̒l�Ő�߂��� �c Y
			v.su = 0.0f;//�T�uUV
			v.sv = 0.0f;//�T�uUV
			v.pos.z = 0.0f;
			v.spc = GetColorU8(0xff, 0xff, 0xff, 0xff);//�X�y�L����
		}
		//���W�̏��Ԃ��d�v�@TRIANGLE_STRIP�Ȃ̂ō��ォ��Z������`�������œ����
		//�摜�̂ǂ����g���̂���UV�ɓ����
		verts[0].pos.x = static_cast<float>(x - w / 2);
		verts[0].pos.y = static_cast<float>(y - w / 2);
		verts[0].u = uv1.x;
		verts[0].v = uv1.y;


		verts[1].pos.x = verts[0].pos.x + w;
		verts[1].pos.y = verts[0].pos.y;
		verts[1].u = uv2.x;
		verts[1].v = uv1.y;

		verts[2].pos.x = verts[0].pos.x;
		verts[2].pos.y = verts[0].pos.y + h;
		verts[2].u = uv1.x;
		verts[2].v = uv2.y;

		verts[3].pos.x = verts[0].pos.x + w;
		verts[3].pos.y = verts[0].pos.y + h;
		verts[3].u = uv2.x;
		verts[3].v = uv2.y;
		return verts;
	};

};

void DxShDraw::DrawGraph(int x, int y, double ExRate, int image, int p_shader)
{
	int w, h;
	GetGraphSize(image, &w, &h);
	w *= static_cast<int>(ExRate);
	h *= static_cast<int>(ExRate);
	auto [uv1,uv2] = lpImageMng.GetUV(image);

	std::array<VERTEX2DSHADER, 4> verts = {};

	for (auto& v : verts) {
		v.rhw = 1.0f; //�QD�����̂܂܎����Ă��邽��
		v.dif = GetColorU8(0xff, 0xff, 0xff, 0xff);//�f�B�t�[�Y
		v.u = 0.0f;//�G�̂ǂ��H0~1�̒l�Ő�߂��� �� X
		v.v = 0.0f;//�G�̂ǂ��H0~1�̒l�Ő�߂��� �c Y
		v.su = 0.0f;//�T�uUV
		v.sv = 0.0f;//�T�uUV
		v.pos.z = 0.0f;
		v.spc = GetColorU8(0xff, 0xff, 0xff, 0xff);//�X�y�L����
	}
	//���W�̏��Ԃ��d�v�@TRIANGLE_STRIP�Ȃ̂ō��ォ��Z������`�������œ����
	//�摜�̂ǂ����g���̂���UV�ɓ����
	verts[0].pos.x = static_cast<float>(x - w/2);
	verts[0].pos.y = static_cast<float>(y - w/2);
	verts[0].u = uv1.x;
	verts[0].v = uv1.y;


	verts[1].pos.x = verts[0].pos.x + w;
	verts[1].pos.y = verts[0].pos.y;
	verts[1].u = uv2.x;
	verts[1].v = uv1.y;

	verts[2].pos.x = verts[0].pos.x;
	verts[2].pos.y = verts[0].pos.y+ h;
	verts[2].u = uv1.x;
	verts[2].v = uv2.y;

	verts[3].pos.x = verts[0].pos.x + w;
	verts[3].pos.y = verts[0].pos.y + h;
	verts[3].u = uv2.x;
	verts[3].v = uv2.y;

	SetUsePixelShader(p_shader);
	SetUseTextureToShader(0, image);
	//���_�z��A���_�̐��A
	DrawPrimitive2DToShader(verts.data(), static_cast<int>(verts.size()), DX_PRIMTYPE_TRIANGLESTRIP);
}

void DxShDraw::DrawGraph(int x, int y, double ExRate, int image, int blendImage, int p_shader)
{
	std::array<VERTEX2DSHADER, 4> verts = Create(x,y,ExRate,image);

	SetUsePixelShader(p_shader);
	SetUseTextureToShader(0, image);
	SetUseTextureToShader(1, blendImage);
	//���_�z��A���_�̐��A
	DrawPrimitive2DToShader(verts.data(), static_cast<int>(verts.size()), DX_PRIMTYPE_TRIANGLESTRIP);
}

void DxShDraw::DrawGraph(int x, int y, int image, int blendImage, int p_shader)
{

	std::array<VERTEX2DSHADER, 4> verts = Create(x,y,image);

	SetUsePixelShader(p_shader);
	SetUseTextureToShader(0, image);
	SetUseTextureToShader(1, blendImage);
	//���_�z��A���_�̐��A
	DrawPrimitive2DToShader(verts.data(), static_cast<int>(verts.size()), DX_PRIMTYPE_TRIANGLESTRIP);
}

void DxShDraw::DrawGraph(int x, int y, int image, std::function<void(void)>&& func)
{
	std::array<VERTEX2DSHADER, 4> verts = Create(x, y, image);
	func();
	//���_�z��A���_�̐��A
	DrawPrimitive2DToShader(verts.data(), static_cast<int>(verts.size()), DX_PRIMTYPE_TRIANGLESTRIP);
}

void DxShDraw::DrawGraph(std::array<VERTEX2DSHADER, 4>& verts, int image, std::function<void(void)>&& func)
{
	func();
	//���_�z��A���_�̐��A
	DrawPrimitive2DToShader(verts.data(), static_cast<int>(verts.size()), DX_PRIMTYPE_TRIANGLESTRIP);
}



void DxShDraw::DrawChangeHueGraph(int x, int y, int image,float hue)
{
	if (lpImageMng.GetPSID("resource/shader/Cursor.pso") == -1)
	{
		lpImageMng.LoadPSID("resource/shader/Cursor.pso", "hsv");
	}
	auto RtHSheder = lpImageMng.LoadPSID("resource/shader/Cursor.pso", "hsv");
	auto& buffMng = lpImageMng.GetBuffMng();
	if (buffMng.GetBuf<float>() == nullptr)
	{
		//�萔�o�b�t�@�쐬
		buffMng.CreateBuf<float>();
	}
	auto threshold = static_cast<float*>(buffMng.GetBuf<float>());
	std::array<VERTEX2DSHADER, 4> verts = Create(x, y, image);

	SetUsePixelShader(RtHSheder);
	SetUseTextureToShader(0, image);
	//�l������������
	threshold[0] = hue;
	//�������������Ƃ�`����
	auto buff = buffMng.GetHandle<float>();
	UpdateShaderConstantBuffer(buff);
	SetShaderConstantBuffer(buff, DX_SHADERTYPE_PIXEL, 0);
	//DrawBox(verts[0].pos.x, verts[0].pos.y, verts[3].pos.x, verts[3].pos.y, 0xffffff, true);
	//���_�z��A���_�̐��A
	DrawPrimitive2DToShader(verts.data(), static_cast<int>(verts.size()), DX_PRIMTYPE_TRIANGLESTRIP);
	
}

void DxShDraw::DrawMULGraph(int x, int y, int image, int r, int g, int b)
{
	if (lpImageMng.GetPSID("mul") == -1)
	{
		lpImageMng.LoadPSID("resource/shader/MulColor.pso", "mul");
	}
	auto RtHSheder = lpImageMng.GetPSID("mul");
	auto& buffMng = lpImageMng.GetBuffMng();
	if (buffMng.GetBuf<int>() == nullptr)
	{
		//�萔�o�b�t�@�쐬
		buffMng.CreateBuf<int>();
	}
	auto threshold = static_cast<int*>(buffMng.GetBuf<int>());
	std::array<VERTEX2DSHADER, 4> verts = Create(x, y, image);

	SetUsePixelShader(RtHSheder);
	SetUseTextureToShader(0, image);
	//�l������������
	threshold[0] = r;
	threshold[1] = g;
	threshold[2] = b;
	//�������������Ƃ�`����
	auto buff = buffMng.GetHandle<int>();
	UpdateShaderConstantBuffer(buff);
	SetShaderConstantBuffer(buff, DX_SHADERTYPE_PIXEL, 0);
	//���_�z��A���_�̐��A
	DrawPrimitive2DToShader(verts.data(), static_cast<int>(verts.size()), DX_PRIMTYPE_TRIANGLESTRIP);
}

