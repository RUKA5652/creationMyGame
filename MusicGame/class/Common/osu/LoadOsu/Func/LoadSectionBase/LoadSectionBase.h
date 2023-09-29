#pragma once
#include"../LoadSectionBase.h"
#include<sstream>

template<class T>
inline LoadSectionBase<T>::LoadSectionBase(std::string title)
	:title_(title)
{
	Init();

}

template<class T>
inline LoadSectionBase<T>::~LoadSectionBase()
{
}

template<class T>
inline bool LoadSectionBase<T>::LoadFile(const std::string& fileData, DataPtr data)
{
	return (*loadFileFunc_)(fileData,data);
}

template<class T>
inline void LoadSectionBase<T>::Init()
{
	loadFileFunc_ = std::make_unique<LoadFunc::LoadFile<T>>(
		std::bind_front(&LoadSectionBase<T>::GetHitObjString, this),
		std::bind_front(&LoadSectionBase<T>::SetData, this));
}

template<class T>
inline std::optional<std::string> LoadSectionBase<T>::GetHitObjString(const std::string& fileData)
{
	return LoadFunc::GetDefStringData()(fileData, title_);
}

template<class T>
inline void LoadSectionBase<T>::SetData(const std::string& fileData, DataPtr dataPtr)
{
	auto data = std::stringstream(fileData);
	std::string buf;
	while (std::getline(data, buf))
	{
		for (auto& func : setDataFuncVec_)
		{
			if (func(*dataPtr, buf))
			{
				break;
			}
		}
	}
}

