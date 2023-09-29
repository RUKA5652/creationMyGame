#include "TitleHedDraw.h"
#include"../../../Base/GameCore.h"
#include"../TitleDrawIndex.h"
#include"../../../../JsonParam/IOJSON.h"


/// <summary>
/// JSONで使用するデータ
/// </summary>
inline namespace JSON
{
	//ファイル名前
	constexpr const char* FileName = "Title";
	//オブジェクト
	constexpr const char* ObjKey = "TitleLogo";
	//キー
	constexpr const char* Image = "Image";
	constexpr const char* BufferSize = "BufferSize";
	constexpr const char* Color = "Color";
	constexpr const char* R = "r";
	constexpr const char* G = "g";
	constexpr const char* B = "b";
	constexpr const char* Pos = "Pos";
	constexpr const char* X = "x";
	constexpr const char* Y = "y";
}


TitleHedDraw::TitleHedDraw(EqualizerEffect* effect)
{
	effect_ = effect;

	auto [param, pos] = Load();
	effect_->SetUp(param);
	effect_->drawPos = pos;
}

void TitleHedDraw::Draw()
{
	effect_->Draw();
}

void TitleHedDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(TitleDrawIndex::TitleHed), shared_from_this());
}

std::pair<EqualizerEffect::SetUpParam , EqualizerEffect::Pos> TitleHedDraw::Load()
{
	EqualizerEffect::SetUpParam param;
	EqualizerEffect::Pos pos;
	//JSONデータ読み込み
	auto result = InPutJSON()(FileName);
	//格納
	if (result)
	{
		using SetUpParam =  EqualizerEffect::SetUpParam;
		auto& doc = result.value()[ObjKey];
		param.imagePath = doc[Image].GetString();
		param.buffSize = doc[BufferSize].Get<SetUpParam::Size>();
		auto arry = doc[Color].GetArray();
		param.color1 = { arry[0][R].GetInt(),arry[0][G].GetInt(),arry[0][B].GetInt() };
		param.color2 = { arry[1][R].GetInt(),arry[1][G].GetInt(),arry[1][B].GetInt() };
		pos.x = doc[Pos][X].GetInt();
		pos.y = doc[Pos][Y].GetInt();
	}
	return { param,pos };
}
