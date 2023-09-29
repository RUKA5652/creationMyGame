#include "SelectUIDraw.h"
#include"../../../Base/GameCore.h"
#include"../SelectDrawIndex.h"
#include"../../../../shaderDraw/DxShDraw.h"
#include<DxLib.h>
#include "../../../../Manager/ImageMng.h"
#include"../../../WindowSize.h"
#include"../../../../Input/Select/SelectSceneInput.h"
#include"../../../../Input/EnumCast.h"

constexpr FLOAT3 mulColor(1,1,0);

SelectUIDraw::SelectUIDraw()
{
	guideHandle_ = LoadGraph("resource/skin/UI/Select/guide.png");
	maskHandle_ = LoadGraph("resource/skin/UI/Select/mask.png");
	shader_ = LoadPixelShader("resource/shader/DrawSelectCursor.pso");
	auto size = lpWindowSize->GetSize();
	screen_ = MakeScreen(size.x, size.y,true);
	bufferHandle_ = CreateShaderConstantBuffer(sizeof(float) * 4 * 2);
	time_ = 0;		
	checkColor_.x = 0;
	checkColor_.y = 0;
	checkColor_.z = 0;
	checkColor_.w = 0;
}

SelectUIDraw::~SelectUIDraw()
{
	DeleteGraph(guideHandle_);
	DeleteGraph(maskHandle_);
	DeleteShader(shader_);
	DeleteGraph(screen_);
	DeleteShaderConstantBuffer(bufferHandle_);
}

void SelectUIDraw::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	
	checkColor_.w = 1;
	bool flag = false;
	auto data = input.GetInputData();
	auto& key1 = data[Cast(SELECT::UP)];
	auto& key2 = data[Cast(SELECT::DOWN)];
	if (key1.now || key2.now)
	{
		flag = true;
		checkColor_.x = 1;
		checkColor_.y = 0;
		checkColor_.z = 0;
	}
	key1 = data[Cast(SELECT::RSKIP)];
	key2 = data[Cast(SELECT::LSKIP)];
	if (key1.now || key2.now)
	{
		flag = true;
		checkColor_.x = 0;
		checkColor_.y = 1;
		checkColor_.z = 0;
	}
	key1 = data[Cast(SELECT::SPEED)];
	if (key1.now )
	{
		flag = true;
		checkColor_.x = 0;
		checkColor_.y = 0;
		checkColor_.z = 1;
	}

	if (!flag)
	{
		checkColor_.w = 0;
		checkColor_.x = 0;
		checkColor_.y = 0;
		checkColor_.z = 0;
	}

}

void SelectUIDraw::Draw()
{

	auto inScreem = GetDrawScreen();
	SetDrawScreen(screen_);
	ClearDrawScreen();


	DxShDraw::DrawGraph(0, 0, guideHandle_, [&]() {
		SetUsePixelShader(shader_);
	SetUseTextureToShader(0, guideHandle_);
	SetUseTextureToShader(1, maskHandle_);
	SetUseTextureToShader(2, inScreem);
	auto buff = static_cast<float*>(GetBufferShaderConstantBuffer(bufferHandle_));
	buff[0] = mulColor.x;
	buff[1] = mulColor.y;
	buff[2] = mulColor.z;
	buff[3] = 0;
	buff[4] = checkColor_.x;
	buff[5] = checkColor_.y;
	buff[6] = checkColor_.z;
	buff[7] = checkColor_.w;
	UpdateShaderConstantBuffer(bufferHandle_);
	SetShaderConstantBuffer(bufferHandle_, DX_SHADERTYPE_PIXEL, 0);
		});

	SetDrawScreen(inScreem);
	DxLib::DrawGraph(0, 0, screen_, true);




}

void SelectUIDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(SelectDrawIndex::UI), shared_from_this());
}
