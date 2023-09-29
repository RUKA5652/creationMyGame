#include "ResultSharingData.h"
#include "../Skin/Image/SkinImage.h"
#include "../../WindowSize.h"
#include"../HistoryScore/MakeScoreRank.h"

ResultSharingData::ResultSharingData(const std::string& filePass, Beat::ResultDataConstPtr& resultData, ResultScene::FuncData& func)
{
	rank.Init(resultData);
	//ç∂Ç©ÇÁèáÇ…äiî[Ç∑ÇÈ
	selects.emplace_back(std::make_unique<Retry>(rank,std::bind(func.changeGame, filePass)));
	selects.emplace_back(std::make_unique<Back>(func.changeSelect));
	selects.shrink_to_fit();
}

ResultSharingData::Rank::Rank()
{
	rankImage = -1;
	soundHandle = -1;
}

ResultSharingData::Rank::~Rank()
{
	DeleteSoundMem(soundHandle);
}

void ResultSharingData::Rank::Init(Beat::ResultDataConstPtr& resultData)
{
	int x, y;
	GetGraphSize(lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::Rank), &x, &y);
	pos.x = lpWindowSize->GetSize().x - x - 50;
	pos.y = y;
	CreateRank(resultData);

}

void ResultSharingData::Rank::CreateRank(Beat::ResultDataConstPtr& resultData)
{
	std::string soundFileName;
	auto score = resultData->hitsData->score;
	auto result = MakeScoreRank()(static_cast<int>(score));
	rankImage = result.first[0];
	soundFileName = result.second;
	SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
	soundHandle = LoadSoundMem(("resource/skin/result/" + soundFileName + ".wav").c_str());
	SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
}

ResultSharingData::Retry::Retry(Rank& rank, std::function<void(void)> func)
{
	this->func = std::move(func);
	int x, y;
	GetGraphSize(rank.rankImage, &x, &y);
	pos.x = rank.pos.x;
	pos.y = rank.pos.y + y;
	blendParam = 1;
	image = lpSkinImagePtr.GetAnimHandle(Beat::SkinImageType::Retry);
}

ResultSharingData::Back::Back(std::function<void(void)> func)
{
	this->func = std::move(func);
	image = lpSkinImagePtr.GetAnimHandle(Beat::SkinImageType::BACK);
	int x, y;
	GetGraphSize(lpSkinImagePtr.GetImageHandle(image), &x, &y);
	auto winSize = lpWindowSize->GetSize();
	pos.x = 0;
	pos.y = winSize.y - y;
	blendParam = 0.5;
}

ResultSharingData::Select::Select()
{
	blendParam = 0;
	image = -1;
}
