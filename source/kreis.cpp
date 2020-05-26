
#include "kreis.hpp"
#include "vec2.hpp"
#include "color.hpp"
#include "window.hpp"
#include "rechteck.hpp"

#include <iostream>

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

void Kreis::draw(Window& window, float const& thickness) const {
	float line = thickness;
	if (is_inside(window, *this)) {
		line *= 2;
	}
	/*
	1) x-Achse einteilen, z. B. Abstand 1
	2) für jeden x-Wert den dazugehören y-Wert auf Kreis berechnen:
		y = sqrt(x^2 + radius^2)
	3) Punkt einzeichnen
	*/
	float r = this->radius_;
	float rr = r * r;
	//oberer Halbkreis:
	for (int x = -r; x <= r; x += 2) {
		//erster Punkt:
		float x1 = x;
		float xx = x1 * x1;
		float y1 = sqrt(rr - xx);
		//zweiter Punkt:
		float x2 = x1 + 1;
		xx = x2 * x2;
		float y2 = sqrt(rr - xx);
		window.draw_line(
			x1 + this->center_.x, y1 + this->center_.y, x2 +
			this->center_.x, y2 + this->center_.y,
			this->color_.r, this->color_.g, this->color_.b, line
		);
	}
	//unterer Halbkreis:
	for (int x = -r; x <= r; x += 2) {
		//erster Punkt:
		float x1 = x;
		float xx = x1 * x1;
		float y1 = -1 * sqrt(rr - xx);
		//zweiter Punkt:
		float x2 = x1 + 1;
		xx = x2 * x2;
		float y2 = -1 * sqrt(rr - xx);
		window.draw_line(
			x1 + this->center_.x, y1 + this->center_.y, x2 +
			this->center_.x, y2 + this->center_.y,
			this->color_.r, this->color_.g, this->color_.b, line
		);
	}

	return;
}

void Kreis::draw(Window& window) const {
	Kreis::draw(window, 1);
	return;
}

Rechteck Kreis::bounding_box() const {
	Rechteck bb{ Vec2{this->center_.x - this->radius_, this->center_.y - this->radius_}, 
		Vec2{this->center_.x + this->radius_, this->center_.y + this->radius_} };
	return bb;
}

bool is_inside(Window& window, Kreis const& kreis) {
	auto mouse = window.mouse_position();
	Rechteck bb = kreis.bounding_box();
	Vec2 bb_min = bb.min();
	Vec2 bb_max = bb.max();
	//bb.draw(window);
	if (bb_min.x <= mouse.first && mouse.first <= bb_max.x &&
		bb_min.y <= mouse.second && mouse.second <= bb_max.y) {
		return true;
	}
	return false;
}


