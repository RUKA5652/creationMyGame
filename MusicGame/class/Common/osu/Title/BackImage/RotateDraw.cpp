#include "RotateDraw.h"
#include<cmath>
#include"../../../WindowSize.h"
#include<numbers>
#include"../../../../RandSeed/RandSeed.h"
#include <execution>
#include "../../Skin/FolderSearch.h"
#include"../../../../JsonParam/IOJSON.h"


/// <summary>
/// JSONで使用するデータ
/// </summary>
inline namespace JSON
{
	//ファイル名前
	constexpr const char* FileName = "Title";
	//オブジェクト
	constexpr const char* ObjKey = "RotateIcon";
	//キー
	constexpr const char* MaxCnt = "MaxCnt";
	constexpr const char* WaitTime = "WaitTime";
	constexpr const char* FolderPass = "FolderPass";
	constexpr const char* SizeBtom = "SizeBtom";
	constexpr const char* ColorBtom = "ColorBtom";
	constexpr const char* Degree = "Degree";
	constexpr const char* MoveVec = "MoveVec";
	constexpr const char* X = "x";
	constexpr const char* Y = "y";
}





RotateDraw::RotateDraw()
{
	auto path = Load();
	FolderSearch(std::bind_front(&RotateDraw::SetImage, this))(path);

	auto& size = lpWindowSize->GetSize();
	rand_ = std::mt19937_64(lpSeedMng.GetSeed());
	MakeGenerationThread();
}

RotateDraw::~RotateDraw()
{
	for (auto& image : imageHandles_)
	{
		DeleteGraph(image);
	}
	geneThread_.request_stop();
	geneThread_.detach();
}

void RotateDraw::Draw()
{	
	auto inScreen = GetDrawScreen();
	auto flag = GetUseBackCulling();
	SetUseBackCulling(false);
	for (auto& poly : polyDatas_)
	{
		DrawPrimitive3D(poly.poly.data(), static_cast<int>(poly.poly.size()), DX_PRIMTYPE_TRIANGLESTRIP, poly.image, true);
	}
	SetUseBackCulling(flag);
}

void RotateDraw::Update(Timer::DeletaTimeConst& delta)
{	
	CheckDelet();
	std::for_each(std::execution::par,polyDatas_.begin(), polyDatas_.end(), [&](PolyData& data) {Rotate(data, delta); Move(data, delta); });

}

void RotateDraw::MakePolyData()
{
	if (polyDatas_.size() >= maxCnt_)
	{
		return;
	}
	auto& data = polyDatas_.emplace_back();
	auto& winSize = lpWindowSize->GetSize();
	//大きさ作成
	float imageX, imageY;
	data.image = imageHandles_[static_cast<int>(GetRand(static_cast<float>(imageHandles_.size())))];
	GetGraphSizeF(data.image, &imageX, &imageY);
	auto size = GetRand(imageY - sizeBtom_) + sizeBtom_;
	imageX = (size/imageY)* imageX;
	imageY = size;
	//座標作成
	auto sign = GetRand(2) == 0 ? -1 : 1;
	FLOAT2 pos = {-imageX - GetRand(imageX),
		-imageY / 2.0f + sign * GetRand(winSize.y / 2.0f)};
	//色作成
	FLOAT4 color = { GetRand(256), GetRand(256),GetRand(256),GetRand(256 - colorBtom_) + colorBtom_ };

	MakePoly(data, pos,color, imageX,imageY);
	data.deg = GetRand(static_cast<float>(degree_));
	data.moveVec = { GetRand(static_cast<float>(moveVec_.x)) + moveVec_.x ,GetRand(static_cast<float>(moveVec_.y)) + moveVec_.y };
}

void RotateDraw::MakePoly(PolyData& polyData, FLOAT2 pos,FLOAT4 color ,float sizeX, float sizeY)
{
	auto& poly = polyData.poly;
	for (auto& d : poly)
	{
		d.pos.x = pos.u;
		d.pos.y = pos.v;
		d.pos.z = 0;
		d.dif = GetColorU8((int)color.x, (int)color.y,
							(int)color.z, (int)color.z);
		d.spc = GetColorU8(0, 0, 0, 0);
	}
	poly[0].pos.x += 0;
	poly[0].pos.y += 0;
	poly[0].pos.z += 0;
	poly[0].u = 0;
	poly[0].v = 1;
	poly[1].pos.x += sizeX;
	poly[1].pos.y += 0;
	poly[1].pos.z += 0;
	poly[1].u = 1;
	poly[1].v = 1;

	poly[2].pos.x += 0;
	poly[2].pos.y += sizeY;
	poly[2].pos.z += 0;
	poly[2].u = 0;
	poly[2].v = 0;
	poly[3].pos.x += sizeX;
	poly[3].pos.y += sizeY;
	poly[3].pos.z += 0;
	poly[3].u = 1;
	poly[3].v = 0;

	polyData.center.x = pos.u + sizeX / 2;
	polyData.center.y = pos.v + sizeY / 2;
	polyData.center.z = 0;
}

void RotateDraw::Rotate(PolyData& polyData, Timer::DeletaTimeConst& delta)
{
	float time = delta / 1000.0f;
	float cos = std::cos(polyData.deg * time  * std::numbers::pi_v<float> / 180);
	float sin = std::sin(polyData.deg * time * std::numbers::pi_v<float> / 180);

	for (auto& data : polyData.poly)
	{
		// 回転の中心を原点に移動
		float x = data.pos.x - polyData.center.x;
		float y = data.pos.y - polyData.center.y;
		float z = data.pos.z - polyData.center.z;

		// 回転行列をかける
		float x_ = x * cos - z * sin;
		float y_ = y;
		float z_ = x * sin + z * cos;

		// 回転の中心を元に戻す
		data.pos.x = x_ + polyData.center.x;
		data.pos.y = y_ + polyData.center.y;
		data.pos.z = z_ + polyData.center.z;
	}
}

void RotateDraw::Move(PolyData& polyData, Timer::DeletaTimeConst& delta)
{
	float time = delta / 1000.0f;
	for (auto& data : polyData.poly)
	{
		data.pos.x += polyData.moveVec.u * time;
		data.pos.y += polyData.moveVec.v * time;
	}
	polyData.center.x += polyData.moveVec.u * time;
	polyData.center.y += polyData.moveVec.v * time;
}

void RotateDraw::CheckDelet()
{
	auto& windSize = lpWindowSize->GetSize();

	auto num = std::erase_if(polyDatas_, [windSize](PolyData& polyData) {
		if (windSize.y < polyData.poly[0].pos.y && windSize.y < polyData.poly[3].pos.y)
		{
			return true;
		}
		if (windSize.x < polyData.poly[0].pos.x && windSize.x < polyData.poly[3].pos.x)
		{
			return true;
		}
		return false; });

	if (num == 0)
	{
		return;
	}
	geneCnt_ -= static_cast<int>(num);
}

void RotateDraw::MakeGenerationThread()
{
	geneCnt_ = 0;
	geneThread_ = std::jthread([&](std::stop_token stoken) {
		for (; geneCnt_ < maxCnt_ || !stoken.stop_requested(); geneCnt_++)
		{
			std::this_thread::sleep_for(std::chrono::seconds(static_cast<int>(GetRand(static_cast<float>(waitTime_)))));
			if (stoken.stop_requested())
			{
				break;
			}
			MakePolyData();
		}
	});
}

float RotateDraw::GetRand(float num)
{
	return  static_cast<float>(rand_()%static_cast<int>(num));
}

void RotateDraw::SetImage(const std::filesystem::path& path, std::string&& fileName)
{
	imageHandles_.emplace_back(LoadGraph(path.string().c_str()));
}

std::string RotateDraw::Load()
{
	std::string path;
	//JSONデータ読み込み
	auto result = InPutJSON()(FileName);
	//格納
	if (result)
	{
		auto& doc = result.value()[ObjKey];
		maxCnt_ = doc[MaxCnt].GetInt();
		waitTime_ = doc[WaitTime].GetInt();
		path = doc[FolderPass].GetString();
		sizeBtom_ = doc[SizeBtom].GetFloat();
		colorBtom_ = doc[ColorBtom].GetFloat();
		degree_ = doc[Degree].GetInt();
		auto& vec = doc[MoveVec];
		moveVec_ = { vec[X].GetInt(),vec[Y].GetInt() };
	}
	return path;
}

