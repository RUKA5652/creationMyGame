#include "TitleBackImageDraw.h"
#include<DxLib.h>
#include"../../../Base/GameCore.h"
#include"../TitleDrawIndex.h"
#include"../../../WindowSize.h"
#include"GradationImage.h"
#include"../../../../JsonParam/IOJSON.h"


/// <summary>
/// JSON�Ŏg�p����f�[�^
/// </summary>
inline namespace JSON
{
	//�t�@�C�����O
	constexpr const char* FileName = "Title";
	//�I�u�W�F�N�g
	constexpr const char* ObjKey = "BackImage";
	//�L�[
	constexpr const char* StartColor = "StartColor";
	constexpr const char* EndColor = "EndColor";
	constexpr const char* R = "r";
	constexpr const char* G = "g";
	constexpr const char* B = "b";
	constexpr const char* StartPos = "StartPos";
	constexpr const char* EndPos = "EndPos";
	constexpr const char* X = "x";
	constexpr const char* Y = "y";
}


TitleBackImageDraw::TitleBackImageDraw()
{
	//handle_ = LoadGraph("resource/skin/Default/Background.png");
	auto& size = lpWindowSize->GetSize();
	handle_ = MakeScreen(size.x, size.y, true);
	Load();
}

TitleBackImageDraw::~TitleBackImageDraw()
{
	DeleteGraph(handle_);
}

void TitleBackImageDraw::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	rotateDraw_.Update(delta);
}

void TitleBackImageDraw::Draw()
{
	DrawGraph(0, 0, handle_, true);
	rotateDraw_.Draw();
}

void TitleBackImageDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(TitleDrawIndex::BackImage), shared_from_this());
}

void TitleBackImageDraw::Load()
{
	//JSON�f�[�^�ǂݍ���
	auto result = InPutJSON()(FileName);
	GradationImage gra;
	//�i�[
	if (result)
	{
		auto& doc = result.value()[ObjKey];
		auto& pos = doc[StartPos];
		gra.startPos = { pos[X].GetFloat(),pos[Y].GetFloat() };
		pos = doc[EndPos];
		gra.endPos = { pos[X].GetFloat(),pos[Y].GetFloat() };
		auto& color = doc[StartColor];
		gra.startColor = { color[R].GetFloat(),color[G].GetFloat(),color[B].GetFloat()};
		color = doc[EndColor];
		gra.endColor = { color[R].GetFloat(),color[G].GetFloat(),color[B].GetFloat() };
	}
	gra(handle_);
}

