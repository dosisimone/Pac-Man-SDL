#ifndef VECTOR2F_H
#define VECTOR2F_H

#include <math.h> 

class Vector2f
{
public:
	//CONSTANTS
	static const Vector2f ZERO;
	static const Vector2f RIGHT;
	static const Vector2f UP;
	static const Vector2f LEFT;
	static const Vector2f DOWN;

	// PROPERTIES
	float X;
	float Y;

	//COSTRUCTORS
	Vector2f()
	{
		X = 0.f;
		Y = 0.f;
	}

	Vector2f(float anX, float anY)
	{
		X = anX;
		Y = anY;
	}

	//OPERATORS
	const Vector2f Vector2f::operator-(const Vector2f& other) const
	{
		Vector2f v(X - other.X, Y - other.Y);
		return v;
	}

	const Vector2f Vector2f::operator+(const Vector2f& other) const
	{
		Vector2f v(X + other.X, Y + other.Y);
		return v;
	}


	const Vector2f Vector2f::operator*(const Vector2f& other) const
	{
		Vector2f v(X * other.X, Y * other.Y);
		return v;
	}

	Vector2f& Vector2f::operator+=(const Vector2f& other)
	{
		X = X + other.X;
		Y = Y + other.Y;
		return *this;
	}

	Vector2f& Vector2f::operator*=(const float aFloat)
	{
		X *= aFloat;
		Y *= aFloat;
		return *this;
	}

	Vector2f& Vector2f::operator/=(const float aFloat)
	{
		X /= aFloat;
		Y /= aFloat;

		return *this;
	}

	const Vector2f Vector2f::operator*(const float aValue) const
	{
		Vector2f v(X * aValue, Y * aValue);
		return v;
	}

	//FUNCTIONS
	float Vector2f::Length() const
	{
		return sqrt(X * X + Y * Y);
	}

	void Vector2f::Normalize()
	{
		float length = Length();

		if (length > 0.f) 
		{
			*this /= length;
		}
	}
};

#endif // VECTOR2F_H