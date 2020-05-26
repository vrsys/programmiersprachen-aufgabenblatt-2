#include "vec2.hpp" 
#include "color.hpp" 
#include "window.hpp"

#ifndef KREIS_HPP
#define KREIS_HPP

class Kreis {
public:
	Kreis(Kreis const& kreis); //copy constructor
	Kreis(Vec2 const& center, float radius, Color const& color);
	Kreis(Vec2 const& center, float radius);

	/*
	void set_center(Vec2 const& center);
	void set_color(Color const& color);
	Vec2 get_center() const;
	*/
	float circumference() const;
	void draw(Window window, float thickness) const;
	void draw(Window window) const;

private:
	Vec2 center_;
	float radius_;
	Color color_;
};

#endif