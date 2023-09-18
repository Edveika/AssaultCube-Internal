#pragma once
#define PI 3.1415927f

struct Vector4 { float x, y, z, w; };

struct Vector3
{
	float x, y, z;

	Vector3() {};
	Vector3(const float x, const float y, const float z) : x(x), y(y), z(z) {}
	Vector3 operator + (const Vector3& rhs) const { return Vector3(x + rhs.x, y + rhs.y, z + rhs.z); }
	Vector3 operator - (const Vector3& rhs) const { return Vector3(x - rhs.x, y - rhs.y, z - rhs.z); }
	Vector3 operator * (const float& rhs) const { return Vector3(x * rhs, y * rhs, z * rhs); }
	Vector3 operator / (const float& rhs) const { return Vector3(x / rhs, y / rhs, z / rhs); }
	Vector3& operator += (const Vector3& rhs) { return *this = *this + rhs; }
	Vector3& operator -= (const Vector3& rhs) { return *this = *this - rhs; }
	Vector3& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector3& operator /= (const float& rhs) { return *this = *this / rhs; }
	float Length() const { return sqrtf(x * x + y * y + z * z); }
	Vector3 Normalize() const { return *this * (1 / Length()); }
	float Distance(const Vector3& rhs) const { return (*this - rhs).Length(); }
};

struct Vector2
{
	float x, y;

	Vector2() {};
	Vector2(const float x, const float y) : x(x), y(y) {}
	Vector2 operator + (const Vector2& rhs) const { return Vector2(x + rhs.x, y + rhs.y); }
	Vector2 operator - (const Vector2& rhs) const { return Vector2(x - rhs.x, y - rhs.y); }
	Vector2 operator * (const float& rhs) const { return Vector2(x * rhs, y * rhs); }
	Vector2 operator / (const float& rhs) const { return Vector2(x / rhs, y / rhs); }
	Vector2& operator += (const Vector2& rhs) { return *this = *this + rhs; }
	Vector2& operator -= (const Vector2& rhs) { return *this = *this - rhs; }
	Vector2& operator *= (const float& rhs) { return *this = *this * rhs; }
	Vector2& operator /= (const float& rhs) { return *this = *this / rhs; }
	float Length() const { return sqrtf(x * x + y * y); }
	Vector2 Normalize() const { return *this * (1 / Length()); }
	float Distance(const Vector2& rhs) const { return (*this - rhs).Length(); }
};

namespace Math
{
	float RadianToDegree(float radian);
	float DegreeToRadian(float degree);
	Vector3 RadianToDegree(Vector3 radians);
	Vector3 DegreeToRadian(Vector3 degrees);
	bool WorldToScreen(Vector3 Position, Vector2& ScreenPosition, float viewMatrix[16], int screenWidth, int screenHeight);
	Vector3 Subtract(Vector3 src, Vector3 dst);
	float PythagoreanTheorem(Vector3 vec);
	float Distance(Vector3 src, Vector3 dst);
	Vector3 CalcAngle(Vector3 src, Vector3 dst);
}