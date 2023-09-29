#pragma once
#include<memory>
#include<optional>
#include"../Timer/LoopTimer.h"
#include"../Common/Base/GameCore.h"
#include"../Input/InputManager.h"

class EffectPoly;

/// <summary>
/// すべてのシーンの基底クラス
/// </summary>
class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	//ユーザー入力すべての処理
	virtual void ProcessInput();
	void TimeUpdate();
	//毎フレーム呼ばれる
	virtual std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> inScene) = 0;

	virtual void DrawOnScreen();

	//描画()
	virtual void Draw();

	void DrawUpdate();

	DeletaTimeConst& GetDeletaTime();

protected:
	std::unique_ptr<LoopTimer> timer_;

	//初期化タイミングをずらしたい
	std::unique_ptr<GameCore> core_;

	std::unique_ptr<InputManager> input_;


	int handle_;
	friend EffectPoly;
private:



};

