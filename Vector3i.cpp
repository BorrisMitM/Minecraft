#include "Vector3i.h"
Vector3i::Vector3i()
{
	x = y = z = 0;
}

Vector3i::Vector3i(int x, int y, int z) : x(x), y(y), z(z)
{
}

Vector3i Vector3i::operator + (Vector3i const& v)
{
	Vector3i temp;
	temp.x = x + v.x;
	temp.y = y + v.y;
	temp.z = z + v.z;
	return temp;
}

Vector3i Vector3i::operator - (Vector3i const& v)
{
	Vector3i temp;
	temp.x = x - v.x;
	temp.y = y - v.y;
	temp.z = z - v.z;
	return temp;
}

Vector3i& Vector3i::operator+=(Vector3i const& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;

	return *this;
}

Vector3i& Vector3i::operator-=(Vector3i const& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;

	return *this;
}

Vector3i Vector3i::operator * (float const& v)
{
	Vector3i temp;
	temp.x = x * v;
	temp.y = y * v;
	temp.z = z * v;
	return temp;
}


void Vector3i::Print()
{
	cout << x << ", " << y << ", " << z << endl;
}
