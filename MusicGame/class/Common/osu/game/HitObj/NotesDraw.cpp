#include "NotesDraw.h"
#include"NoteData.h"
#include"../NoteSizeRatio.h"
#include<DxLib.h>
#include "../../../../../_debug/_DebugConOut.h"
#include"../../Skin/Image/SkinImage.h"
#include"../../../Base/GameCore.h"
#include "../GameDrawIndex.h"

NotesDraw::NotesDraw(LaneDivisionConstPtr division, Note::NotesDataConstPtr noteData, NoteSizeRatioConstPtr noteRatio, Beat::HitsDataConstPtr hitdata)
{
	noteRatio_ = std::move(noteRatio);
	noteData_ = std::move(noteData);
	hitdata_ = std::move(hitdata);
    CreateImage(division);

}

NotesDraw::~NotesDraw()
{

}

void NotesDraw::Draw()
{
	NormalDraw(noteData_->normalsData);
	HoldDraw(noteData_->holdsData);
}

void NotesDraw::CreateImage(LaneDivisionConstPtr& division)
{
    normalImage_.resize(division->divisionData);
    normalImage_.shrink_to_fit();
    holdImage_.resize(division->divisionData);
    holdImage_.shrink_to_fit();

    auto center = division->divisionData / 2;
    for (int i = 0; i < division->divisionData; i++)
    {
        normalImage_[i] = (i - i / center) % 2 == 0 ? lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::Notes1) : 
                                                       lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::Notes2);

        holdImage_[i] = (i - i / center) % 2 == 0 ? lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::HoldLane1) : 
                                                     lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::HoldLane2);
    }
    if (division->divisionData >= 5 && division->divisionData%2 == 1)
    {
        std::shift_right(std::next(normalImage_.begin(), center), normalImage_.end(), 1);
        normalImage_[center] = lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::Notes5);

        std::shift_right(std::next(holdImage_.begin(), center), holdImage_.end(), 1);
        holdImage_[center] = lpSkinImagePtr.GetFirstImage(Beat::SkinImageType::HoldLane5);
    }


}

void NotesDraw::SetFunc(GameCore* gameCore)
{
	gameCore->SetDraw(static_cast<int>(GameDrawIndex::Notes), shared_from_this());
}

void NotesDraw::NormalDraw(Note::Normals normalsData) const
{
	for (auto& laneNotes : normalsData)
	{
		for (auto& note : laneNotes)
		{
			auto pos2 = note.pos + noteRatio_->GetSize();
			DrawExtendGraph(note.pos.x, note.pos.y, pos2.x, pos2.y, normalImage_[note.lane], true);
		}
	}
}

void NotesDraw::HoldDraw(Note::Holds holdsData) const
{
    // 外側の for ループ: ホールド音符の情報を取り出して処理
    for (int i = 0; i < holdsData.size(); i++)
    {
        // ホールド音符の情報を取り出し
        auto& laneNotes = holdsData[i];

        // 現在処理しているホールド音符の演奏結果を取り出し
        const auto& hitData = hitdata_->hitData_[i].holdsResult;

        // 内側の for ループ: 各ホールド音符に対して処理
        for (auto& note : laneNotes)
        {
            // ホールド音符が "BAD" の結果として評価された場合は、
            // 画像の描画にアルファブレンドを使用
            if (hitData && hitData.value().sTime == note.sTime &&
                hitData.value().result == Beat::Type::BAD)
            {
                SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
            }

            // ホールド音符間のハンドル画像を描画
            auto pos2 = note.ePos + noteRatio_->GetSize();
            DrawExtendGraph(note.sPos.x, note.sPos.y, pos2.x, pos2.y, holdImage_[note.lane], true);

            // ホールド音符のハンドル画像を描画
            DrawExtendGraph(note.ePos.x, note.ePos.y, pos2.x, pos2.y, normalImage_[note.lane], true);

            // ホールド音符のハンドル画像を赤色で強調表示
            pos2 = note.sPos + noteRatio_->GetSize();
            SetDrawAddColor(255, 00, 00);
            DrawExtendGraph(note.sPos.x, note.sPos.y, pos2.x, pos2.y, normalImage_[note.lane], true);

            // 描画モードや色を元に戻し、次の処理へ備える
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
            SetDrawAddColor(0, 0, 0);
        }
    }
}
