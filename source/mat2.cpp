#include "mat2.hpp"

//Quelle: http://statistik.wu-wien.ac.at/~leydold/MOK/HTML/node17.html

Mat2& Mat2::operator*=(Mat2 const& m)
{
	this->e_00 = this->e_00 * m.e_00 + this->e_01 * m.e_10;
	this->e_10 = this->e_10 * m.e_00 + this->e_11 * m.e_10;
	this->e_01 = this->e_00 * m.e_01 + this->e_01 * m.e_11;
	this->e_11 = this->e_10 * m.e_01 + this->e_11 * m.e_11;
	return *this;
}

Mat2 operator*(Mat2 const& m1, Mat2 const& m2)
{
	Mat2 a = m1;
	a *= m2;
	return a;
}