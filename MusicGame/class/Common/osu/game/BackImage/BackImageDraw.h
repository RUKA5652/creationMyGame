#pragma once
#include"../../../Base/Draw/DrawBase.h"
#include"../../EventsData.h"
#include"../../../template/Vector2.h"
#include <string>


class BackImageDraw
	:public DrawBase
{
public:
	BackImageDraw(const std::string& musicScorePass, std::shared_ptr<const Beat::Events::BackImage> data);

	~BackImageDraw();

	void Draw() override;
private:
	Vector2 pos;
	

	int handle_;

	void SetFunc(GameCore* gameCore) override;

};

