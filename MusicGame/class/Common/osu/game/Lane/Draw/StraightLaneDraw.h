#pragma once
#include"LaneDrawBase.h"
#include<memory>
#include"../LaneType.h"
#include"../LaneDivision.h"

/// <summary>
/// �����̃��[���^�C�v�̕`��
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

    //1���[�����̃C���[�W
    int laneImage_;
    //�P���[�����̃C���[�W�����̂������C���[�W
    int multipleLaneImage_;

    //���[���̐�
    int laneNum;

    void SetFunc(GameCore* gameCore) override;

    //���̃C���[�W�쐬
    void CreateMultipleLane(LaneDivisionConstPtr& divData);

};

