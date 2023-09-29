#include "GradationImage.h"
#include"../../../../shaderDraw/DxShDraw.h"
#include<array>

GradationImage::GradationImage()
{
	shader_ = LoadPixelShader("resource/shader/Gradation.pso");
}

GradationImage::~GradationImage()
{
	DeleteShader(shader_);
}

void GradationImage::operator()(int handle)
{
	auto now = GetDrawScreen();
	SetDrawScreen(handle);
	//向こうのデータではfloat3,3,2で宣言されているがこちら側で設定するときは4,4,4として考える
	auto buffHandle = CreateShaderConstantBuffer(sizeof(float) * 4*4);
	float sizeX, sizeY;
	GetGraphSizeF(handle,&sizeX,&sizeY);
	DxShDraw::DrawGraph(0, 0, handle, [&](){
		SetUsePixelShader(shader_);
		float* buffData = static_cast<float*>(GetBufferShaderConstantBuffer(buffHandle));
		//float4
		buffData[0] = startColor.x / 255;
		buffData[1] = startColor.y / 255;
		buffData[2] = startColor.z / 255;
		//float4
		buffData[4] = endColor.x / 255;
		buffData[5] = endColor.y / 255;
		buffData[6] = endColor.z / 255;
		//float4
		buffData[8] = startPos.u;
		buffData[9] = startPos.v;
		buffData[10] = endPos.u;
		buffData[11] = endPos.v;
		//float4
		buffData[12] = sizeX;
		buffData[13] = sizeY;
		UpdateShaderConstantBuffer(buffHandle);
		SetShaderConstantBuffer(buffHandle, DX_SHADERTYPE_PIXEL, 0);
	});

	DeleteShaderConstantBuffer(buffHandle);
	SetDrawScreen(now);
}
