#pragma once
#include<vector>
#include"Scene/BaseScene.h"

class SceneManager;
/// <summary>
/// Dxlibや、シーンマネージャーのセットアップ
/// プログラムの開始時以降いらないので関数オブジェクトとして宣言
/// </summary>
struct GameInstance
{
public:

	bool operator()(SceneManager& sceneManager);
private:



};

