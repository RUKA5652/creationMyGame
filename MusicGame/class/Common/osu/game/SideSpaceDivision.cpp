#include "SideSpaceDivision.h"
#include "../LoadConfigData.h"

SideSpaceDivision::SideSpaceDivision()
{
    //���[�����g�p�����ꍇCircleSize�f�[�^�������Ă���
    //SetDivison(2.0 / 8.0);
    SetDivison(lpConfigData->GetConfigData().SideSpaceDivison);
}

const double& SideSpaceDivision::GetDivisionSpaceRatio() const
{
    return divisionSpaceRatio;
}

void SideSpaceDivision::SetDivison(double data)
{
    divisionSpaceRatio = data;
}
