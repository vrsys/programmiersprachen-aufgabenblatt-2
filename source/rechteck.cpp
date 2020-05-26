
#include "rechteck.hpp"
#include "vec2.hpp" 

Rechteck::Rechteck(Rechteck const& rechteck) {
	this->max_ = rechteck.max_;
	this->min_ = rechteck.min_;
	this->color_ = rechteck.color_;
}

Rechteck::Rechteck(Vec2 const& min, Vec2 const& max, Color const& color) {
	this->min_ = min;
	this->max_ = max;
	this->color_ = color;
}