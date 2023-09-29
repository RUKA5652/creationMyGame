#pragma once
#include<bitset>
#include<vector>
#include<array>
#include<map>
#include <optional>
#include <deque>
#include<memory>
#include"../../Base/BaseData.h"
#include "../HitObj.h"
#include"HitObj/NoteData.h"
#include"../Skin/Image/SkinImageData.h"

namespace Beat
{
	inline namespace HitResult
	{
		enum class Type
		{
			NON,
			JUST = static_cast<int>(SkinImageType::JUST),
			GREAT = static_cast<int>(SkinImageType::Great),
			GOOD = static_cast<int>(SkinImageType::Good),
			BAD = static_cast<int>(SkinImageType::Bad),
			MAX,
		};
		
		struct NormalResult
		{
			Beat::Time time;
			Type result;
		};
		struct HoldResult
		{
			Beat::Time sTime;
			Beat::Time eTime;
			Type result;
			Sound::Type sound;
			Time holdTime;
			Time checkStart;
			Time checkEnd;
			Time tupPoint;
			bool endFlag;
		};
	//	using NormalResult = std::pair<Note::NormalData*, HitResult::Type>;
	//	using HoldResult = std::pair<Note::HoldData*, HitResult::Type>;
	};

	using NormalHitsData = std::deque<NormalResult>;

	using HoldHitData = std::optional<HoldResult>;


	struct Hit
	{
		void clear();
		NormalHitsData normalsResult;
		HoldHitData holdsResult;
	};

	constexpr int maxScore = 1000000;

	struct HitsData
		:public BaseData
	{
		int combo = 0;
		double score = 0.0;
		std::map<HitResult::Type, int> result;
		HitsData(const int size);
		std::vector<Hit> hitData_;
	};

	using HitsDataPtr = std::shared_ptr<HitsData>;
	using HitsDataConstPtr = std::shared_ptr<const HitsData>;
	using CheckHitTime = std::map<Beat::HitResult::Type, Beat::Time>;
}

