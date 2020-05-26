
#include "kreis.hpp"
#include "vec2.hpp"
#include "color.hpp"

//für pi:
#define _USE_MATH_DEFINES
#include <math.h>


Kreis::Kreis(Kreis const& kreis) :
	center_{ kreis.center_ },
	radius_{ kreis.radius_ },
	color_{ kreis.color_ }
{}


Kreis::Kreis(Vec2 const& center, float radius, Color const& color) :
	center_{ center },
	radius_{ radius },
	color_{ color }
{}

Kreis::Kreis(Vec2 const& center, float radius) :
	center_{ center },
	radius_{ radius },
	color_{ 0, 0, 0 }
{}

/*
void Kreis::set_center(Vec2 const& center) {
	this->center_ = center;
}

void Kreis::set_color(Color const& color) {
	this->color_ = color;
}

Vec2 Kreis::get_center() const {
	return Vec2(center_);
}
*/

float Kreis::circumference() const {
	return 2 * M_PI * this->radius_;
}


