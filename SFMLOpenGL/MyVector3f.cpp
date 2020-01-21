#include "MyVector3f.h"

using namespace gpp;

MyVector3f::MyVector3f() : 
	m_x(0),
	m_y(0),
	m_z(0)
{
}

MyVector3f::MyVector3f(float x, float y, float z) : 
	m_x(x),
	m_y(y),
	m_z(z)
{
}

float MyVector3f::length() const
{
	return sqrt(this->lenghtSquared());
}

float MyVector3f::lenghtSquared() const
{
	return (m_x * m_x + m_y * m_y + m_z * m_z);
}

MyVector3f MyVector3f::unitVector() const
{
	float magnitude = this->length();
	if (magnitude > 0)
		return MyVector3f(m_x / magnitude, m_y / magnitude, m_z / magnitude);
	else
		return MyVector3f();
}

void MyVector3f::normalise()
{
	float magnitude = this->length();
	if (magnitude > 0)
	{
		m_x /= magnitude;
		m_y /= magnitude;
		m_z /= magnitude;
	}
}

float MyVector3f::dotProduct(const MyVector3f vec) const
{
	return (m_x * vec.m_x + m_y * vec.m_y + m_z * vec.m_z);
}

MyVector3f MyVector3f::crossProduct(const MyVector3f vec) const
{
	return MyVector3f((m_y * vec.m_z - vec.m_y * m_z), ((m_x * vec.m_z) - (vec.m_x * m_z)) * -1, (m_x * vec.m_y) - (vec.m_x * m_y));
}

MyVector3f MyVector3f::operator+(const MyVector3f vec) const
{
	return MyVector3f(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
}

MyVector3f MyVector3f::operator-(const MyVector3f vec) const
{
	return MyVector3f(m_x - vec.m_x, m_y - vec.m_y, m_z - vec.m_z);
}

MyVector3f MyVector3f::operator*(const float scalar) const
{
	return MyVector3f(m_x * scalar, m_y * scalar, m_z * scalar);
}

MyVector3f MyVector3f::operator/(const float divisor) const
{
	if (divisor != 0)
		return MyVector3f(m_x / divisor, m_y / divisor, m_z / divisor);
	else
		return MyVector3f();
}

MyVector3f MyVector3f::operator-=(const MyVector3f vec)
{
	m_x -= vec.m_x;
	m_y -= vec.m_y;
	m_z -= vec.m_z;
	return *this;
}

MyVector3f MyVector3f::operator+=(const MyVector3f vec) 
{
	m_x += vec.m_x;
	m_y += vec.m_y;
	m_z += vec.m_z;
	return *this;
}


MyVector3f MyVector3f::operator-() const
{
	return MyVector3f(-m_x, -m_y, -m_z);
}

std::string MyVector3f::toString() const
{
	return { "x: " + std::to_string(m_x) + " , y: " + std::to_string(m_y) + " , z: " +std::to_string(m_z) };
}

std::string MyVector3f::operator<<(MyVector3f const vec) const
{
	return std::string("x: " + std::to_string(vec.m_x) + " , y: " + std::to_string(vec.m_y) + " , z: " + std::to_string(vec.m_z));
}
