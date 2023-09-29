#pragma once
#include"../../../../Base/Draw/DrawBase.h"
#include"../ReelData.h"
#include"../../../HistoryScore/HistoryScore.h"
#include"../../../HistoryScore/HistoryScoreLoad.h"
#include"../../../HistoryScore/MakeScoreRank.h"
#include<array>

class SelectScoreDraw
	:public DrawBase
{
public:
	SelectScoreDraw(Beat::ReelDataPtr reelData);
	~SelectScoreDraw();

	void Update(Timer::DeletaTimeConst& delta, const InputManager& input) override;

	void Draw() override;

	void SetFunc(GameCore* gameCore) override;
private:
	enum class State
	{
		Non,
		Selet,
		Load,
	};
	
	Beat::ReelDataPtr reelData_;
	//現在描画しているscoreの曲パス
	std::string nowDrawPath_;
	//現在描画しているデータ
	HistoryScore score_;

	HistoryScoreLoad loadFunc_;
	
	State state_;

	Timer::DeletaTime waitTime_;

	int drawScreen_;

	const std::vector<Beat::SkinImage>& numImage_;

	Vector2 numImageSize_;
	int maxCnt_;

	Vector2 offsetPos_;

	MakeScoreRank makeRank_;


	int rankingDraw_;

	Vector2 rankGrapSize_;

	struct DrawLoadPrm
	{
		DrawLoadPrm();
		~DrawLoadPrm();
		void Update(Timer::DeletaTimeConst& delta);
		int shaderHndle;
		int mainTex;
		int thickTex;
		int buffHandle;
		int screen;
		float thicknessMax;
		float thicknessMin;
	};

	DrawLoadPrm drawLoadPrm_;

	int noDataImage_;

	Vector2 noDataDrawPos_;

	void DrawScore();

	void DrawNo();

	void DrawNonData();

	void LoadData();

	void DrawLoad();

};

