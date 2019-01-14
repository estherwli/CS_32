#include <iostream>
using namespace std;

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



/*
"circular dependency"
*/

class Circle {
public:
	Circle(double x, double y, double r);
	//...
private:
	double m_x;
	double m_y;
	double m_r;
};

Circle::Circle(double x, double y, double r)
	:m_x(x), m_y(y), m_r(r) {
	//...
}

class StickFigure {
public:
	StickFigure(double bl, double headDiam,
		string nm, double hx, double hy);
	Circle& circle();
private:
	string m_name;
	Circle m_head; //you can't touch your liver
	double m_bodyLength;
};

//*********************** this constructor won't compile *******************************
StickFigure::StickFigure(double bl, double headDiam, string nm, double hx, double hy) {
	m_name = nm;
	m_x = hx; //won't compile bc m_x is a private member of Circle
	m_head.m_y = hy; //won't compile bc m_y is a private member of Circle
	circle().m_r = headDiam / 2; //won't compile bc m_r is a private member of Circle
	m_bodyLength = bl;
}
//***************************************************************************************

StickFigure::StickFigure(double bl, double headDiam, string nm, double hx, double hy)
	: m_name(nm), m_head(hx, hy, headDiam / 2), m_bodyLength(bl) {
	//empty body is okay; sometimes need error-checking here 
}

Circle& StickFigure::circle() {
	return m_head;
}

/*
if you declare no constructors at all, the compiler writes a zero-argument constructor ("default constructor")

Steps of construction:
1. ------------
2. Construct each data member, consulting the member initialization list. If a member is not listed:
	-if it is of a builtin type, it's left uninitialized
	-if it is of a class type, it's default-constructed (having no default constructor -> error)
		-must initialize class types in step 2 using member-initialization list
3. Execute the body of the constructor

*/


//for an empty string: 1. m_text points to '\0', m_len = 0  <== for this example, we'll use this
//        OR           2. m_text = nullptr, m_len = 0  <== you do more work, but ppl using it will be happy

//Option 1
class String {
public:
	String(const char* text);
	String();
private:
	//Class invariant:
	//  m_text points to a dynamically allocated array of m_len + 1 chars
	//  m_len >= 0
	//  m_len == strlen(m_text)
	char* m_text;
	int m_len;
};


//Option 2
class String {
public:
	String(const char* text);
	String();
private:
	//Class invariant:
	//  EITHER: 
	//    m_text points to a dynamically allocated array of m_len + 1 chars
	//    m_len >= 0
	//    m_len == strlen(m_text)
	//  OR
	//    m_text == nullptr
	//    m_len == 0
	char* m_text;
	int m_len;
};

String::String(const char* text) {
	m_len = strlen(text);
	m_text = new char[m_len + 1]; //dynamically allocated array size does NOT need to be known at compile time
	strcpy(m_text, text); //strcpy(destination, source);

}





