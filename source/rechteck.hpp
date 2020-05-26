#include "vec2.hpp" 
#include "color.hpp" 
#include "pair.hpp"
#include "window.hpp"

#ifndef RECHTECK_HPP
#define RECHTECK_HPP

class Rechteck {
public:
	Rechteck(Rechteck const& rechteck);
	Rechteck(Vec2 const& min, Vec2 const& max, Color const& color);
	Rechteck(Vec2 const& min, Vec2 const& max);

	Pair side_lenghs() const;
	float circumference() const;
	void draw(Window window) const;
	void draw(Window window, float thickness) const;

private:
	Vec2 min_; //linke untere Ecke
	Vec2 max_; //rechte obere Ecke
	Color color_;
};

#endif
