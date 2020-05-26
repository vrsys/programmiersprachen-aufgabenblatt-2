#include "vec2.hpp" //soll das hier hin?
#include "color.hpp" //soll das hier hin

#ifndef RECHTECK_HPP
#define RECHTECK_HPP

class Rechteck {
public:
	Rechteck(Rechteck const& rechteck);
	Rechteck(Vec2 const& min, Vec2 const& max, Color const& color);

private:
	Vec2 min_; //linke untere Ecke
	Vec2 max_; //rechte obere Ecke
	Color color_;
};

#endif
