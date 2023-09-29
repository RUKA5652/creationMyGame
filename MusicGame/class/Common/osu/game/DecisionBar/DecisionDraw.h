#pragma once
#include "../../../Base/Draw/DrawBase.h"
#include "../DecisionData.h"
#include"../../../template/Vector2.h"
#include<deque>
#include"SetDrawEnum.h"


class DecisionDrawInterface;


class DecisionDraw :
    public DrawBase
{
public:
    DecisionDraw(Beat::HitsDataConstPtr hitsData, Decision::SetDrawFuncPtr drawSetFunc);
    ~DecisionDraw();
    void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;
    void Draw() override;

    void Create(const Beat::Type& type);

private:

    DecisionDrawInterface* drawInterFace_;

    void SetFunc(GameCore* gameCore) override;

};




