#pragma once
#include<concepts>
//using Vector2 = Vector2Tmple<int>;


#define requiresVec2  requires std::integral<T> || std::floating_point<T> || std::signed_integral<T> || std::unsigned_integral<T>
//�e���v���[�g�N���X
 //���܂蕶��@template <class T> class
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

	//2�����Z�q
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

	//������Z�q
	inline Vector2Tmple& operator=(const Vector2Tmple& num);		//���������Q�Ɠn���ł�����
	template<class F>
	inline Vector2Tmple<T> operator=(const Vector2Tmple<F>& num);
	//�Y�������Z�q
	inline int& operator[](const int& cnt);

	//�P�����Z�q
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

	inline Vector2Tmple operator+()const; //�������const �͊֐����ł�this�̃����o�[�̕ύX�𔛂� 

	inline Vector2Tmple operator-()const;
	//cast
	template<class F>
	inline Vector2Tmple<F> cast(void) const;

	//��r���Z�q
	inline bool operator<(const Vector2Tmple& num)const;
	inline bool operator<=(const Vector2Tmple& num)const;
	inline bool operator>(const Vector2Tmple& num)const;
	inline bool operator>=(const Vector2Tmple& num)const;
	inline bool operator==(const Vector2Tmple& num)const;
	inline bool operator!=(const Vector2Tmple& num)const;


	//�x�N�g���̑傫����Ԃ�
	double Magnitude()const;//���̒��ł͒l�̕ύX�����Ȃ���
	//�x�N�g����2���Ԃ�
	double SQ_Magnitude()const;
	//�x�N�g���̑傫����Ԃ�
	template<class F>
	F Magnitude()const;//���̒��ł͒l�̕ύX�����Ȃ���
	//�x�N�g����2���Ԃ�
	template<class F>
	F SQ_Magnitude()const;

	//���K������
	void Normalize(); 
	Vector2Tmple Normalized();
	//�p�x��Ԃ�
	float Theta();
	//90�x��]
	void Rotate90();
	//������Ԃ�
	Vector2Tmple<int> Sige();

	Vector2Tmple abs();

	Vector2Tmple round();

	bool CheckNon();

private:
};

template<class T> //�錾�O�Ȃ̂ōēx�錾���ċ����Ă����Ȃ��Ƃ����Ȃ�
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
/// ���ς�Ԃ�
/// </summary>
/// <param name="va">����</param>
/// <param name="vb">�E��</param>
/// <returns>���ϒl</returns>
template<class T>
inline extern float Dot(const Vector2Tmple<T>& va, const Vector2Tmple<T>& vb);

/// <summary>
/// �O�ς�Ԃ�
/// </summary>
/// <param name="va">����</param>
/// <param name="vb">�E��</param>
/// <returns>�O�ϒl</returns>
template<class T>
inline extern float Cross(const Vector2Tmple<T>& va, const Vector2Tmple<T>& vb);
template<class T>
inline extern double Angle(const Vector2Tmple<T>& va, const Vector2Tmple<T>& vb);



using Vector2Flt = Vector2Tmple<float>;

using Vector2Dbl = Vector2Tmple<double>;

using Vector2 = Vector2Tmple<int>;

using Position2 = Vector2Tmple<int>;

#include"Vector2/Vector2.h"

