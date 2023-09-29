#pragma once
#include<concepts>
//using Vector2 = Vector2Tmple<int>;


#define requiresVec2  requires std::integral<T> || std::floating_point<T> || std::signed_integral<T> || std::unsigned_integral<T>
//テンプレートクラス
 //決まり文句　template <class T> class
template <class T = int> requiresVec2
class Vector2Tmple
{
public:



	Vector2Tmple();
	constexpr Vector2Tmple(T x, T y);
	template<class F> requires std::integral<F> || std::floating_point<F> || std::signed_integral<F> || std::unsigned_integral<F>
	Vector2Tmple(F x, F y);
	constexpr ~Vector2Tmple();
	T x;
	T y;

	//2項演算子
	inline Vector2Tmple operator+(const Vector2Tmple& num);
	template<class F>
	inline Vector2Tmple operator+(const Vector2Tmple<F> num);

	inline Vector2Tmple operator-(const Vector2Tmple& num);
	template<class F> requires std::integral<F> || std::floating_point<F> || std::signed_integral<F> || std::unsigned_integral<F>
	inline Vector2Tmple operator-(const F num);
	template<class F>
	inline Vector2Tmple operator-(const Vector2Tmple<F> num);

	inline Vector2Tmple operator*(const Vector2Tmple& num);
	template<class F>
	inline Vector2Tmple operator*(const Vector2Tmple<F> num);
	template<class F> requires std::integral<F> || std::floating_point<F> || std::signed_integral<F> || std::unsigned_integral<F>
	inline Vector2Tmple operator*(const F num);

	inline Vector2Tmple operator/(const Vector2Tmple& num);
	template<class F>
	inline Vector2Tmple operator/(const Vector2Tmple<F> num);
	template<class F> requires std::integral<F> || std::floating_point<F> || std::signed_integral<F> || std::unsigned_integral<F>
	inline Vector2Tmple operator/(const F num);

	inline Vector2Tmple operator%(const Vector2Tmple& num);

	//代入演算子
	inline Vector2Tmple& operator=(const Vector2Tmple& num);		//代入だから参照渡しでもおｋ
	template<class F>
	inline Vector2Tmple<T> operator=(const Vector2Tmple<F>& num);
	//添え字演算子
	inline int& operator[](const int& cnt);

	//単項演算子
	inline Vector2Tmple& operator+=(const Vector2Tmple& num);
	template<class F>
	inline Vector2Tmple& operator+=(const Vector2Tmple<F>& num);
	template<class F> requires std::integral<F> || std::floating_point<F> || std::signed_integral<F> || std::unsigned_integral<F>
	inline Vector2Tmple & operator+=(const F & num);
	inline Vector2Tmple& operator-=(const Vector2Tmple& num);
	template<class F> requires std::integral<F> || std::floating_point<F> || std::signed_integral<F> || std::unsigned_integral<F>
	inline Vector2Tmple & operator-=(const F & num);
	template<class F>
	inline Vector2Tmple& operator-=(const Vector2Tmple<F>& num);
	inline Vector2Tmple& operator*=(const Vector2Tmple& num);
	template<class F> requires std::integral<F> || std::floating_point<F> || std::signed_integral<F> || std::unsigned_integral<F>
	inline Vector2Tmple & operator/=(const F & num);
	inline Vector2Tmple& operator/=(const Vector2Tmple& num);

	inline Vector2Tmple& operator%=(const Vector2Tmple& num);

	inline Vector2Tmple operator+()const; //おしりのconst は関数内でのthisのメンバーの変更を縛る 

	inline Vector2Tmple operator-()const;
	//cast
	template<class F>
	inline Vector2Tmple<F> cast(void) const;

	//比較演算子
	inline bool operator<(const Vector2Tmple& num)const;
	inline bool operator<=(const Vector2Tmple& num)const;
	inline bool operator>(const Vector2Tmple& num)const;
	inline bool operator>=(const Vector2Tmple& num)const;
	inline bool operator==(const Vector2Tmple& num)const;
	inline bool operator!=(const Vector2Tmple& num)const;


	//ベクトルの大きさを返す
	double Magnitude()const;//この中では値の変更をしないよ
	//ベクトルの2乗を返す
	double SQ_Magnitude()const;
	//ベクトルの大きさを返す
	template<class F>
	F Magnitude()const;//この中では値の変更をしないよ
	//ベクトルの2乗を返す
	template<class F>
	F SQ_Magnitude()const;

	//正規化する
	void Normalize(); 
	Vector2Tmple Normalized();
	//角度を返す
	float Theta();
	//90度回転
	void Rotate90();
	//符号を返す
	Vector2Tmple<int> Sige();

	Vector2Tmple abs();

	Vector2Tmple round();

	bool CheckNon();

private:
};

template<class T> //宣言外なので再度宣言して教えてあげないといけない
inline Vector2Tmple<T> operator+(const Vector2Tmple<T>& me, const  T& num);
template<class T>
inline Vector2Tmple<T> operator-(const Vector2Tmple<T>& me, const  T& num);
template<class T>
inline Vector2Tmple<T> operator-(const Vector2Tmple<T>& me, const  Vector2Tmple<T>& num);
template<class T> 
inline Vector2Tmple<T> operator*(const Vector2Tmple<T>& me, const  T& num);
template<class T> 
inline Vector2Tmple<T> operator/(const Vector2Tmple<T>& me, const  T& num);
template<class T>
inline Vector2Tmple<T> operator*(const T& num, const Vector2Tmple<T>& me);

/// <summary>
/// 内積を返す
/// </summary>
/// <param name="va">左項</param>
/// <param name="vb">右項</param>
/// <returns>内積値</returns>
template<class T>
inline extern float Dot(const Vector2Tmple<T>& va, const Vector2Tmple<T>& vb);

/// <summary>
/// 外積を返す
/// </summary>
/// <param name="va">左項</param>
/// <param name="vb">右項</param>
/// <returns>外積値</returns>
template<class T>
inline extern float Cross(const Vector2Tmple<T>& va, const Vector2Tmple<T>& vb);
template<class T>
inline extern double Angle(const Vector2Tmple<T>& va, const Vector2Tmple<T>& vb);



using Vector2Flt = Vector2Tmple<float>;

using Vector2Dbl = Vector2Tmple<double>;

using Vector2 = Vector2Tmple<int>;

using Position2 = Vector2Tmple<int>;

#include"Vector2/Vector2.h"

