#pragma once
#include<vector>
#include"Scene/BaseScene.h"

class SceneManager;
/// <summary>
/// Dxlib��A�V�[���}�l�[�W���[�̃Z�b�g�A�b�v
/// �v���O�����̊J�n���ȍ~����Ȃ��̂Ŋ֐��I�u�W�F�N�g�Ƃ��Đ錾
/// </summary>
struct GameInstance
{
public:

	bool operator()(SceneManager& sceneManager);
private:



};

