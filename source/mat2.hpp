
#include <array>

#ifndef MAT2_HPP
#define MAT2_HPP

//Mat2 definition

struct Mat2 {

	//matrix layout:
	//e_00 e_10
	//e_01 e_11

	float e_00 = 1.0f; //oben links
	float e_10 = 0.0f; //unten links
	float e_01 = 0.0f; //oben rechts
	float e_11 = 1.0f; //unten rechts

	Mat2& operator*=(Mat2 const& m);

};

Mat2 operator*(Mat2 const& m1, Mat2 const& m2);

#endif