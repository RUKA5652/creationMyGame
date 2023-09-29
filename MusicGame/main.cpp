#include<Windows.h>
#include"class/GameInstance.h"
#include"class/Manager/SceneManager.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//�G���g���[�|�C���g 
{
	SceneManager sceneMang;
	//�Z�b�g�A�b�v���������s������N�����Ȃ�
	if (!GameInstance()(sceneMang))
	{
		return -1;
	}
	sceneMang.run();

	sceneMang.Delete();

	return 0;
}


