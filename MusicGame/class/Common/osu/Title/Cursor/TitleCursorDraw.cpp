#include "TitleCursorDraw.h"
#include"../../../Base/GameCore.h"
#include "../TitleDrawIndex.h"
#include"../../../WindowSize.h"
#include<DxLib.h>
#include"../../../../JsonParam/IOJSON.h"


/// <summary>
/// JSONで使用するデータ
/// </summary>
inline namespace JSON
{
	//ファイル名前
	constexpr const char* FileName = "Title";
	//オブジェクトキー
	constexpr const char* ObjKey = "Cursor";
	//キー
	constexpr const char* Image = "Image";
	constexpr const char* Pos = "Pos";
	constexpr const char* X = "x";
	constexpr const char* Y = "y";
	constexpr const char* ON = "ActiveTimeMs";
	constexpr const char* OFF = "NotActiveTimeMs";
}

TitleCursorDraw::TitleCursorDraw(std::shared_ptr<CursorShareData> shareData)
{
	Load();
	time_ = 0;
	endTime_ = 0;
	flag_ = true;
	shareData_ = std::move(shareData);
}

TitleCursorDraw::~TitleCursorDraw()
{
	DeleteGraph(handle_);
}

void TitleCursorDraw::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	if (shareData_->startFlag)
	{
		onTime_ = 50;
		offTime_ = 50;
		endTime_ += delta;
		if (endTime_ >= 2* 1000)
		{
			shareData_->endFlag = true;
		}
	}
	if (flag_)
	{
		OnUpdate(delta);
	}
	else
	{
		OffUpdate(delta);
	}
}

void TitleCursorDraw::OnUpdate(Timer::DeletaTimeConst& delta)
{
	time_ += delta;
	if (time_ > onTime_)
	{
		time_ = 0;
		flag_ = false;
	}

}

void TitleCursorDraw::OffUpdate(Timer::DeletaTimeConst& delta)
{
	time_ += delta;
	if (time_ > offTime_)
	{
		time_ = 0;
		flag_ = true;
	}

}

void TitleCursorDraw::Load()
{
	//JSONデータ読み込み
	auto result = InPutJSON()(FileName);
	//格納
	if (result)
	{
		auto& doc = result.value()[ObjKey];
		handle_ = LoadGraph(doc[Image].GetString());
		pos_.x = doc[Pos][X].GetInt();
		pos_.y = doc[Pos][Y].GetInt();
		onTime_ = doc[ON].GetInt();
		offTime_ = doc[OFF].GetInt();
	}
}

void TitleCursorDraw::Draw()
{
	if (!flag_)
	{
		return;
	}
	DrawGraph(pos_.x, pos_.y, handle_, true);
}

void TitleCursorDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(TitleDrawIndex::Cursor), shared_from_this());
}

