#pragma once
#include "../../../Base/Draw/DrawBase.h"
#include"../Lane/LaneDivision.h"
#include"../DecisionTransform.h"
#include<vector>

class LaneDivision;
class DecisionTransform;

class LightDraw :
    public DrawBase
{
public:
    LightDraw(LaneDivisionConstPtr division, DecisionTransformConstPtr data);
    void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;
    void Draw() override;


private:

    int image_;

    LaneDivisionConstPtr division_;

    const InputManager::InputResult* inputData_;

    int EndPosY_;

    void SetFunc(GameCore* gameCore) override;

    void LoadImageData();

    void CreatePos(DecisionTransformConstPtr& data);

};

