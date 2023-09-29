#include<Windows.h>
#include"class/GameInstance.h"
#include"class/Manager/SceneManager.h"


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_	HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)//エントリーポイント 
{
	SceneManager sceneMang;
	//セットアップ処理が失敗したら起動しない
	if (!GameInstance()(sceneMang))
	{
		return -1;
	}
	sceneMang.run();

	sceneMang.Delete();

	return 0;
}


