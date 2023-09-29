#pragma once
#include"../../../Base/Update/UpdateBase.h"
#include<memory>
#include<functional>
#include "CursorShareData.h"
/// <summary>
/// カーソル更新
/// </summary>
class TitleCursorUpdate
	:public UpdateBase
{
public:
	TitleCursorUpdate(std::shared_ptr<CursorShareData> shareData,std::shared_ptr<std::function<void(void)>> func);
	~TitleCursorUpdate();
	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;
private:
	std::shared_ptr<std::function<void(void)>> func_;
	std::shared_ptr<CursorShareData> shareData_;
	int voiceHandle_;
	int StartSHadle_;

	void Load();

};

