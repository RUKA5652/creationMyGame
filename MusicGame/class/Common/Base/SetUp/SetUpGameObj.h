#pragma once
#include<vector>
#include"../GameObjBase.h"
#include"../BaseData.h"


class GameCore;
class ObjBase;
class BaseData;
/// <summary>
/// GameObjからGameCoreに必要な情報をセットする
/// </summary>
class SetUpGameObj
{
public:
	virtual ~SetUpGameObj();
	virtual void SetUp(GameCore* core);
	virtual void SetGameObj(ObjBasePtr obj) final;
private:
	std::vector<ObjBasePtr> objData_;
	GameCore* core_;
	void Add();
protected:
	virtual void SetGameCore(GameCore* core) final;
	virtual void SetObjCore() final;
	virtual void MakeObj() = 0;

};

