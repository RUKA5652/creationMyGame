#pragma once
#include<memory>
#include<DxLib.h>
#include<functional>
#include"../Input/InputManager.h"
#include"SoundType.h"
#include"../Common/template/Vector2.h"
#include "../Timer/LoopTimer.h"


#define lpVolumeMng  SoundVolume::GetInstance()

class SoundVolume
{
public:
	using volume = float;

	static  SoundVolume& GetInstance(void)
	{
		static SoundVolume s_Instance;
		return s_Instance;
	}

	int GetVolume(Sound::Type type)const;
	int PlaySoundMem(int handle,Sound::Type type, int PlayType = DX_PLAYTYPE_LOOP, int TopPositionFlag = true)const;

	void SetFollowingHandle(int handle, Sound::Type type);
	void RemoveSetFollowingHandle(int handle, Sound::Type type);



	void  ProcessInput();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="pos">画面左下からどれだけ内側に寄せるか</param>
	void DrawParam(Vector2 pos);

private:
	enum class State
	{
		NON,
		STANDBY,
		OPUNE,
	};

	struct shaderPrm
	{
		~shaderPrm();
		int backImage;
		//描画したいイメージ
		int mainTex;
		//濃淡情報イメージ
		int thickTex;
		//使用する値
		float thickness;
		//handle
		int buffHandle_;
	};

	std::map<Sound::Type, volume> volume_;
	//一緒に音を変えたい
	std::map<Sound::Type , std::vector<int>> soundHandle_;

	std::unique_ptr<InputManager> input_;

	int screen_;

	int shaderHndle_;

	shaderPrm songDrawPrm_;

	shaderPrm seDrawPrm_;

	State nowState_;

	std::map<State, std::function<void(void)>> update_;

	Timer::DeletaTime clauseTime_;

	LoopTimer timer_;

	SoundVolume();
	~SoundVolume();

	void LoadVolume();

	void UpdateVolume();

	void UpdateNon();

	void UpdateStandby(); 

	void CountClause();

	void ShaderDraw(Vector2 pos, shaderPrm& prm);

	void Save();
	

};

