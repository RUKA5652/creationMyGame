#pragma once
#include<memory>
#include<optional>
#include"../Timer/LoopTimer.h"
#include"../Common/Base/GameCore.h"
#include"../Input/InputManager.h"

class EffectPoly;

/// <summary>
/// ���ׂẴV�[���̊��N���X
/// </summary>
class BaseScene
{
public:
	BaseScene();
	virtual ~BaseScene();
	//���[�U�[���͂��ׂĂ̏���
	virtual void ProcessInput();
	void TimeUpdate();
	//���t���[���Ă΂��
	virtual std::unique_ptr<BaseScene> Update(std::unique_ptr<BaseScene> inScene) = 0;

	virtual void DrawOnScreen();

	//�`��()
	virtual void Draw();

	void DrawUpdate();

	DeletaTimeConst& GetDeletaTime();

protected:
	std::unique_ptr<LoopTimer> timer_;

	//�������^�C�~���O�����炵����
	std::unique_ptr<GameCore> core_;

	std::unique_ptr<InputManager> input_;


	int handle_;
	friend EffectPoly;
private:



};

