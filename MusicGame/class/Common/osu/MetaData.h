#pragma once
#include<string>

/// <summary>
/// �f�[�^��`
/// OSU�f�[�^ MetaData
/// </summary>
namespace Beat
{
	//���ʃ��^���f�[�^
	struct MetaData
	{
		using TitleData = std::string;
		using CreatorData = std::string;
		//�Ȗ�
		TitleData Title;
		//�Ȃ̍��
		CreatorData Artist;
		//���ʍ쐬�o�[�W����
		std::string Version;
		//���ʍ��
		CreatorData Creator;
		//�\���̃��Z�b�g
		void clear()
		{
			Title.clear();
			Artist.clear();
			Version.clear();
			Creator.clear();
		}
		auto operator<=>(const MetaData&) const = default;

	};
	using MetaDataPtr = MetaData*;

}

