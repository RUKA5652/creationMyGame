#pragma once
#include"../../../Base/Draw/DrawBase.h"
#include"../../../template/Vector2.h"
#include<memory>
#include "CursorShareData.h"
/// <summary>
/// ÉJÅ[É\Éãï`âÊ
/// </summary>
class TitleCursorDraw
	:public DrawBase
{
public:
	TitleCursorDraw(std::shared_ptr<CursorShareData> shareData);
	~TitleCursorDraw();
	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;
	void Draw() override;
private:
	void SetFunc(GameCore* gameCore) override;
	Timer::DeletaTime time_;
	bool flag_;
	int handle_;
	Vector2 pos_;

	int onTime_;
	int offTime_;

	int endTime_;

	std::shared_ptr<CursorShareData> shareData_;

	void OnUpdate(Timer::DeletaTimeConst& delta);
	void OffUpdate(Timer::DeletaTimeConst& delta);

	void Load();

};

