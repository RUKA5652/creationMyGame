#include "TitleCursorUpdate.h"
#include"../../../../Input/Title/TitleSceneInput.h"
#include<DxLib.h>
#include "../../../../SoundVolume/SoundVolume.h"
#include"../../../../JsonParam/IOJSON.h"


/// <summary>
/// JSON�Ŏg�p����f�[�^
/// </summary>
inline namespace JSON
{
	//�t�@�C�����O
	constexpr const char* FileName = "Title";
	//�I�u�W�F�N�g
	constexpr const char* ObjKey = "Cursor";
	//�L�[
	constexpr const char* Voice = "Voice";
	constexpr const char* Start = "Start";
}


TitleCursorUpdate::TitleCursorUpdate(std::shared_ptr<CursorShareData> shareData, std::shared_ptr<std::function<void(void)>> func)
{
	func_ = std::move(func);
	shareData_ = std::move(shareData);
	Load();
}

TitleCursorUpdate::~TitleCursorUpdate()
{
	DeleteSoundMem(StartSHadle_);
	DeleteSoundMem(voiceHandle_);
}

void TitleCursorUpdate::Update(Timer::DeletaTimeConst& delta, const InputManager& input)
{
	if (shareData_->endFlag)
	{
		(*func_)();
	}
	if(shareData_->startFlag)
	{
		return;
	}
	auto& data = input.GetInputData();
	if (data.at(static_cast<int>(TITLE::DECIDE)).oneShot())
	{
		shareData_->startFlag = true;
		//PlaySoundMem(StartSHadle_,DX_PLAYTYPE_BACK);
		lpVolumeMng.PlaySoundMem(StartSHadle_, Sound::Type::SE, DX_PLAYTYPE_BACK);
		//PlaySoundMem(voiceHandle_, DX_PLAYTYPE_BACK);
		lpVolumeMng.PlaySoundMem(voiceHandle_, Sound::Type::SE, DX_PLAYTYPE_BACK);
	}


}

void TitleCursorUpdate::Load()
{
	//JSON�f�[�^�ǂݍ���
	auto result = InPutJSON()(FileName);
	//�i�[
	if (result)
	{
		auto& doc = result.value()[ObjKey];
		voiceHandle_ = LoadSoundMem(doc[Voice].GetString());
		StartSHadle_ = LoadSoundMem(doc[Start].GetString());
	}
}
