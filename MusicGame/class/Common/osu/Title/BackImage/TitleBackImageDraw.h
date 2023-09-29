#pragma once
#include"../../../Base/Draw/DrawBase.h"
#include <string>
#include"../../../template/Vector3.h"
#include"RotateDraw.h"
/// <summary>
/// �^�C�g���w�i�`��
/// </summary>
class TitleBackImageDraw
	:public DrawBase
{
public:
	TitleBackImageDraw();

	~TitleBackImageDraw();
	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;

	void Draw() override;

private:

	int handle_;

	RotateDraw rotateDraw_;

	void SetFunc(GameCore* gameCore) override;

	void Load();
};

