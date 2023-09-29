#include "EffectPoly.h"

EffectPoly::EffectPoly(FLOAT4& ipadData)
	:ipadData_(ipadData)
{
	Init();
	moveTime_ = 0;
}

void EffectPoly::Draw(BaseScene* scene)
{
	if (scene == nullptr)
	{
		return;
	}
	DrawPrimitive2D(poly.data(), static_cast<int>(poly.size()), DX_PRIMTYPE_TRIANGLESTRIP, scene->handle_, true);
}

bool EffectPoly::GetEnd()
{
	return endFlag_;
}

void EffectPoly::Init()
{
	endFlag_ = false;
}
