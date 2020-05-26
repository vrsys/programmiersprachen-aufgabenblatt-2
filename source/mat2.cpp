#include "mat2.hpp"
#include "vec2.hpp"

/*Quellen:
http://statistik.wu-wien.ac.at/~leydold/MOK/HTML/node17.html
https://www.mathebibel.de/2x2-determinanten-berechnen
http://www.mathematrix.de/matrix-transponieren/
*/


Mat2& Mat2::operator*=(Mat2 const& m) {
	this->e_00 = this->e_00 * m.e_00 + this->e_01 * m.e_10;
	this->e_10 = this->e_10 * m.e_00 + this->e_11 * m.e_10;
	this->e_01 = this->e_00 * m.e_01 + this->e_01 * m.e_11;
	this->e_11 = this->e_10 * m.e_01 + this->e_11 * m.e_11;
	return *this;
}

float Mat2::det() const {
	float det = this->e_00 * this->e_11 - this->e_10 * this->e_01;
	return det;
}

Mat2 operator*(Mat2 const& m1, Mat2 const& m2) {
	Mat2 a = m1;
	a *= m2;
	return a;
}

Vec2 operator*(Mat2 const& m, Vec2 const& v) {
	Vec2 a{};
	a.x = m.e_00 * v.x + m.e_01 * v.y;
	a.y = m.e_10 * v.x + m.e_11 * v.y;
	return a;
}

Mat2 transpose(Mat2 const& m) {
	Mat2 a{ m.e_00, m.e_01, m.e_10, m.e_11 };
	return a;
}

/*Mat2 inverse(Mat2 const& m) {
	float det = m.det; //funktioniert nicht wegen det?
	if (det == 0) {
		std::cout << "FEHLER: Zu dieser Matrix gibt es keine inverse Matrix.";
		return Mat2{0, 0, 0, 0};
	}
	//Kofaktoren berechnen mithilfe Unterdeterminante d:
	float d_00 = m.e_11;
	float d_01 = -1 * m.e_10;
	float d_10 = -1 * m.e_01;
	float d_11 = m.e_00;
	//Kofaktormatrix aufstellen:
	Mat2 k{ d_00, d_10, d_01, d_11 };
	//Kofaktormatrix transponieren:
	Mat2 t{ transpose(k) };
	//Ergebnis berechnen:
	Mat2 e{ k.e_00 / det, k.e_10 / det, k.e_01 / det, k.e_11 / det };
	return e;
}*/

Mat2 make_rotation_mat2(float phi) {
	return Mat2{};
}
