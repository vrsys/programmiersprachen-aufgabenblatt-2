
#include "vec2.hpp"

#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <iostream>


TEST_CASE("describe_vec2", "[vec2]") {
	Vec2 a;
	Vec2 b{ 5.1f, -9.3f };
	REQUIRE(0.0f == Approx(a.x));
	REQUIRE(0.0f == Approx(a.y));
	REQUIRE(5.1f == Approx(b.x));
	REQUIRE(-9.3f == Approx(b.y));
}

TEST_CASE("vec2 operators") {
	// +=
	Vec2 a;
	Vec2 b{ 1.0f, 1.0f };
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
	Vec2 c{ 2.0f, 2.0f };
	c /= 2.0f;
	REQUIRE(c.x == 1.0f);
	REQUIRE(c.y == 1.0f);
}

TEST_CASE("operators") {
	// +
	Vec2 a{2.0f, 2.0f};
	Vec2 b{ 3.0f, 3.0f };
	Vec2 c = a + b;
	REQUIRE(c.x == 5.0f);
	REQUIRE(c.y == 5.0f);
	// -
	c = b - a;
	REQUIRE(c.x == 1.0f);
	REQUIRE(c.y == 1.0f);
	// *
	c = b * 2;
	REQUIRE(c.x == 6.0f);
	REQUIRE(c.y == 6.0f);
	// /
	c = a / 2;
	REQUIRE(c.x == 1.0f);
	REQUIRE(c.y == 1.0f);
	// *
	c = 2 * b;
	REQUIRE(c.x == 6.0f);
	REQUIRE(c.y == 6.0f);
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}
