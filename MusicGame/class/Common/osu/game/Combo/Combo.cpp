#include "Combo.h"
#include"../../../Base/GameCore.h"
#include<string>
#include"ComboDraw.h"
#include "ComboUpdate.h"


Combo::Combo(Beat::HitsDataPtr hitdata)
	:ObjBase(1,1)
{
	//loop_ = std::make_unique<ComboUpdate>(hitdata_,cnt_);
	update_.emplace_back(std::make_unique<ComboUpdate>(hitdata));
	draw_.emplace_back(std::make_shared<ComboDraw>(hitdata));
}


