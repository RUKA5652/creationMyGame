#pragma once
#include"../../../Base/GameObjBase.h"
#include<optional>
#include<string>
#include "ReelData.h"
#include"../../../../Scene/UsingChangeSceneFunc.h"
#include "ReelAnimData.h"

class ReelSound;

/// <summary>
/// ���[���Ǘ�class
/// </summary>
class Reel
	:public ObjBase
{
public:
	Reel(Beat::ReelDataPtr reelData, ReelSound* reelSound,const ChengeSceneFunc::CreateGameFunc& func);

	~Reel();

private:

	Beat::ReelDataPtr reelData_;
	ReelAnimData animData_;

};

/*
	�ȃt�H���_���I������Ē��g���W�J����
	�t�H���_�̕`�揇�Ԃ̓\�[�g��(���C���\�[�g(��ԋ���),
	�����t�H���_���܂Ƃ߂�,���O��)
	���̃t�H���_�̋Ȃ��Ԃɗ���܂ł��ЂƂ�����ɂ���
	�擪�̋Ȃ��t�H���_�̃T���l�Ƃ��Ĉ���

*/

