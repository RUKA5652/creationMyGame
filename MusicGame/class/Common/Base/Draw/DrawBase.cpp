#include "DrawBase.h"
#include "../../../../_debug/_DebugConOut.h"

DrawBase::~DrawBase()
{
	TRACE("DrawBase���\n");
}

void DrawBase::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
}

void DrawBase::SetFunc(GameCore* gameCore)
{
}

