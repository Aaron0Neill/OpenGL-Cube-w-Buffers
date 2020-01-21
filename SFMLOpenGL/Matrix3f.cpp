#include "Matrix3f.h"

using namespace gpp;

Matrix3f::Matrix3f() :
	m_a11(0.f),
	m_a12(0.f),
	m_a13(0.f),
	m_a21(0.f),
	m_a22(0.f),
	m_a23(0.f),
	m_a31(0.f),
	m_a32(0.f),
	m_a33(0.f)
{
}

Matrix3f::Matrix3f(float a1, float a2, float a3, float b1, float b2, float b3, float c1, float c2, float c3) :
	m_a11(a1),
	m_a12(a2),
	m_a13(a3),
	m_a21(b1),
	m_a22(b2),
	m_a23(b3),
	m_a31(c1),
	m_a32(c2),
	m_a33(c3)
{
}

Matrix3f::Matrix3f(MyVector3f a, MyVector3f b, MyVector3f c) : 
	m_a11(a.getX()),
	m_a12(a.getY()),
	m_a13(a.getZ()),
	m_a21(b.getX()),
	m_a22(b.getY()),
	m_a23(b.getZ()),
	m_a31(c.getX()),
	m_a32(c.getY()),
	m_a33(c.getZ())
{
}

Matrix3f Matrix3f::transpose() const
{
	return Matrix3f(m_a11, m_a21, m_a31, m_a12, m_a22, m_a32, m_a13, m_a23, m_a33);
}

float Matrix3f::determinant() const
{
	float det = m_a11 * ((m_a22 * m_a33) - (m_a32 * m_a23)) - m_a21 * (m_a33 * m_a12 - m_a32 * m_a13) + m_a31 * (m_a23 * m_a12 - m_a22 * m_a13);
	return det;
}

Matrix3f Matrix3f::inverse() const
{
	float det = this->determinant();
	if (det > 0)
	{
		Matrix3f inverse = { (m_a33 * m_a22 - m_a32 * m_a23) , (m_a32 * m_a13 - m_a33 * m_a12) , (m_a23 * m_a12 - m_a22 * m_a13),
							 (m_a31 * m_a23 - m_a33 * m_a21) , (m_a33 * m_a11 - m_a31 * m_a13) , (m_a21 * m_a13 - m_a23 * m_a11),
							 (m_a32 * m_a21 - m_a31 * m_a22) , (m_a31 * m_a12 - m_a32 * m_a11) , (m_a22 * m_a11 - m_a21 * m_a12) };
		inverse = inverse * (1.f / det);
		return inverse;
	}
	else
		return Matrix3f();
}

Matrix3f Matrix3f::translate(const MyVector3f displacement)
{
	return Matrix3f(1, 0, displacement.getX(),
					0, 1, displacement.getY(),
					0, 0, 1);
}

Matrix3f Matrix3f::scale(float const scale)
{
	return Matrix3f(scale,0,0,
					0,scale,0,
					0,0,scale);
}

Matrix3f Matrix3f::rotateX(float const angle)
{
	float angleRad = 3.14159 / 180 * angle;
	return Matrix3f(1,0,0,
					0,cos(angleRad),-sin(angleRad),
					0,sin(angleRad),cos(angleRad));
}

Matrix3f Matrix3f::rotateY(float const angle)
{
	float angleRad = 3.14159 / 180 * angle;
	return Matrix3f(cos(angleRad), 0, sin(angleRad),
					0, 1, 0,
					-sin(angleRad), 0, cos(angleRad));
}

Matrix3f Matrix3f::rotateZ(float const angle)
{
	float angleRad = 3.14159 / 180 * angle;
	return Matrix3f(cos(angleRad), -sin(angleRad), 0,
					sin(angleRad), cos(angleRad), 0,
					0, 0, 1);
}

MyVector3f Matrix3f::row(int row) const
{
	switch (row)
	{
	case 0:
		return  MyVector3f(m_a11, m_a12, m_a13);
		break;
	case 1:
		return  MyVector3f(m_a21, m_a22, m_a23);
		break;
	case 2:
		return  MyVector3f(m_a31, m_a32, m_a33);
		break;
	default:
		return  MyVector3f(0,0,0);
		break;
	}
}

MyVector3f Matrix3f::column(int col) const
{
	switch (col)
	{
	case 0:
		return  MyVector3f(m_a11, m_a21, m_a31);
		break;
	case 1:
		return  MyVector3f(m_a12, m_a22, m_a32);
		break;
	case 2:
		return  MyVector3f(m_a13, m_a23, m_a33);
		break;
	default:
		return  MyVector3f(0, 0, 0);
		break;
	}
}

MyVector3f Matrix3f::operator*(const MyVector3f vec) const
{
	return MyVector3f((m_a11 * vec.getX()) + (m_a12 * vec.getY()) + (m_a13 * vec.getZ()),
		(m_a21 * vec.getX()) + (m_a22 * vec.getY()) + (m_a23 * vec.getZ()),
		(m_a31 * vec.getX()) + (m_a32 * vec.getY()) + (m_a33 * vec.getZ()));
}

Matrix3f Matrix3f::operator*(const float s) const
{
	return Matrix3f(m_a11 * s, m_a12 * s, m_a13 * s,
					m_a21 * s, m_a22 * s, m_a23 * s,
					m_a31 * s, m_a32 * s, m_a33 * s);
}

Matrix3f Matrix3f::operator*(const Matrix3f m) const
{
	return Matrix3f((m_a11 * m.m_a11) + (m_a12 * m.m_a21) + (m_a13 * m.m_a31),
					(m_a11 * m.m_a12) + (m_a12 * m.m_a22) + (m_a13 * m.m_a32),
					(m_a11 * m.m_a13) + (m_a12 * m.m_a23) + (m_a13 * m.m_a33),
					(m_a21 * m.m_a11) + (m_a22 * m.m_a21) + (m_a23 * m.m_a31),
					(m_a21 * m.m_a12) + (m_a22 * m.m_a22) + (m_a23 * m.m_a32),
					(m_a21 * m.m_a13) + (m_a22 * m.m_a23) + (m_a23 * m.m_a33),
					(m_a31 * m.m_a11) + (m_a32 * m.m_a21) + (m_a33 * m.m_a31),
					(m_a31 * m.m_a12) + (m_a32 * m.m_a22) + (m_a33 * m.m_a32),
					(m_a31 * m.m_a13) + (m_a32 * m.m_a23) + (m_a33 * m.m_a33));
}

Matrix3f Matrix3f::operator+(const Matrix3f m) const
{
	return Matrix3f(m_a11 + m.m_a11, m_a12 + m.m_a12, m_a13 + m.m_a13,
					m_a21 + m.m_a21, m_a22 + m.m_a22, m_a23 + m.m_a23,
					m_a31 + m.m_a31, m_a32 + m.m_a32, m_a33 + m.m_a33);
}

Matrix3f Matrix3f::operator-(const Matrix3f m) const
{
	return Matrix3f(this->m_a11 - m.m_a11, this->m_a12 - m.m_a12, this->m_a13 - m.m_a13,
					this->m_a21 - m.m_a21, this->m_a22 - m.m_a22, this->m_a23 - m.m_a23,
					this->m_a31 - m.m_a31, this->m_a32 - m.m_a32, this->m_a33 - m.m_a33);
}

Matrix3f Matrix3f::operator-() const
{
	return Matrix3f(-m_a11,-m_a12,-m_a13,-m_a21, -m_a22, -m_a23, -m_a31, -m_a32, -m_a33);
}

std::string Matrix3f::toString() const
{
	return std::string(("{( " + std::to_string(m_a11) + " , " + std::to_string(m_a12) + " , " + std::to_string(m_a13) + ")\n ( "
		+ std::to_string(m_a21) + " , " + std::to_string(m_a22) + " , " + std::to_string(m_a23) + ")\n ( "
		+ std::to_string(m_a31) + " , " + std::to_string(m_a32) + " , " + std::to_string(m_a33) + ")}"));
}

std::string Matrix3f::operator<<(const Matrix3f matrix) const
{
	return matrix.toString();
}
