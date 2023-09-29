#pragma once
#include<memory>
#include <forward_list>
#include<mutex>

class BaseScene;
struct GameInstance;


class SceneManager
{
public:
	//using NowScene = std::forward_list<std::unique_ptr<BaseScene>>::iterator;
	using NowScene = std::unique_ptr<BaseScene>;

	SceneManager();
	~SceneManager();

	void ProcessInput();

	//毎フレーム呼ばれる
	void Update();
	//毎フレーム呼ばれる
	void Draw();

	void run();

	void Delete();

private:	

	SceneManager(SceneManager&) = delete;

	NowScene nowScene_;


	friend GameInstance;
};

