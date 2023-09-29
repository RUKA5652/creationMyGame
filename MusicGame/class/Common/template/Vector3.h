#pragma once
#include"Vector2.h"
#include<concepts>
#include<DxLib.h>

#define requiresVec3  std::integral<T> || std::floating_point<T> || std::signed_integral<T> || std::unsigned_integral<T>

template<class T = double> requires requiresVec3
class Vector3Tmple
{
public:
	Vector3Tmple();
	Vector3Tmple(T x, T y, T z);
	Vector3Tmple(const VECTOR& vec);
	T x,y,z;

	inline DxLib::VECTOR operator()() const;

	inline static Vector3Tmple<T> GetForward();

	inline static Vector3Tmple<T> GetRight();

	inline static Vector3Tmple<T> GetUp();

	inline T Magnitude()const;//Ç±ÇÃíÜÇ≈ÇÕílÇÃïœçXÇÇµÇ»Ç¢ÇÊ

	inline void Normalize();

	//äOêœ

	inline Vector3Tmple<T> Cross(const Vector3Tmple<T>& n) const;

	inline Vector3Tmple<T> operator=(const VECTOR& n);

	template<class F> requiresVec2
	inline Vector3Tmple<T> operator=(const Vector2Tmple<F>& n);

	inline Vector3Tmple<T> operator+(const Vector3Tmple<T>& n)const;

	inline Vector3Tmple<T> operator+(const VECTOR& n)const;

	inline void operator+=(const VECTOR& n)const;

	inline Vector3Tmple<T> operator-(const VECTOR& n)const;

	template<class F> requires requiresVec3
	inline Vector3Tmple<T> operator*(const F& n)const;

	inline Vector3Tmple<T> operator*(const MATRIX& matrix)const;
	inline Vector3Tmple<T> operator*(const VECTOR& n)const;

	inline void operator+=(const Vector3Tmple<T>& n);

	inline bool operator!=(const Vector3Tmple<T>& n);

};




using Vector3 = Vector3Tmple<double>;

#include"Vector3/Vector3.h"

