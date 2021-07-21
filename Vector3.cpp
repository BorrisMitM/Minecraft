#include "Vector3.h"
Vector3::Vector3()
{
	x = y = z = 0.0f;
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
}

Vector3 Vector3::operator + (Vector3 const& v)
{
	Vector3 temp;
	temp.x = x + v.x;
	temp.y = y + v.y;
	temp.z = z + v.z;
	return temp;
}

Vector3 Vector3::operator - (Vector3 const& v)
{
	Vector3 temp;
	temp.x = x - v.x;
	temp.y = y - v.y;
	temp.z = z - v.z;
	return temp;
}

Vector3& Vector3::operator+=(Vector3 const& v)
{
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;

	return *this;
}

Vector3& Vector3::operator-=(Vector3 const& v)
{
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;

	return *this;
}

Vector3 Vector3::operator * (float const& v)
{
	Vector3 temp;
	temp.x = x * v;
	temp.y = y * v;
	temp.z = z * v;
	return temp;
}

bool Vector3::operator==(Vector3 const& v)
{
	float error = 0.01;
	if (abs(this->x - v.x) > error || abs(this->y - v.y) > error || abs(this->z - v.z) > error) {
		return false;
	}
	else {
		return true;
	}
}

Vector3 Vector3::cross(const Vector3& v2) {
	Vector3 cross(
		(this->y * v2.z - this->z * v2.y),
		(this->z * v2.x - this->x * v2.z),
		(this->x * v2.y - this->y * v2.x)
	);
	return cross;
}

float Vector3::dot(const Vector3& v2)
{
	return x * v2.x + y * v2.y + z * v2.z;
}

float Vector3::sqrdMagnitude()
{
	return x * x + y * y + z * z;
}

void Vector3::Normalize()
{
	float length = sqrt(x * x + y * y + z * z);
	// cannot normalize vector of length 0;
	if (length == 0) return;
	x /= length;
	y /= length;
	z /= length;
}

void Vector3::Print()
{
	cout << x << ", " << y << ", " << z << endl;
}
