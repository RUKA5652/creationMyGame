#pragma once
#include"../../../Base/Update/UpdateBase.h"
#include"../../../../Scene/GameScene.h"
#include"NotesGenerate.h"
#include"NotesMove.h"
#include "Notes.h"



class NotesUpdate
	:public UpdateBase
{
public:
	NotesUpdate(HitObjVecConstPtr objData, Notes::Initialization& initData, std::function<void(void)> func);
	void Update(Timer::DeletaTimeConst& delta,const InputManager& input) override;


private:
	NotesGenerate generater_;
	NotesMove move_;

	Beat::HitsDataConstPtr hitData_;

	std::function<void(void)> func_;

	std::array<int, 2> resultConboVoice_;

	bool soundFlag_;

};

