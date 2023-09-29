#pragma once
#include<string>
#include"../../../MetaData.h"
#include"../CreateNumString.h"

/// <summary>
/// HitObjî•ñŠi”[ŠÖ”
/// ƒtƒ@ƒCƒ‹“Ç‚İ‚İ—p
/// </summary>
namespace MetadataLoadFunc
{
	struct CreateData
	{
		const std::string hedData;
		CreateData(const std::string hed):hedData(hed){};
		auto Getdata(const std::string& data)
		{
			 return CreateNumString()(data, hedData);
		}
	};

	struct Artist:
		public CreateData
	{
		Artist() :CreateData("Artist:"){};
		bool operator()(Beat::MetaData& general, const std::string& data)
		{
			auto result = Getdata(data);
			if (!result)
			{
				return false;
			}
			general.Artist = result.value();

			return true;
		}
	};

	struct Title :
		public CreateData
	{
		Title() :CreateData("Title:") {};
		bool operator()(Beat::MetaData& general, const std::string& data)
		{
			auto result = Getdata(data);
			if (!result)
			{
				return false;
			}
			general.Title = result.value();
			return true;
		}
	};

	struct Version :
		public CreateData
	{
		Version() :CreateData("Version:") {};
		bool operator()(Beat::MetaData& general, const std::string& data)
		{
			auto result = Getdata(data);
			if (!result)
			{
				return false;
			}
			general.Version = result.value();
			return true;
		}
	};

	struct Creator :
		public CreateData
	{
		Creator() :CreateData("Creator:") {};
		bool operator()(Beat::MetaData& general, const std::string& data)
		{
			auto result = Getdata(data);
			if (!result)
			{
				return false;
			}
			general.Creator = result.value();
			return true;
		}
	};

}
