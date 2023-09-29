#pragma once
#include "../LoadSectionBase.h"
#include"../../../EventsData.h"

class EventLoad :
    public LoadSectionBase<Beat::Events>
{
public:
    EventLoad();

    bool LoadFile(const std::string& fileData, Beat::LoadDataPtr data) override;
private:
    void Init();


};

