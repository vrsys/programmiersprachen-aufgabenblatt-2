
#include "rechteck.hpp"
#include "vec2.hpp" 
#include "pair.hpp"

Rechteck::Rechteck(Rechteck const& rechteck) {
	this->max_ = rechteck.max_;
	this->min_ = rechteck.min_;
	this->color_ = rechteck.color_;
}

Rechteck::Rechteck(Vec2 const& min, Vec2 const& max, Color const& color) :
	min_{ min },
	max_{ max },
	color_{ color }
{}

Rechteck::Rechteck(Vec2 const& min, Vec2 const& max) :
	min_{ min },
	max_{ max },
	color_{0, 0, 0}
{}

Pair Rechteck::side_lenghs() const {
	float x;
	if (this->max_.x > this->min_.x) {
		x = this->max_.x - this->min_.x;
	}
	else {
		x = this->min_.x - this->max_.x;
	}
	float y;
	if (this->max_.y > this->min_.y) {
		y = this->max_.y - this->min_.y;
	}
	else {
		y = this->min_.y - this->max_.y;
	}
	return Pair{x, y};
}

float Rechteck::circumference() const {
	Pair a{ this->side_lenghs()};
	return (a.a + a.b) * 2;
}