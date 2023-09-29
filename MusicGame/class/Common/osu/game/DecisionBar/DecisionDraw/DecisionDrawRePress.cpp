#include "DecisionDrawRePress.h"
#include "../../../../WindowSize.h"
#include"../../../../../shaderDraw/DxShDraw.h"
#include "../../../../../../_debug/_DebugConOut.h"
#include"../../../../../AnimCurve/animCurve.h"


namespace
{
	constexpr int startLife = 10;
	constexpr float ExSize = 0.4f;
}

DecisionDrawRePress::DecisionDrawRePress(Beat::HitsDataConstPtr hitsData)
	:DecisionDrawInterface::DecisionDrawInterface(hitsData)
{
	const auto& windowSize = lpWindowSize->GetSize();
	offset_ = { windowSize.x / 2 ,windowSize.y / 2 };
	drawData_.flag = false;
	shaderHandle_ = LoadPixelShader("resource/shader/UVScroll.pso");
	subImage_ = LoadGraph("resource/skin/Default/subImage.png");
	InitPolyData();





}


DecisionDrawRePress::~DecisionDrawRePress()
{
	DeleteShader(shaderHandle_);
	DeleteGraph(subImage_);
}

void DecisionDrawRePress::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	if (drawData_.flag)
	{
		drawData_.lifeSpan -= 1;
		if (drawData_.lifeSpan < 0)
		{
			drawData_.flag = false;
		}
		else
		{
			thred_ = std::jthread([&] {
				//èkè¨î{ó¶
				auto t = 1.0f - static_cast<float>(drawData_.lifeSpan) / static_cast<float>(startLife);
				auto exSize = std::lerp(ExSize, 0.7f,  animCurve::MoveOutIn(t, 4));
				auto sizeX = drawData_.sizeX / 2 * exSize;
				auto sizeY = drawData_.sizeY / 2 * exSize;
				polyData_[0].pos.x = drawData_.pos.x - sizeX;
				polyData_[0].pos.y = drawData_.pos.y - sizeY;
				polyData_[0].u = 0;
				polyData_[0].v = 0;
				polyData_[0].su = 0;
				polyData_[0].sv = 0;

				polyData_[1].pos.x = drawData_.pos.x + sizeX;
				polyData_[1].pos.y = drawData_.pos.y - sizeY;
				polyData_[1].u = 1;
				polyData_[1].v = 0;
				polyData_[1].su = 1;
				polyData_[1].sv = 0;

				polyData_[2].pos.x = drawData_.pos.x - sizeX;
				polyData_[2].pos.y = drawData_.pos.y + sizeY;
				polyData_[2].u = 0;
				polyData_[2].v = 1;
				polyData_[2].su = 0;
				polyData_[2].sv = 1;

				polyData_[3].pos.x = drawData_.pos.x + sizeX;
				polyData_[3].pos.y = drawData_.pos.y + sizeY;
				polyData_[3].u = 1;
				polyData_[3].v = 1;
				polyData_[3].su = 1;
				polyData_[3].sv = 1;

				if (drawData_.subImage == subImage_)
				{
					/** //â°
					polyData_[0].su = std::lerp(0, 1, t);
					polyData_[0].sv = 0;
					polyData_[1].su = std::lerp(1, 0, t);
					polyData_[1].sv = 0;
					polyData_[2].su = std::lerp(0, 1, t);
					polyData_[2].sv = 1;
					polyData_[3].su = std::lerp(1, 0, t);
					polyData_[3].sv = 1;
					/*/ //èc
					polyData_[0].su = 0;
					polyData_[0].sv = std::lerp(0.5f, 1, t);
					polyData_[1].su = 1; 
					polyData_[1].sv = std::lerp(0.5f, 1, t);
					polyData_[2].su = 0;
					polyData_[2].sv = std::lerp(1, 0.5f, t);
					polyData_[3].su = 1;
					polyData_[3].sv = std::lerp(1, 0.5f, t);
					/**/
				}


				});
		}
	}
}

void DecisionDrawRePress::Draw()
{
	if (drawData_.flag)
	{
		if (thred_.joinable())
		{
			thred_.join();
		}
		//DrawGraph(drawData_.pos.x, drawData_.pos.y, drawData_.handle, true); 

		//DrawPrimitive2D(polyData_.data(), polyData_.size(), DX_PRIMTYPE_TRIANGLESTRIP, drawData_.handle, true);



		DxShDraw::DrawGraph(polyData_, drawData_.handle,[&](){	
			SetUsePixelShader(shaderHandle_);
		SetUseTextureToShader(0, drawData_.handle);
		SetUseTextureToShader(1, drawData_.subImage); });
	}
}

void DecisionDrawRePress::Create(const Beat::Type& type)
{
	drawData_.handle = imageData_.at(type);
	drawData_.subImage = type == Beat::Type::JUST ? subImage_ : drawData_.handle;
	drawData_.lifeSpan = startLife;
	GetGraphSize(drawData_.handle, &drawData_.sizeX, &drawData_.sizeY);
	drawData_.pos = offset_;
	//drawData_.pos.x -= drawData_.sizeX ;
	drawData_.pos.y -= drawData_.sizeY /2;

	drawData_.flag = true;
}

void DecisionDrawRePress::InitPolyData()
{
	for (auto& d : polyData_)
	{
		d.rhw = 1.0f;
		d.dif = GetColorU8(0xff, 0xff, 0xff, 0xff);
		d.spc = GetColorU8(0x00, 0x00, 0x00, 0x00);
		d.u = 0.0f;
		d.v = 0.0f;
		d.su = 0.0f;
		d.sv = 0.0f;
		d.pos.z = 0.0f;
	}
}

DecisionDrawRePress::DrawData::DrawData()
{
	flag = false;
	sizeX = 0;
	sizeY = 0;
	subImage = -1;
}
