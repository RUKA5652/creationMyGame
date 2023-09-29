#pragma once
#include"../../../Base/BaseData.h"
#include"../../../template/Vector3.h"
#include"../../../template/Vector2.h"
#include"../../HitObj.h"
#include"../../LoadData.h"
#include <deque>

namespace Note
{
	using Handle = int;
	using Size = Vector2Tmple<int>;
	using Pos = Vector2Tmple<int>;
	struct NormalData
	{
		NormalData(const Beat::Time& geneTime, const Beat::Time& endTime);
		Pos pos;
		int lane;
		Beat::UpdateTime generatTime;
		Beat::Sound::Type sound;
		Beat::Time endTime;
	};

	struct HoldData
	{
		HoldData(const Beat::Time& geneTime);
		Pos sPos;
		Pos ePos;
		int lane;
		Beat::UpdateTime generatTime;
		Beat::Sound::Type sound;
		Beat::Time holdTime;
		Beat::Time sTime;
		Beat::Time eTime;
	};

	using Normals = std::vector<std::deque<NormalData>>;
	using Holds = std::vector<std::deque<HoldData>>;

	struct NotesData:
		public BaseData
	{
		NotesData(int size)
		{
			normalsData.resize(size);
			holdsData.resize(size);
		}

		bool empty()
		{
			for (auto& datas : normalsData)
			{
				if (datas.size())
				{
					return false;
				}
			}
			for (auto& datas : holdsData)
			{
				if (datas.size())
				{
					return false;
				}
			}
			return true;
		}

		Normals normalsData;
		Holds holdsData;
	};

	using NotesDataPtr = std::shared_ptr<NotesData>;
	using NotesDataConstPtr = std::shared_ptr<const NotesData>;
}


