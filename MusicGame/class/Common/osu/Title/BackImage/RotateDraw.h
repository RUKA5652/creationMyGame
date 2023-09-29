#pragma once
#include <array>
#include<DxLib.h>
#include<vector>
#include<random>
#include<thread>
#include<filesystem>
#include "../../../../Timer/Timer.h"
#include"../../../template/Vector2.h"


/// <summary>
/// 回るタイトル背景オブジェクトの描画 
/// </summary>
class RotateDraw
{
public:
	RotateDraw();
	~RotateDraw();
	//描画
	void Draw();
	//更新
	void Update(Timer::DeletaTimeConst& delta);
private:
	struct PolyData
	{
		//回転の中心
		FLOAT3 center;
		//移動ベクトル
		FLOAT2  moveVec;
		//角度
		float deg;
		//イメージハンドル
		int image;
		//描画ポリゴンデータ
		std::array<VERTEX3D, 4> poly;
	};
	//リソースフォルダデータ
	std::vector<int> imageHandles_;

	//生成処理用スレッド
	std::jthread geneThread_;

	//現在生成されいてる数
	int geneCnt_;

	//ポリゴンデータ群
	std::vector<PolyData> polyDatas_;

	//乱数生成器
	std::mt19937_64 rand_;

	//生成最大数
	int maxCnt_;

	//生成待機時間
	int waitTime_;

	//大きさの最小値
	float sizeBtom_;

	//色の最小値
	float colorBtom_;

	//回転角の上限
	int degree_;

	//移動制限
	Vector2 moveVec_;

	//ポリゴンデータ作成
	void MakePolyData();
	//PolyDataの値を作りセットする
	void MakePoly(PolyData& polyData, FLOAT2 pos, FLOAT4 color, float sizeX, float sizeY);
	//Y軸回転
	void Rotate(PolyData& polyData, Timer::DeletaTimeConst& delta);
	//移動
	void Move(PolyData& polyData , Timer::DeletaTimeConst& delta);
	//削除チェック
	void CheckDelet();
	//生成
	void MakeGenerationThread();
	// <param name="num">値範囲</param>
	float GetRand(float num);
	//フォルダロードに投げる関数
	void SetImage(const std::filesystem::path& path, std::string&& fileName);
	//設定読み込み
	std::string Load();
};

