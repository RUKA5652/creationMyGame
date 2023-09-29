#pragma once
#include"../Vector2.h"
#include<algorithm>
#include <cassert>
#include<cmath>

template<class T>  requiresVec2
inline Vector2Tmple<T>::Vector2Tmple()
{
		x = 0;
		y = 0;
}

template<class T>  requiresVec2
constexpr inline Vector2Tmple<T>::Vector2Tmple(T x, T y)/*:x(x),y(y)　やらないけどこれでも可*/
{
		Vector2Tmple::x = x;
		Vector2Tmple::y = y;
	//-------これでも行けるね------------
	/*this->x = x;
	this->y = y;*/
	//------------------
}

template<class T> requiresVec2
template<class F>requires std::integral<F> || std::floating_point<F> || std::signed_integral<F> || std::unsigned_integral<F>
inline Vector2Tmple<T>::Vector2Tmple(F x, F y)
{
	Vector2Tmple::x = static_cast<T>(x);
	Vector2Tmple::y = static_cast<T>(y);
}

template<class T>  requiresVec2
constexpr inline Vector2Tmple<T>::~Vector2Tmple()
{

}

template<class T>  requiresVec2
inline Vector2Tmple<T> Vector2Tmple<T>::operator+(const Vector2Tmple<T>& num)
{
		return  {this->x + num.x, this->y + num.y };
}

template<class T>  requiresVec2
inline Vector2Tmple<T> Vector2Tmple<T>::operator-(const  Vector2Tmple<T>& num)
{
		return { this->x - num.x, this->y - num.y };
}

template<class T> requiresVec2
inline Vector2Tmple<T> Vector2Tmple<T>::operator*(const  Vector2Tmple<T>& num)
{
		return { this->x * num.x, this->y * num.y };
}

template<class T> requiresVec2
inline Vector2Tmple<T> Vector2Tmple<T>::operator/(const  Vector2Tmple<T>& num)
{
		if (num.x == 0)
		{
				this->x = 0;
		}

		if (num.y == 0)
		{
				this->y = 0;
		}


		return { this->x / num.x, this->y / num.y };
}

template<class T> requiresVec2
inline Vector2Tmple<T> Vector2Tmple<T>::operator%(const  Vector2Tmple<T>& num)
{

		//if (num.x == 0)
		//{
		//		this->x = 0;
		//}
	
		//if (num.y == 0)
		//{
		//		this->y = 0;
		//}
	

		return { this->x % num.x, this->y % num.y };
}

template<class T> requiresVec2
inline Vector2Tmple<T>& Vector2Tmple<T>::operator=(const  Vector2Tmple<T>& num)
{
		this->x = num.x;
		this->y = num.y;

		return   *this; //thisはポインターだよ　実体で渡したいよね*をつけよう
}

template<class T> requiresVec2
inline int& Vector2Tmple<T>::operator[](const int& cnt)
{
		switch (cnt)
		{
		//case 0:
		//		return x;
				//break;
		case 1:
				return y;
				//break;
		default:
				return x;
				//break;
		}
}

template<class T> requiresVec2
inline Vector2Tmple<T>& Vector2Tmple<T>::operator+=(const  Vector2Tmple<T>& num)
{
		this->x += num.x;
		this->y += num.y;
		return   *this; //thisはポインターだよ　実体で渡したいよね*をつけよう
}
template<class T> requiresVec2
template<class F>
inline Vector2Tmple<T>& Vector2Tmple<T>::operator+=(const  Vector2Tmple<F>& num)
{
	auto num_ = num.cast<T>();
	this->x += num_.x;
	this->y += num_.y;
	return   *this; //thisはポインターだよ　実体で渡したいよね*をつけよう
}

template<class T> requiresVec2
template<class F> requires std::integral<F> || std::floating_point<F> || std::signed_integral<F> || std::unsigned_integral<F>
inline Vector2Tmple<T>& Vector2Tmple<T>::operator+=(const F& num)
{
	auto num_ = static_cast<T>(num);
	this->x += num_;
	this->y += num_;
	return *this;
}

template<class T> requiresVec2
template<class F> requires std::integral<F> || std::floating_point<F> || std::signed_integral<F> || std::unsigned_integral<F>
inline Vector2Tmple<T>& Vector2Tmple<T>::operator-=(const F& num)
{
	auto num_ = static_cast<T>(num);
	this->x -= num_;
	this->y -= num_;
	return *this;
}
template<class T> requiresVec2
template<class F>
inline Vector2Tmple<T>& Vector2Tmple<T>::operator-=(const  Vector2Tmple<F>& num)
{
	auto num_ = num.cast<T>();
	this->x -= num_.x;
	this->y -= num_.y;
	return   *this; //thisはポインターだよ　実体で渡したいよね*をつけよう
}

template<class T> requiresVec2
template<class F> requires std::integral<F> || std::floating_point<F> || std::signed_integral<F> || std::unsigned_integral<F>
inline Vector2Tmple<T>& Vector2Tmple<T>::operator/=(const F& num)
{
	auto num_ = static_cast<T>(num);
	this->x /= num_;
	this->y /= num_;
	return *this;
}


template<class T> requiresVec2
inline Vector2Tmple<T>& Vector2Tmple<T>::operator-=(const  Vector2Tmple<T>& num)
{
		this->x -= num.x;
		this->y -= num.y;
		return   *this; //thisはポインターだよ　実体で渡したいよね*をつけよう
}

template<class T> requiresVec2
inline Vector2Tmple<T>& Vector2Tmple<T>::operator*=(const  Vector2Tmple<T>& num)
{
		this->x *= num.x;
		this->y *= num.y;
		return   *this; //thisはポインターだよ　実体で渡したいよね*をつけよう
}

template<class T> requiresVec2
inline Vector2Tmple<T>& Vector2Tmple<T>::operator/=(const  Vector2Tmple<T>& num)
{
		if (num.x == 0)
		{
				this->x = 0;
		}
		else
		{
				this->x /= num.x;
		}

		if (num.y == 0)
		{
				this->y = 0;
		}
		else
		{
				this->y /= num.y;
		}
		return   *this; //thisはポインターだよ　実体で渡したいよね*をつけよう
}

template<class T> requiresVec2
inline Vector2Tmple<T>& Vector2Tmple<T>::operator%=(const  Vector2Tmple<T>& num)
{
		if (num.x == 0)
		{
				this->x = 0;
		}
		else
		{
				this->x %= num.x;
		}

		if (num.y == 0)
		{
				this->y = 0;
		}
		else
		{
				this->y %= num.y;
		}
		return   *this; //thisはポインターだよ　実体で渡したいよね*をつけよう
}

template<class T> requiresVec2
inline Vector2Tmple<T> Vector2Tmple<T>::operator+() const
{
		return  *this; //thisはポインターだよ　実体で渡したいよね*をつけよう
}

template<class T> requiresVec2
inline Vector2Tmple<T> Vector2Tmple<T>::operator-() const
{
		return { -this->x,-this->y };
}

template<class T> requiresVec2
inline bool Vector2Tmple<T>::operator<(const  Vector2Tmple<T>& num)const
{
	double a = this->SQ_Magnitude();
	double b = num.SQ_Magnitude();
	if (a != b)
	{
		return a < b;
	}
	else
	{
		if (this->x != num.x)
		{
			return this->x < num.x;
		}
		if (this->y != num.y)
		{
			return this->y < num.y;
		}


	}
	return false;
}

template<class T> requiresVec2
inline bool Vector2Tmple<T>::operator<=(const  Vector2Tmple<T>& num) const
{
		//if (!this->x <= num.x)
		//{
		//		return false;
		//}
		//if (!this->y <= num.y)
		//{
		//		return false;
		//}
		//return true;
		return (this->x <= num.x && this->y <= num.y);
}

template<class T> requiresVec2
inline bool Vector2Tmple<T>::operator>(const  Vector2Tmple<T>& num)const
{
	/*	if (!this->x > num.x)
		{
				return false;
		}
		if (!this->y > num.y)
		{
				return false;
		}
		return true;*/
		return (this->x > num.x && this->y > num.y);
}

template<class T> requiresVec2
inline bool Vector2Tmple<T>::operator>=(const  Vector2Tmple<T>& num)const
{
		//if (!this->x >= num.x)
		//{
		//		return false;
		//}
		//if (!this->y >= num.y)
		//{
		//		return false;
		//}
		//return true;
		return (this->x >= num.x && this->y >= num.y);
}

template<class T> requiresVec2
inline bool Vector2Tmple<T>::operator==(const  Vector2Tmple<T>& num)const
{
	/*	if (!this->x == num.x)
		{
				return false;
		}
		if (!this->y == num.y)
		{
				return false;
		}
		return true;*/

		return (this->x == num.x && this->y == num.y);
}

template<class T> requiresVec2
inline bool Vector2Tmple<T>::operator!=(const  Vector2Tmple<T>& num) const
{
		//if (!this->x != num.x)
		//{
		//		return false;
		//}
		//if (!this->y != num.y)
		//{
		//		return false;
		//}
		//return true;
		return !(this->x == num.x && this->y == num.y);;

}

template<class T> requiresVec2
inline double Vector2Tmple<T>::Magnitude() const
{
	return static_cast<float>(hypot(x, y));
}

template<class T> requiresVec2
template<class F>
inline F Vector2Tmple<T>::Magnitude() const
{
	return static_cast<F>(std::hypot(static_cast<double>(x), static_cast<double>(y)));
}

template<class T> requiresVec2
inline double Vector2Tmple<T>::SQ_Magnitude() const
{
	return	x * x + y * y;
}

template<class T> requiresVec2
template<class F>
inline F Vector2Tmple<T>::SQ_Magnitude() const
{
	return static_cast<F>(x * x + y * y);
}


template<class T> requiresVec2
inline void Vector2Tmple<T>::Normalize()
{
	auto mag = Magnitude();
	if (mag == 0.0f) { return;};
	x = x / mag;
	y = y / mag;
}

template<class T> requiresVec2
inline Vector2Tmple<T> Vector2Tmple<T>::Normalized()
{
		 Vector2Tmple<T> vec = (*this);
		 vec.Normalize();
		 return vec;
}

template<class T> requiresVec2
inline float Vector2Tmple<T>::Theta()
{
	return atan2(this.y, this.x); 
}




template<class T> requiresVec2
inline void Vector2Tmple<T>::Rotate90()
{
	std::swap(x, y);
	x = -x;
}

template<class T> requiresVec2
inline Vector2 Vector2Tmple<T>::Sige()
{
		return Vector2{(x>0) - (x < 0),(y > 0) - (y < 0) };
}

template<class T> requiresVec2
inline Vector2Tmple<T> Vector2Tmple<T>::abs()
{
	return {std::abs(x),std::abs(y)};
}

template<class T> requiresVec2
inline  Vector2Tmple<T>  Vector2Tmple<T>::round()
{
	return {std::round(x),std::round(y) };
}

template<class T> requiresVec2
inline bool Vector2Tmple<T>::CheckNon()
{
	return  this->x == 0 && this->y == 0;
}

template<class T>
inline Vector2Tmple<T> operator+(const Vector2Tmple<T>& me, const Vector2Tmple<T>& num)
{
	return { me.x + num.x,me.y + num.y };
}

template<class T>
inline Vector2Tmple<T> operator-(const Vector2Tmple<T>& me, const T& num)
{
	return { me.x - num.x,me.y - num.y };
}

template<class T>
inline Vector2Tmple<T> operator-(const Vector2Tmple<T>& me, const Vector2Tmple<T>& num)
{
	return { me.x - num.x,me.y - num.y };
}

template<class T> requiresVec2
inline Vector2Tmple<T> operator*(const  Vector2Tmple<T>& me, const T& num)
{
		return { (me.x * num),(me.y * num) };
}

template<class T> requiresVec2
inline Vector2Tmple<T> operator/(const  Vector2Tmple<T>& me, const T& num)
{
	return { (me.x / num),(me.y / num) };
}



template<class T> requiresVec2
inline Vector2Tmple<T> operator*(const T& num, const  Vector2Tmple<T>& me)
{
		return { (me.x * num),(me.y * num) };
}


template<class T>
inline float Dot(const Vector2Tmple<T>& va, const Vector2Tmple<T>& vb)
{
	return va.x * vb.x + va.y * vb.y;;
}

template<class T>
inline float Cross(const Vector2Tmple<T>& va, const Vector2Tmple<T>& vb)
{
	return va.x * vb.y - vb.x * va.y;
}

template<class T>
inline double Angle(const Vector2Tmple<T>& va, const Vector2Tmple<T>& vb)
{
	float dx = vb.x - va.x;
	float dy = vb.y - va.y;
	float rad = std::atan2(dy, dx);
	return rad ;
}

template<class T> requiresVec2
template<class F>
inline Vector2Tmple<T> Vector2Tmple<T>::operator+(const Vector2Tmple<F> num)
{
	return   { this->x +static_cast<T>(num.x), this->y +static_cast<T>(num.y) };
}
template<class T> requiresVec2
template<class F> requires std::integral<F> || std::floating_point<F> || std::signed_integral<F> || std::unsigned_integral<F>
inline Vector2Tmple<T> Vector2Tmple<T>::operator-(const F num)
{
	return  { this->x - static_cast<T>(num), this->y - static_cast<T>(num) };
}
template<class T> requiresVec2
template<class F>
inline Vector2Tmple<T> Vector2Tmple<T>::operator-(const Vector2Tmple<F> num)
{
	return  { this->x - static_cast<T>(num.x), this->y - static_cast<T>(num.y) };
}
template<class T> requiresVec2
template<class F>
inline Vector2Tmple<T> Vector2Tmple<T>::operator*(const Vector2Tmple<F> num)
{
	return    { this->x * static_cast<T>(num.x), this->y * static_cast<T>(num.y) };
}
template<class T> requiresVec2
template<class F> requires std::integral<F> || std::floating_point<F> || std::signed_integral<F> || std::unsigned_integral<F>
inline Vector2Tmple<T> Vector2Tmple<T>::operator*(const F num)
{
	return  { this->x * static_cast<T>(num), this->y * static_cast<T>(num) };
}
template<class T> requiresVec2
template<class F>
inline Vector2Tmple<T> Vector2Tmple<T>::operator/(const Vector2Tmple<F> num)
{
	return   { this->x / static_cast<T>(num.x), this->y / static_cast<T>(num.y) };
}

template<class T> requiresVec2
template<class F> requires std::integral<F> || std::floating_point<F> || std::signed_integral<F> || std::unsigned_integral<F>
inline Vector2Tmple<T> Vector2Tmple<T>::operator/(const F num) 
{
	return   { this->x / static_cast<T>(num), this->y / static_cast<T>(num) };
}

template<class T> requiresVec2
template<class F>
inline Vector2Tmple<T> Vector2Tmple<T>::operator=(const Vector2Tmple<F>& num)
{
	return   { this->x = static_cast<T>(num.x), this->y = static_cast<T>(num.y) };
}

template<class T> requiresVec2
template<class F>
inline Vector2Tmple<F> Vector2Tmple<T>::cast(void) const
{
	return Vector2Tmple<F>{static_cast<F>(x), static_cast<F>(y) };
}

