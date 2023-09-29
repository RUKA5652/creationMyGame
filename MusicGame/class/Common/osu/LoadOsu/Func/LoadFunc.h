#pragma once
#include <string>
#include<optional>
#include<functional>

namespace LoadFunc
{
	struct GetDefStringData
	{
		std::optional<std::string> operator()(const std::string& fileData,const std::string& hed)
		{
			auto hitPos = fileData.find(hed.c_str());
			//������Ȃ�����
			if (hitPos == fileData.npos)
			{
				return std::nullopt;
			}
			hitPos += hed.size();
			auto endPos = fileData.find("\n[", hitPos);
			auto data = fileData.substr(hitPos, endPos - hitPos);
			return data;
		}

	};

	template<class T>
	struct LoadFile
	{
		using Data = T*;
		using GetStringData = std::function<std::optional<std::string>(const std::string&)>;
		using SetData = std::function<void(const std::string&, Data data)>;

		LoadFile(GetStringData&& getStringDataFunc, SetData&&  setDataFunc)
		{
			getStringData = (getStringDataFunc);
			setData =	(setDataFunc);
		}

		//�R���X�g���N�^�Ŏ󂯎�����֐��ŏ���
		bool operator()(const std::string& fileData, Data data)
		{
			//ptr��null�`�F�b�N
			if (!data)
			{
				return false;
			}
			data->clear();
			auto stringData = getStringData(fileData);
			if (!stringData.has_value())
			{
				return false;
			}
			setData(stringData.value(),data);
			return true;
		}
	private:
		GetStringData getStringData;
		SetData setData;
	};

}

