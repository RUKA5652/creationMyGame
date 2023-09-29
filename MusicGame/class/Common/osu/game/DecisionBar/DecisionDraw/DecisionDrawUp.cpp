#include "DecisionDrawUp.h"
#include "../../../../WindowSize.h"

constexpr int startLife = 10;

DecisionDrawUp::DecisionDrawUp(Beat::HitsDataConstPtr hitsData)
	:DecisionDrawInterface::DecisionDrawInterface(hitsData)
{
	const auto& windowSize = lpWindowSize->GetSize();
	offset_ = { windowSize.x / 2 ,windowSize.y / 2 };
}

void DecisionDrawUp::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	const auto& windowSize = lpWindowSize->GetSize();
	Vector2 center = { windowSize.x / 2 ,windowSize.y / 2 };
	for (auto& data : dataDeque_)
	{
		data.lifeSpan -= 1;
		data.pos.y -= 5;
	}
	std::erase_if(dataDeque_, [](DrawData& data) {return data.lifeSpan <= 0; });
}

void DecisionDrawUp::Draw()
{
	//ƒqƒbƒg”»’è•`‰æ
	for (auto& data : dataDeque_)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * (1 - (data.lifeSpan / startLife))));

		DrawGraph(data.pos.x, data.pos.y, data.handle, true);
		//DrawBox(data.pos.x, data.pos.y, data.pos.x + 30, data.pos.y + 30, data.handle, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void DecisionDrawUp::Create(const Beat::Type& type)
{
	DrawData data;
	data.handle = imageData_.at(type);
	data.lifeSpan = startLife;
	int x, y;
	GetGraphSize(data.handle, &x, &y);
	data.pos = offset_;
	data.pos.x -= x / 2;
	data.pos.y -= y / 2;
	dataDeque_.emplace_back(data);
}
