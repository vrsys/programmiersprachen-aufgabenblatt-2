#include "vec2.hpp" //soll das hier hin?
#include "color.hpp" //soll das hier hin?

#ifndef KREIS_HPP
#define KREIS_HPP

class Kreis {
public:
	Kreis(Kreis const& kreis); //copy constructor
	Kreis(Vec2 const& center, float radius, Color const& color);

	void set_center(Vec2 const& center);
	void set_color(Color const& color);
	Vec2 get_center() const;

private:
	Vec2 center_;
	float radius_;
	Color color_;
};

#endif