#include "WaitSound.h"
#include <DxLib.h>
#include<filesystem>
#include "../../SoundVolume/SoundVolume.h"
#include"../../../rapidjson/document.h"
#include"../../JsonParam/IOJSON.h"

/// <summary>
/// JSONで使用するデータ
/// </summary>
inline namespace JSON
{
	//ファイル名前
	constexpr const char* FileName = "WaitSound";
	//キー
	constexpr const char* soundPath = "path";
	constexpr const char* bufferNum = "BufferNum";
}

WaitSound::WaitSound(double beatLength, int waitSoundCount)
{
	beatLength_ = beatLength;
	waitSoundCount_ = waitSoundCount;
	LoadFile();
	waitTime_ = beatLength_ * waitSoundCount_;
}

WaitSound::~WaitSound()
{
	DeleteSoundMem(waitSoundHandle_);
#ifdef _SAVEJSON
	SaveFile();
#endif // _SAVEJSON
}

void WaitSound::WaitPlaySound(DeletaTimeConst& time)
{
	if (waitTime_ < 0)
	{
		return;
	}
	waitTime_ -= time;
	if ((waitTime_ / beatLength_) < waitSoundCount_)
	{
		waitSoundCount_--;
		if (waitSoundCount_ >= 0)
		{
			lpVolumeMng.PlaySoundMem(waitSoundHandle_, Sound::Type::SE,DX_PLAYTYPE_BACK);
		}
	}
}

void WaitSound::LoadFile()
{
	auto result = InPutJSON()(FileName);
	if (result)
	{
		auto& doc = result.value();
		waitSoundHandle_ = LoadSoundMem(doc[soundPath].GetString(), doc[bufferNum].GetInt());
	}
}
#ifdef _SAVEJSON

void WaitSound::SaveFile()
{
	rapidjson::Document doc;
	doc.SetObject();
	doc.AddMember(rapidjson::StringRef(soundPath), "resource/skin/Default/soft-hitnormal.wav", doc.GetAllocator());
	doc.AddMember(rapidjson::StringRef(bufferNum), 8, doc.GetAllocator());
	OutPutJSON()(doc, FileName);
}

#endif // _SAVEJSON

