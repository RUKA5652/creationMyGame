#pragma once
#include "../LoadSectionBase.h"
#include "../../../Difficulty.h"

class DifficultyLoad :
    public LoadSectionBase<Beat::Difficulty>
{
public:
    DifficultyLoad();

    bool LoadFile(const std::string& fileData, Beat::LoadDataPtr data) override;
private:
    void Init();
};

