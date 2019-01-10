
//=========================
//Circle.h
//has declaration of Circle class to avoid duplicates in Circle.app and myapp.cpp

class Circle {
public: 
	Circle(double x, double y, double r);
	bool scale(double factor);
	void draw();
	double radius() const;
		// Class invariant:
		// m_r > 0
private:
	double m_x;
	double m_y;
	double m_r;
};

//=========================
//Circle.cpp
//defines Circle::Circle... area
//needs: <<, >>, exit, atan

#include "Circle.h" //pulls in declaration from Circle.h
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

double area(const Circle& x); //Circle& is not a pointer; we are passing-by-const-reference

Circle::Circle(double x, double y, double r) {
	if (r <= 0) {
		cerr << "Cannot create a circle with radius " << r << endl;
		exit(1); //terminates program (drastic, but we don't learn about exceptions)
	}
	m_x = x;
	m_y = y;
	m_r = r;
}

bool Circle::scale(double factor) {
	if (factor <= 0)
		return false;
	m_r *= factor;
	return true;
}

void Circle::draw() {

}

double Circle::radius() const {
	return m_r;
}

double area(const Circle& x) { 
	const double PI = 4 * atan(1.0); //cmath libary doesn't have the Pi constant
	return PI * x.radius() * x.radius();
}


//=========================
//myapp.cpp
//defines main
//needs Circle::Circle... area, <<, >>

int main() {
	Circle c(8, -3, 3.7); 
	Circle d(-2, -5, 10); //square's upper left corner and diameter: m_xul = 12, m_yul = 15, m_diam = 20
	c.scale(2);
	d.draw();
	cout << area(d);
	double e;
	cin >> e;
	if (d.scale(e)) //stuff inside if statement will get executed
		cout << d.radius(); 
	Circle f(0, 0, -43); //constructor doesn't return anything bc sometimes it can't construct a valid object


}

/*
-C++ source program (.cpp)
	-compiler translates C++ source program into object file
-object file (.o or .obj)
	-defines: main
	-needs: Circle::Circle, Circle::scale, Circle::draw, area, operator <<
-libraries
	-defines: strlen, string::size, atan, operator <<, ...
	-linker uses object file and libraries to build executable
-executable (.exe or a.out or whatever follows "g32 -o")

-without defining function body, program compiles

interface (what) VS. implementation (how)

double area(Circle x); //in C++: pass-by-copy; in Java, pass-by-reference



class Blah
{
	...
		void g(Foo f, Foo& fr, Foo* fp);  // just need to say   class Foo;
	...
		Foo* m_fp;           // just need to say   class Foo;
	Foo* m_fpa[10];      // just need to say   class Foo;
	vector<Foo*> m_fpv;  // just need to say   class Foo;

	Foo m_f;             // must #include Foo.h
	Foo m_fa[10];        // must #include Foo.h
	vector<Foo> m_fv;    // must #include Foo.h
};

void Blah::g(Foo f, Foo& fr, Foo* fp)
{
	Foo f2(10, 20);      // must #include Foo.h
	f.gleep();           // must #include Foo.h
	fr.gleep();          // must #include Foo.h
	fp->gleep();         // must #include Foo.h
}

*/



