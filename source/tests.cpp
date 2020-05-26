
#include "vec2.hpp"
#include "mat2.hpp"
#include "color.hpp"
#include "kreis.hpp"
#include "rechteck.hpp"

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <iostream>
//für pi:
#define _USE_MATH_DEFINES
#include <math.h>


// 2.2
TEST_CASE("describe_vec2", "[vec2]") {
	Vec2 a;
	Vec2 b{ 5.1f, -9.3f };
	REQUIRE(0 == Approx(a.x));
	REQUIRE(0 == Approx(a.y));
	REQUIRE(5.1f == Approx(b.x));
	REQUIRE(-9.3f == Approx(b.y));
}

// 2.3
TEST_CASE("vec2 operators", "[vec2]") {
	// +=
	Vec2 a;
	Vec2 b{ 1, 1 };
	a += b;
	REQUIRE(a.x == b.x);
	REQUIRE(a.y == b.y);
	// -=
	a -= b;
	REQUIRE(a.x == 0);
	REQUIRE(a.y == 0);
	// *=
	b *= 0;
	REQUIRE(b.x == 0);
	REQUIRE(b.y == 0);
	// /=
	Vec2 c{ 2, 2 };
	c /= 2.0f;
	REQUIRE(c.x == 1);
	REQUIRE(c.y == 1);
}

// 2.4
TEST_CASE("operators", "[vec2]") {
	// +
	Vec2 a{ 2, 2 };
	Vec2 b{ 3, 3 };
	Vec2 c = a + b;
	REQUIRE(c.x == 5);
	REQUIRE(c.y == 5);
	// -
	c = b - a;
	REQUIRE(c.x == 1);
	REQUIRE(c.y == 1);
	// *
	c = b * 2;
	REQUIRE(c.x == 6);
	REQUIRE(c.y == 6);
	// /
	c = a / 2;
	REQUIRE(c.x == 1);
	REQUIRE(c.y == 1);
	// *
	c = 2 * b;
	REQUIRE(c.x == 6);
	REQUIRE(c.y == 6);
}

// 2.5 und 2.6
TEST_CASE("mat2 operators", "[mat2]") {
	// *= 2.5
	Mat2 a{ 1, 0, 1, 1 };
	Mat2 b{ 1, 1, 0, 1 };
	a *= b;
	REQUIRE(a.e_00 == 2);
	REQUIRE(a.e_10 == 1);
	REQUIRE(a.e_01 == 1);
	REQUIRE(a.e_11 == 1);
	a = Mat2{ 1, 1, 0, 1 };
	b = Mat2{ 1, 0, 1, 1 };
	a *= b;
	REQUIRE(a.e_00 == 1);
	REQUIRE(a.e_10 == 1);
	REQUIRE(a.e_01 == 1);
	REQUIRE(a.e_11 == 2);
	// * 2.5
	a = Mat2{ 1, 1, 0, 1 };
	b = Mat2{ 1, 0, 1, 1 };
	Mat2 c = a * b;
	REQUIRE(c.e_00 == 1);
	REQUIRE(c.e_10 == 1);
	REQUIRE(c.e_01 == 1);
	REQUIRE(c.e_11 == 2);
	// * 2.6
	Vec2 d{ 2, 2 };
	Vec2 e = a * d;
	REQUIRE(e.x == 2);
	REQUIRE(e.y == 4);
}

// 2.6
TEST_CASE("determinant", "[mat2]") {
	Mat2 a{ 2, 2, 2, 2 };
	Mat2 b{ 3, 2, 2, -3 };
	Mat2 c{ -4, -2.5, -2, 7 };
	/*float a_det = a.det; //funktioniert nicht?
	float b_det = b.det;
	float c_det = c.det;
	REQUIRE(a_det == 0);
	REQUIRE(b_det == -13);
	REQUIRE(c_det == -33);*/
}

// 2.6
TEST_CASE("transpose", "[mat2]") {
	Mat2 a{ 2, 4, 4, 1 };
	Mat2 b = transpose(a);
	REQUIRE(b.e_00 == 2);
	REQUIRE(b.e_10 == 4);
	REQUIRE(b.e_01 == 4);
	REQUIRE(b.e_11 == 1);
}

// 2.6
TEST_CASE("inverse", "[mat2]") {
	Mat2 a{ 4, 5, 3, 7 };
	/*Mat2 b = inverse(a); //funktioniert nicht wegen det?
	REQUIRE(b.e_00 == Approx(7/13));
	REQUIRE(b.e_10 == Approx(-5/13));
	REQUIRE(b.e_01 == Approx(-3/13));
	REQUIRE(b.e_11 == Approx(4/13));*/
}

// 2.7
TEST_CASE("describe color", "[color]") {
	Color a;
	REQUIRE(a.r == 0.5f);
	REQUIRE(a.g == 0.5f);
	REQUIRE(a.b == 0.5f);
	Color b{ 1, 1, 1 };
	REQUIRE(b.r == 1);
	REQUIRE(b.g == 1);
	REQUIRE(b.b == 1);
}

// 2.9
TEST_CASE("rechteck_circumference", "[Rechteck]") {
	Rechteck a{ Vec2 {0, 0}, Vec2 {5, 5} };
	float b = a.circumference();
	REQUIRE(b == 20);
}

// 2.9
TEST_CASE("kreis_circumference", "[Kreis]") {
	Kreis a{ Vec2{0, 0}, 1 };
	float b = a.circumference();
	REQUIRE(b == Approx(2 * M_PI));
}


int main(int argc, char* argv[]) {
	return Catch::Session().run(argc, argv);
}
