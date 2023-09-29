#pragma once
#include"../GameObjBase.h"
#include"../../../../_debug/_DebugConOut.h"

class SetUpGameObj;
/// <summary>
/// GameObj作成関数
/// </summary>
/// <typeparam name="T"></typeparam>
/// <typeparam name="F"></typeparam>
template<class T,class F = ObjBase>
class CreateSupport
{
public:
	CreateSupport();
	virtual ~CreateSupport();
	virtual T* CreateInitData() = 0;
	virtual ObjBasePtr CreateObj() = 0;
protected:
	T* initData_;
};

template<class T, class F>
inline CreateSupport<T, F>::CreateSupport()
{
	initData_ = nullptr;
}
template<class T, class F>
inline CreateSupport<T, F>::~CreateSupport()
{
	TRACE("クリエイトサポート解放\n");
}
;


