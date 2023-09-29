#pragma once
#include"../../Base/Update/UpdateBase.h"
#include"ResultSharingData.h"


class ResultUpdate
	:public UpdateBase
{
public:
	ResultUpdate(ResultSharingDataConstPtr sharData);

	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;

private:

	void Init();

	void Select(const InputManager& input);

	ResultSharingData::SelectsItr itr_;

	ResultSharingDataConstPtr sharData_;

	bool voiceOneShot_;
};

