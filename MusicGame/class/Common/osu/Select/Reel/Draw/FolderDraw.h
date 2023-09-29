#pragma once
#include"../../../../Base/Draw/DrawBase.h"
#include"../ReelData.h"
#include"../../../../template/Vector2.h"
#include<DxLib.h>
#include<array>
#include "../ReelAnimData.h"



class FolderDraw
	:public DrawBase
{
public:
	FolderDraw(Beat::ReelDataPtr reelData, ReelAnimData& animData);
	~FolderDraw();
	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;

	void Draw() override;

	void SetFunc(GameCore* gameCore) override;
private:
	Beat::ReelDataPtr reelData_;

	Vector2 folderImageSize_;

	int centerPosY_;

	int upIndexCnt_;
	int downIndexCnt_;

	int drawHandle_;

	ReelAnimData& animData_;

	Timer::DeletaTime time_;

	bool flashFlag_;

	void Init();
	//ヘッドのデータを描画する
	void DrawMenu(int offsetX, int offsetY, Beat::ReelData::MapGroup& group, bool flag);
	//beatマップデータを描画する
	void DrawMenu(int offsetX, int offsetY, const Beat::BeatMap* map, bool flag);

	void DrawSelectGroup();

	void DrawNotSelectGroup();

};