#pragma once
#include"../LoadSectionBase.h"
#include <functional>
#include <optional>
#include<memory>
#include"../../../GeneralData.h"
#include "../LoadFunc.h"


class GeneralLoad:
	public LoadSectionBase<Beat::General>
{
public:
	GeneralLoad();
	~GeneralLoad();

	bool LoadFile(const std::string& fileData, Beat::LoadDataPtr data) override;

private:
	void Init();

};

