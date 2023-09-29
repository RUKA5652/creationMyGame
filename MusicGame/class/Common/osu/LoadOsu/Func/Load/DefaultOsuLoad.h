#pragma once
#include "../OsuLoadBase.h"
class DefaultOsuLoad :
    public OsuLoadBase
{
public:
    DefaultOsuLoad(Beat::LoadDataPtr& loadData);

private:

    void Init();

};



