#pragma once
#include "../../DecisionData.h"
#include"../../../../template/Vector2.h"
#include "../../../../../Timer/Timer.h"
#include "../../../../../Input/InputManager.h"
#include "../SetDrawEnum.h"

class DecisionDrawInterface
{
public:

    DecisionDrawInterface(Beat::HitsDataConstPtr hitsData);
    virtual ~DecisionDrawInterface();
    virtual void Update(Timer::DeletaTimeConst& delta, const InputManager& input) = 0;
    virtual void Draw() = 0;

    virtual void Create(const Beat::Type& type) = 0;

protected:
    struct DrawData
    {
        int handle = -1;
        Vector2 pos;
        double lifeSpan = 0;
    };


    Vector2 offset_;

    Beat::HitsDataConstPtr hitsData_;

    std::map<Beat::Type, std::string> imagePass_;

    std::map<Beat::Type, int> imageData_;

private:
    void LoadImageData();


};

