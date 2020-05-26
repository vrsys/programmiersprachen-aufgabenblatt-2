
#include <array>
#include <iostream>

#ifndef MAT2_HPP
#define MAT2_HPP

//Mat2 definition

struct Mat2 {

	//matrix layout:
	//e_00 e_10
	//e_01 e_11

	float e_00 = 1; //oben links
	float e_10 = 0; //unten links
	float e_01 = 0; //oben rechts
	float e_11 = 1; //unten rechts

	Mat2& operator*=(Mat2 const& m);

	float det() const;

};

Mat2 operator*(Mat2 const& m1, Mat2 const& m2);
//Vec2 operator*(Mat2 const& v, Vec2 const& m); //funtkioniert nicht?

//Mat2 inverse(Mat2 const& m); //funktioniert nicht wegen det?
Mat2 transpose(Mat2 const& m); 
Mat2 make_rotation_mat2(float phi);

#endif