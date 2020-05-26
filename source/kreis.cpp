
#include "kreis.hpp"
#include "vec2.hpp"
#include "color.hpp"


Kreis::Kreis(Kreis const& kreis) {
	this->center_ = kreis.center_;
	this->radius_ = kreis.radius_;
	this->color_ = kreis.color_;
}

Kreis::Kreis(Vec2 const& center, float radius, Color const& color) {
	this->center_ = center;
	this->radius_ = radius;
	this->color_ = color;
}


void Kreis::set_center(Vec2 const& center) {
	this->center_ = center;
}

void Kreis::set_color(Color const& color) {
	this->color_ = color;
}

Vec2 Kreis::get_center() const {
	return Vec2(center_);
}




