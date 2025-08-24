#include<iostream>
using namespace std;

#define DELIMETER "\n-----------------------------\n"
#define FIGURA <<std::string(strchr(typeid(*this).name(), ' ') + 1)

/*
rectangle(Прямоугольник)
Окружность(circle)
Треугольник(triangle)->right triangle (прямоугольный треугольник)
					 ->isosceles triangle (равнобедренный треугольник)
					 ->triangle
*/

enum Color
{
	Red		= 0x000000FF,
	Green	= 0x0000FF00,
	Blue	= 0x00FF0000,
	Yellow	= 0x0000FFFF,
	Orange	= 0x0000A5FF,
	White	= 0x00FFFFFF
};

class Shape
{
	Color color;
public:
	Shape(Color color):color(color){/*тело конструктора*/ }
	//virtual double 
	virtual double get_area()const = 0;
	virtual double get_perimetr()const = 0;
	virtual void draw()const = 0;
	virtual void info()const
	{
		cout << "Площадь " FIGURA <<": " << get_area() << endl;
		cout << "Периметр  " FIGURA << ": " << get_perimetr() << endl;
		cout << endl;
		draw();
	}
};
  /////////////
 // SQUARE ///
/////////////
class Square:public Shape
{ 
	double side_1;
public:
	Square(double side, Color color) :Shape(color)
	{
		set_side(side);
	}
	double get_side()const
	{
		return side_1;
	}
	void set_side(double side)
	{
		this->side_1 =side;
	}
	double get_area()const override
	{
		return side_1 * side_1;
	}
	double get_perimetr()const override
	{
		return 2 * (side_1 +side_1);
	}
	void draw()const override
	{
		setlocale(LC_ALL, "C");
		for (int i = 0; i < side_1; i++)
		{
			for (int j = 0; j < side_1; j++)
			{
				cout << "\xDB\xDB";
			}
			cout << endl;
		}
		setlocale(LC_ALL, "");
	}
void info()const override
{
	cout << "Геометрическая фигура: " FIGURA << endl;
	cout << "Длина стороны " FIGURA << ": " << get_side() << endl;
	Shape::info();
	cout << DELIMETER;
}
};
  /////////////////
 /// RECTANGLE ///
/////////////////
class Rectangle:public Square
{
	double side_1,side_2;
public:
	Rectangle(double side_1, double side_2, Color color) :Square(side_1, color)
	{
		set_side_1(side_1);
		set_side_2(side_2);
	}
	double get_side_1()const
	{
		return side_1;
	}
	double get_side_2()const
	{
		return side_2;
	}
	void set_side_1(double side)
	{
		this->side_1 = side;
	}
	void set_side_2(double side)
	{
		this->side_2 = side;
	}
	double get_area()const override
	{
		return side_1 * side_2;
	}
	double get_perimetr()const override
	{
		return 2 * (side_1+side_2);
	}
	void draw()const override
	{
		setlocale(LC_ALL, "C");
		for (int i = 0; i < side_1; i++)
		{
			for (int j = 0; j < side_2; j++)
			{
				cout << "\xDB\xDB";
			}
			cout << endl;
		}
		setlocale(LC_ALL, "");
	}
	void info()const override
	{
		cout << "Геометрическая фигура: " FIGURA << endl;
		cout << "Длина одной стороны " FIGURA<< ": " << get_side_1() << endl;
		cout << "Длина другой стороны "  FIGURA << ": " << get_side_2() << endl;
		Shape::info();
		cout << DELIMETER;
	}

};
  ////////////////
 /// TRIANGLE ///
///////////////
class Triangle:public Shape
{
	double Leg_1, Leg_2;//катеты
public:
	Triangle(double Leg_1, double Leg_2, Color color) :Shape(color)
	{
		set_Leg_1(Leg_1);
		set_Leg_2(Leg_2);
	}
	double get_Leg_1()const
	{
		return Leg_1;
	}
	double get_Leg_2()const
	{
		return Leg_2;
	}
	void set_Leg_1(double Leg_1)
	{
		this->Leg_1 = Leg_1;
	}
	void set_Leg_2(double Leg_2)
	{
		this->Leg_2 = Leg_2;
	}
	double get_hypotenuse()const
	{
		return sqrt((Leg_1 * Leg_1) + (Leg_2 * Leg_2));
	}
	double get_area()const override
	{
		return (Leg_1 * Leg_2)/2;
	}
	double get_perimetr()const override
	{
		return (Leg_1 + Leg_2 + get_hypotenuse());
	}
	void draw()const override
	{
		for (int i = 0; i < Leg_1; i++)
		{
			for (int j = 0; j < (Leg_2/Leg_1)*i+1; j++)
			{
				cout << "*";
			}
			cout << endl;
		}
	}
	void info()const override
	{
		cout << "Геометрическая фигура: "<< (Leg_1==Leg_2?"Isosceles (равнобедренный) ":"") FIGURA << endl;
		cout << "Длина одного катета " FIGURA << ": " << get_Leg_1() << endl;
		cout << "Длина другого катета "  FIGURA << ": " << get_Leg_2() << endl;
		cout << "Длина гипотенузы "  FIGURA << ": " << get_hypotenuse() << endl;
		Shape::info();
		cout << DELIMETER;
	}
};
  ///////////////
 /// CIRCLLE ///
///////////////
class Circle :public Shape
{
	double radius;
public:
	Circle(double radius, Color color) :Shape(color)
	{
		set_radius(radius);
	}
	void set_radius(double radius)
	{
		this->radius = radius;
	}
	double get_radius()const
	{
		return radius;
	}
	double get_area()const override
	{
		return 3.14159 * radius * radius;
	}
	double get_perimetr()const override
	{
		return 2 * 3.14159 * radius;
	}
	void draw()const override
	{
		setlocale(LC_ALL, "C");
			for (int y = radius; y >= -radius; --y) {
				for (int x = -radius; x <= radius; ++x) {
					if (std::round(std::sqrt(x * x + y * y)) == radius) {
						std::cout << "\xDB\xDB";
					}
					else cout << "  ";
				}
				cout << endl;
			}
		setlocale(LC_ALL, "");
	}
	void info()const override
	{
		cout << "Геометрическая фигура: " FIGURA << endl;
		cout << "Радиус " FIGURA << ": " << get_radius() << endl;
		Shape::info();
		cout << DELIMETER;
	}
};

void main()
{
	setlocale(LC_ALL, "");
	//Shape shape(Color::Red);
	Square square(5,Color::Red);
	/*cout << "Длина стороны квадрата: " << square.get_side() << endl;
	cout << "Площадь квадрата: " << square.get_area() << endl;
	cout << "Периметр квадрата: " << square.get_perimetr() << endl;*/
	//square.draw();
	square.info();

	Rectangle rectangle(5,10,Color::Red);
	rectangle.info();

	Triangle triangle(13, 13, Color::Red);
	triangle.info();

	Circle circle(5, Color::Red);
	circle.info();
}