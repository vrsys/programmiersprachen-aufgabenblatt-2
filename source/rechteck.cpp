
#include "rechteck.hpp"
#include "vec2.hpp" 
#include "pair.hpp"
#include "window.hpp"

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

void Rechteck::draw(Window window) const {
	Pair a{ this->side_lenghs() };
	window.draw_line(0, 0, 100, 100, 1, 1, 1, 1);
	//unten links nach unten rechts:
	/*window.draw_line(
		this->min_.x, this->min_.y, 
		this->min_.x + a.a, this->min_.y + a.b,
		this->color_.r, this->color_.g, this->color_.b, 1
	);
	//unten rechts nach oben rechts:
	window.draw_line(
		this->min_.x + a.a, this->min_.y + a.b,
		this->max_.x, this->max_.y,
		this->color_.r, this->color_.g, this->color_.b, 1
	);
	//oben rechts nach oben links:
	window.draw_line(
		this->max_.x, this->max_.y,
		this->max_.x - a.a, this->max_.y - a.b,
		this->color_.r, this->color_.g, this->color_.b, 1
	);
	//oben links nach unten links:
	window.draw_line(
		this->max_.x - a.a, this->max_.y - a.b,
		this->min_.x, this->min_.y,
		this->color_.r, this->color_.g, this->color_.b, 1
	);*/
	return;
}