#pragma once
#include<vector>
#include<string>
#include"../Common/template/Vector2.h"
#include <map>

#define lpImageMng  ImageMng::GetInstance()

using VecInt = std::vector<int>;


class ImageMng
{
public:
	class BuffMng
	{
	public:
		template<class T>
		void CreateBuf(int cnt = 1);
		template<class T>
		int GetHandle();
		template<class T>
		void* GetBuf();
	private:
		BuffMng() {};
		BuffMng(BuffMng&) = delete;
		~BuffMng() {};
		std::map<size_t, int> constantBuffHandle_;
		friend ImageMng;
	};


	static  ImageMng& GetInstance(void)
	{
		static ImageMng s_Instance;
		return s_Instance;
	}
	const VecInt& GetID(const std::string& key /*ファイル名*/); //グラフィックハンドルを返す
	const VecInt& GetID(const std::string& f_name, const std::string& key /*ファイル名*/); //グラフィックハンドルを返す
	const VecInt& GetID(const std::string& f_name, const std::string& key /*ファイル名*/, const Vector2& divSize, const Vector2& divCnt);//グラフィックハンドルを返す 分割されてる場合もあるので
	const VecInt& GetID(const std::string& f_name, const std::string& key /*ファイル名*/, const Vector2&& divSize, const Vector2&& divCnt);
	const bool DeleteID(const std::string& key /*ファイル名*/); //グラフィックハンドルを消す
	const std::pair<Vector2Flt, Vector2Flt> GetUV(int imagehndle);

	const int& LoadPSID(const std::string& f_name, const std::string& key /*ファイル名*/); //
	const int GetPSID(const std::string& key /*ファイル名*/); //

	
	BuffMng& GetBuffMng();
private:
	ImageMng();
	~ImageMng() {};
	BuffMng buffMng_;

	std::map<std::string, VecInt> imageMap_;
	std::map<std::string, int> shaderMap_;
	std::map<int,std::pair<Vector2Flt, Vector2Flt>> handleUV_;
};

template<class T>
inline void ImageMng::BuffMng::CreateBuf(int cnt)
{
	auto [buf, flag] = constantBuffHandle_.try_emplace(typeid(T).hash_code());
	if (flag)
	{
		buf->second = CreateShaderConstantBuffer(sizeof(T) * 4 * cnt);
	}
}

template<class T>
inline int ImageMng::BuffMng::GetHandle()
{
	auto hash = typeid(T).hash_code();
	if (constantBuffHandle_.count(hash))
	{
		return constantBuffHandle_[hash];
	}
	return -1;
}

template<class T>
inline void* ImageMng::BuffMng::GetBuf()
{
	auto hash = typeid(T).hash_code();
	if (constantBuffHandle_.count(hash))
	{
		return GetBufferShaderConstantBuffer(constantBuffHandle_[hash]);
	}
	return nullptr;
}


