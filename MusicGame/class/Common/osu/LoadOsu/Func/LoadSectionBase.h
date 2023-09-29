#pragma once
#include<string>
#include <optional>
#include<memory>
#include<functional>
#include"LoadFunc.h"
#include"../../LoadData.h"

namespace Beat
{
	class LoadModule
	{
	public:
		virtual ~LoadModule() {};
		virtual bool LoadFile(const std::string& fileData, Beat::LoadDataPtr data) { return true; };
	};
}

/// <summary>
/// �Z�N�V�������[�h���N���X
/// </summary>
/// <typeparam name="T">�t�@�C�����</typeparam>
template<class T>
class LoadSectionBase :
	public Beat::LoadModule
{
public:
	using DataPtr = T*;

	LoadSectionBase(std::string title);
	~LoadSectionBase();

	/// <summary>
	/// �t�@�C���ǂݍ���
	/// </summary>
	/// <param name="fileData">�t�@�C���p�X</param>
	/// <returns>���ۃt���O</returns>
	bool LoadFile(const std::string& fileData, DataPtr data);
protected:

	using setDataFunc = std::function<bool(T&, const std::string&)>;

	//�ǂݍ��݃f�[�^Title
	const std::string title_;

	//�ǂݍ��݃f�[�^�쐬�֐��z�� 
	std::vector<setDataFunc> setDataFuncVec_;

	//���[�h�֐�
	std::unique_ptr<LoadFunc::LoadFile<T>> loadFileFunc_;

	void Init();
	//�t�@�C�����𔲂��o��
	std::optional<std::string> GetHitObjString(const std::string& fileData);

	virtual void SetData(const std::string& fileData, DataPtr dataPtr) ;


};

#include"LoadSectionBase/LoadSectionBase.h"


