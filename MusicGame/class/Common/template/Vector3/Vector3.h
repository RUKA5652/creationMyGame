#pragma once
#include"../Vector3.h"

template<class T>  requires requiresVec3
Vector3Tmple<T>::Vector3Tmple()
{
	x = 0;
	y = 0;
	z = 0;
}

template<class T>  requires requiresVec3
inline Vector3Tmple<T>::Vector3Tmple(T x, T y, T z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

template<class T> requires requiresVec3
inline Vector3Tmple<T>::Vector3Tmple(const VECTOR& vec)
{
	x = vec.x;
	y = vec.y;
	z = vec.z;
}

template<class T>  requires requiresVec3
inline DxLib::VECTOR Vector3Tmple<T>::operator()() const
{
	return {static_cast<float>(x),static_cast<float>(y),static_cast<float>(z) };
}

template<class T>  requires requiresVec3
inline Vector3Tmple<T> Vector3Tmple<T>::GetForward()
{
	return { 0,0,1 };
}

template<class T>  requires requiresVec3
inline Vector3Tmple<T> Vector3Tmple<T>::GetRight()
{
	return { 1,0,0 };
}

template<class T>  requires requiresVec3
inline Vector3Tmple<T> Vector3Tmple<T>::GetUp()
{
	return {0,1,0};
}

template<class T>  requires requiresVec3
inline T Vector3Tmple<T>::Magnitude() const
{
	return static_cast<T>(hypot(x, y));
}

template<class T>  requires requiresVec3
inline void Vector3Tmple<T>::Normalize()
{
	auto mag = Magnitude();
	if (mag == 0.0f) { return; };
	x = x / mag;
	y = y / mag;
}

template<class T> requires requiresVec3
inline Vector3Tmple<T> Vector3Tmple<T>::Cross(const Vector3Tmple<T>& n) const
{
	Vector3Tmple<T> Result;
	Result.x = y * n.z - z * n.y;
	Result.y = z * n.x - x * n.z;
	Result.z = x * n.y - y * n.x;
	return Result;
}

template<class T>  requires requiresVec3
inline Vector3Tmple<T> Vector3Tmple<T>::operator=(const VECTOR& n)
{
	this->x = n.x;
	this->y = n.y;
	this->z = n.z;
	return *this;
}

template<class T>  requires requiresVec3
inline Vector3Tmple<T> Vector3Tmple<T>::operator+(const Vector3Tmple<T>& n)const
{
	Vector3Tmple<T> result = *this;
	result.x += n.x;
	result.y += n.y;
	result.z += n.z;
	return result;
}

template<class T> requires requiresVec3
inline Vector3Tmple<T> Vector3Tmple<T>::operator+(const VECTOR& n) const
{
	Vector3Tmple<T> result = *this;
	result.x += n.x;
	result.y += n.y;
	result.z += n.z;
	return result;
}

template<class T> requires requiresVec3
inline void Vector3Tmple<T>::operator+=(const VECTOR& n) const
{
	this.x += n.x;
	this.y += n.y;
	this.z += n.z;
}

template<class T>  requires requiresVec3
inline Vector3Tmple<T> Vector3Tmple<T>::operator-(const VECTOR& n) const
{
	Vector3Tmple<T> result = *this;
	result.x -= n.x;
	result.y -= n.y;
	result.z -= n.z;
	return result;
}

template<class T> requires requiresVec3
inline void Vector3Tmple<T>::operator+=(const Vector3Tmple<T>& n)
{
	x += n.x;
	y += n.y;
	z += n.z;
}

template<class T> requires requiresVec3
inline bool Vector3Tmple<T>::operator!=(const Vector3Tmple<T>& n) 
{
	bool result = true;
	result &= x == n.x;
	result &= y == n.y;
	result &= z == n.z;
	return !result;
}

template<class T>  requires requiresVec3
inline Vector3Tmple<T> Vector3Tmple<T>::operator*(const MATRIX& matrix)const
{
	Vector3Tmple<T> Result;
	Result.x = x * matrix.m[0][0] + y * matrix.m[1][0] + z * matrix.m[2][0] + matrix.m[3][0];
	Result.y = x * matrix.m[0][1] + y * matrix.m[1][1] + z * matrix.m[2][1] + matrix.m[3][1];
	Result.z = x * matrix.m[0][2] + y * matrix.m[1][2] + z * matrix.m[2][2] + matrix.m[3][2];
	return Result;
}

template<class T> requires requiresVec3
inline Vector3Tmple<T> Vector3Tmple<T>::operator*(const VECTOR& n) const
{
	Vector3Tmple<T> result;
	result.x = this->x * n.x;
	result.y = this->y * n.y;
	result.z = this->z * n.z;
	return result;
}

template<class T> requires requiresVec3
template<class F> requiresVec2
inline Vector3Tmple<T> Vector3Tmple<T>::operator=(const Vector2Tmple<F>& n)
{
	this->x = n.x;
	this->y = n.y;
	return *this;
}

template<class T> requires requiresVec3
template<class F> requires requiresVec3
inline Vector3Tmple<T> Vector3Tmple<T>::operator*(const F& n)const
{
	return { x * n,y * n ,z * n };
}






