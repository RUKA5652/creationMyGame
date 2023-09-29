#pragma once
#include"../../../Base/GameObjBase.h"
#include<optional>
#include<string>
#include "ReelData.h"
#include"../../../../Scene/UsingChangeSceneFunc.h"
#include "ReelAnimData.h"

class ReelSound;

/// <summary>
/// リール管理class
/// </summary>
class Reel
	:public ObjBase
{
public:
	Reel(Beat::ReelDataPtr reelData, ReelSound* reelSound,const ChengeSceneFunc::CreateGameFunc& func);

	~Reel();

private:

	Beat::ReelDataPtr reelData_;
	ReelAnimData animData_;

};

/*
	曲フォルダが選択されて中身が展開する
	フォルダの描画順番はソート順(メインソート(一番強い),
	同じフォルダをまとめる,名前順)
	他のフォルダの曲が間に来るまでをひとくくりにする
	先頭の曲をフォルダのサムネとして扱う

*/

