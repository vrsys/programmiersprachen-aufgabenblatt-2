#include "vec2.hpp"

#include <iostream>

float x = 0;
float y = 0;

Vec2& Vec2::operator+=(Vec2 const& v) {
	this->x += v.x;
	this->y += v.y;
	return *this;
}

Vec2& Vec2::operator-=(Vec2 const& v) {
	this->x -= v.x;
	this->y -= v.y;
	return *this;
}

Vec2& Vec2::operator*=(float s) {
	this->x *= s;
	this->y *= s;
	return *this;
}

Vec2& Vec2::operator/=(float s) {
	if (s == 0) {
		std::cout << "FEHLER, Division durch 0";
		return Vec2{};
	}
	this->x /= s;
	this->y /= s;
	return *this;
}

Vec2 operator+(Vec2 const& u, Vec2 const& v) {
	Vec2 a;
	(a += u) += v;
	return a;
}

Vec2 operator-(Vec2 const& u, Vec2 const& v) {
	Vec2 a = u;
	a -= v;
	return a;
}

Vec2 operator*(Vec2 const& v, float s) {
	Vec2 a = v;
	a *= s;
	return a;
}

Vec2 operator/(Vec2 const& v, float s) {
	if (s == 0) {
		std::cout << "FEHLER, Division durch 0";
		return Vec2{};
	}
	Vec2 a = v;
	a /= s;
	return a;
}

Vec2 operator*(float s, Vec2 const& v) {
	Vec2 a = v;
	a *= s;
	return a;
}


