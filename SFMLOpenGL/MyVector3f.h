#pragma once

#include <iostream>
#include <string>
#include <math.h>

namespace gpp
{

	class MyVector3f
	{
	public:
		MyVector3f();
		MyVector3f(float x, float y, float z);

		float length() const;
		float lenghtSquared() const;
		MyVector3f unitVector() const;
		void normalise();
		float dotProduct(const MyVector3f vec)const;
		MyVector3f crossProduct(const MyVector3f vec) const;

		MyVector3f operator+(const MyVector3f vec)const;
		MyVector3f operator-(const MyVector3f vec)const;
		MyVector3f operator*(const float scalar)const;
		MyVector3f operator/(const float divisor)const;
		MyVector3f operator-=(const MyVector3f vec);
		MyVector3f operator+=(const MyVector3f vec);

		MyVector3f operator-()const;

		std::string toString()const;
		std::string operator<<(MyVector3f const vec)const;

		float getX() const { return m_x; }
		float getY() const { return m_y; }
		float getZ() const { return m_z; }

		void setX(float x) { m_x = x; }
		void setY(float y) { m_y = y; }
		void setZ(float z) { m_z = z; }

	private:
		float m_x;
		float m_y;
		float m_z;
	};
}