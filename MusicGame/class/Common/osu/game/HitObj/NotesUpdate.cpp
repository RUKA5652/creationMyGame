#include"NotesUpdate.h"
#include "../../../../SoundVolume/SoundVolume.h"


NotesUpdate::NotesUpdate(HitObjVecConstPtr objData, Notes::Initialization& initData, std::function<void(void)> func)
	:generater_(objData, initData.division,initData.decisionData, initData.noteData, initData.noteSize)
	,move_(initData.noteData, initData.hitdata,initData.length, initData.decisionData)
	, func_(func)
{
	hitData_ = initData.hitdata;
	resultConboVoice_[0] = LoadSoundMem("resource/skin/Game/fullCombo.wav");
	resultConboVoice_[1] = LoadSoundMem("resource/skin/Game/allPerfect.wav");
	soundFlag_ = false;
}

void NotesUpdate::Update(Timer::DeletaTimeConst& delta,const InputManager& input)
{
	generater_.Update(delta,input);
	move_.Update(delta,input);
#ifdef _DEBUG
	if (CheckHitKey(KEY_INPUT_0))
	{
		func_();
	}
#endif // _DEBUG

	if (generater_.GetEnd() && move_.GetEnd())
	{
		func_();
		if (!soundFlag_)
		{
			soundFlag_ = true;
			int index = 1;
			for (auto& [key,count] : hitData_->result)
			{
				if (key == Beat::HitResult::Type::BAD && count > 0)
				{
					index = -1;
					break;
				}
				if (key != Beat::HitResult::Type::JUST && count > 0)
				{
					index = 0;
				}
			}
			if (index != -1)
			{
				lpVolumeMng.PlaySoundMem(resultConboVoice_[index], Sound::Type::SE, DX_PLAYTYPE_BACK, false);
			}
		}
	}
}
