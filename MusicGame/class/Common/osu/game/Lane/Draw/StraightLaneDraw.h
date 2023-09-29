#pragma once
#include"LaneDrawBase.h"
#include<memory>
#include"../LaneType.h"
#include"../LaneDivision.h"

/// <summary>
/// 直線のレーンタイプの描画
/// </summary>
class StraightLaneDraw :
    public LaneDrawBase
{
public:
    StraightLaneDraw(LaneDivisionConstPtr&& divData);
    StraightLaneDraw(LaneDivisionConstPtr& divData);
    ~StraightLaneDraw();
    void Draw() override;


private:
    void Init();

    //1レーン分のイメージ
    int laneImage_;
    //１レーン分のイメージを合体させたイメージ
    int multipleLaneImage_;

    //レーンの数
    int laneNum;

    void SetFunc(GameCore* gameCore) override;

    //合体イメージ作成
    void CreateMultipleLane(LaneDivisionConstPtr& divData);

};

