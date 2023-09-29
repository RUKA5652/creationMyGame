#pragma once
#include"LaneDrawBase.h"
#include"StraightLaneDraw.h"
#include<array>
#include<DxLib.h>

class ObliqueLaneDraw
	:public LaneDrawBase
{
public:
    ObliqueLaneDraw(LaneDivisionConstPtr&& divData);
    ~ObliqueLaneDraw();
    void Draw() override;

    void DrawLane();
    void SetScreen();
    void DrawOblique();
private:
    enum class State
    {
        Set,
        LaneDraw,
        DrawSetScreen,
        SetEffect,
        DrawEffect,
    };

    void SetFunc(GameCore* gameCore) override;


    void MakeScreen();
    void MakePolyGon();

    void SetEffectScreen();
    void DrawEffectScreen();

    StraightLaneDraw draw_;

    State state_;

    int handle_;
    int effectHandle_;
    int inHandle_;
    std::array<VERTEX3D, 4> polyData_;



};



