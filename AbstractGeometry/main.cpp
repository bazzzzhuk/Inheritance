#include<iostream>
#include<Windows.h>
#include<conio.h>

using namespace std;

#define DELIMETER "-----------------------------\n"

namespace Geometry
{
	enum Color
	{
		Red = 0x000000FF,
		Green = 0x0000FF00,
		Blue = 0x00FF0000,
		Yellow = 0x0000FFFF,
		Orange = 0x0000A5FF,
		White = 0x00FFFFFF
	};
#define SHAPE_TAKE_PARAMETERS int start_x, int start_y, int line_width,	Color color
#define SHAPE_GIVE_PARAMETERS start_x, start_y, line_width, color

	class Shape
	{
	protected:
		Color color;
		int start_x;
		int start_y;
		int line_width;
	public:
		static const int MIN_START_X = 100;
		static const int MIN_START_Y = 100;
		static const int MAX_START_X = 2000;
		static const int MAX_START_Y = 2000;
		static const int MIN_LINE_WIDTH = 1;
		static const int MAX_LINE_WIDTH = 16;
		static const int MIN_SIZE = 32;
		static const int MAX_SIZE = 768;

		Shape(SHAPE_TAKE_PARAMETERS) :color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);

		}
		void set_start_x(int start_x)
		{
			this->start_x =
				start_x < MIN_START_X ? MIN_START_X :
				start_x>MAX_START_X ? MAX_START_X :
				start_x;
		}
		void set_start_y(int start_y)
		{
			this->start_y =
				start_y < MIN_START_Y ? MIN_START_Y :
				start_y > MAX_START_Y ? MAX_START_Y :
				start_y;
		}
		void set_line_width(int line_width)
		{
			this->line_width =
				line_width < MIN_LINE_WIDTH ? MIN_LINE_WIDTH :
				line_width > MAX_LINE_WIDTH ? MAX_LINE_WIDTH :
				line_width;
		}
		int get_start_x()const
		{
			return start_x;
		}
		int get_start_y()const
		{
			return start_y;
		}
		int get_line_width()const
		{
			return line_width;
		}

		virtual double get_area()const = 0;
		virtual double get_perimetr()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			// << "Длина стороны квадрата: " << get_side() << endl;
			cout << "Площадь квадрата: " << get_area() << endl;
			cout << "Периметр квадрата: " << get_perimetr() << endl;
			cout << DELIMETER;
			draw();

		}
	};
	/*class Square :public Shape
	{
		double side;
	public:
		Square(double side, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		double get_side()const
		{
			return side;
		}
		void set_side(double side)
		{
			this->side = side;
		}
		double get_area()const override
		{
			return side * side;
		}
		double get_perimetr()const override
		{
			return 4 * side;
		}
		void draw()const override
		{
			for (int i = 0; i < side; i++)
			{
				for (int j = 0; j < side; j++)
				{
					cout << "* ";
				}
				cout << endl;
			}
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Длина стороны квадрата: " << get_side() << endl;
			Shape::info();
		}
	};*/
	class Rectangle : public Shape
	{
	protected:
		double width;
		double height;
	public:
		Rectangle(double width, double height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS)
		{
			set_width(width);
			set_height(height);
		}
		void set_width(double width)
		{
			this->width = width;
		}
		void set_height(double height)
		{
			this->height = height;
		}
		double get_width()const
		{
			return width;
		}
		double get_height()const
		{
			return height;
		}
		double get_area()const override
		{
			return width * height;
		}
		double get_perimetr()const override
		{
			return (width + height) * 2;
		}
		void draw()const override
		{
			//Получаем окно консоли
			HWND hwnd = GetConsoleWindow();
			//Получаем контекст устройства (DC - Device Context)для окна консоли
			HDC hdc = GetDC(hwnd);//DC - Это то, на чем мы будем рисовать

			//Создадим инструменты которыми будем рисовать:
			HPEN hPen = CreatePen(PS_SOLID, 5, color);//PEN карандаш рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color);//Рисует заливку фигуры
			//Выберем созданные инструменты:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//После того все необходимые инструменты созданы и выбраны
			//можно рисовать:
			::Rectangle(hdc, start_x, start_y, start_x+width, start_y+height);

			//hdc, hPen & hBrush занимают ресурсы, а ресурсы надо освобождать:
			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);

		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Стороны: " << width << "x" << height << endl;
			Shape::info();
		}
	};
	class Square :public Rectangle
	{
	protected:
		int side;
	public:
		Square(int side, SHAPE_TAKE_PARAMETERS) :Rectangle(side,side,SHAPE_GIVE_PARAMETERS)
		{
			set_side(side);
		}
		void set_side(int side)
		{
			this->side = side;
		}
		int get_side()const
		{
			return side;
		}
	};
	class Circle : public Shape
	{
	protected:
		int width;
		int height;
	public:
		Circle(int width, int height, SHAPE_TAKE_PARAMETERS) :Shape(SHAPE_GIVE_PARAMETERS) 
		{
				set_width(width);
				set_height(height);
		}
		void set_width(double width)
		{
			this->width = width;
		}
		void set_height(double height)
		{
			this->height = height;
		}
		int get_width()const
		{
			return width;
		}
		int get_height()const
		{
			return height;
		}
		void draw()const override
		{
			HWND hwnd = GetConsoleWindow();
			//Получаем контекст устройства (DC - Device Context)для окна консоли
			HDC hdc = GetDC(hwnd);//DC - Это то, на чем мы будем рисовать

			//Создадим инструменты которыми будем рисовать:
			HPEN hPen = CreatePen(PS_SOLID, 5, color);//PEN карандаш рисует контур фигуры
			HBRUSH hBrush = CreateSolidBrush(color);//Рисует заливку фигуры
			//Выберем созданные инструменты:
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			//После того все необходимые инструменты созданы и выбраны
			//можно рисовать:
			::Ellipse(hdc, start_x, start_y, start_x + width, start_y + height);
			//hdc, hPen & hBrush занимают ресурсы, а ресурсы надо освобождать:
			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void jump()const
		{
			while (true)
			{
				for (int i = height+25; i < height+367; i = i + ((i / 40)))
				{
					Geometry::Circle circ(width, height, start_x, i, 2, Geometry::Color::Orange);
					circ.draw();
					Sleep(2);
					system("cls");

					cout << "1";
				}
				for (int i = 10; i < 150; i += 20)
				{
					Geometry::Circle circ(width, height - i, start_x, 700 + i + i, 2, Geometry::Color::Orange);
					circ.draw();
					Sleep(2);
					system("cls");
					cout << "2";
				}

				for (int i = 700; i > 300; i = i - ((i / 110) * (i / 110)))
				{
					Geometry::Circle circ(width, height, start_x, i, 2, Geometry::Color::Orange);
					circ.draw();
					Sleep(2);
					system("cls");
					cout << "3";
				}
				for (int i = 0; i < 5; i++)
				{
					Geometry::Circle circ(width, height, start_x, 308 + i * i, 2, Geometry::Color::Orange);
					circ.draw();
					Sleep(1);
					system("cls");
					cout << "5";
				}
			}
		}
		double get_area()const override
		{
			return width * width*3.14159;
		}
		double get_perimetr()const override
		{
			return 2 * 3.14159*width;
		}
		void info()const override
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус: " << width <<  endl;
			Shape::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "");
	////Shape shape(Color::Red);
	//cout << "Длина стороны квадрата: " << square.get_side() << endl;
	//cout << "Площадь квадрата: " << square.get_area() << endl;
	//cout << "Периметр квадрата: " << square.get_perimetr() << endl;
	//cout << DELIMETER;
	//Geometry::square.draw();
	Geometry::Square square(50,100,300,5, Geometry::Color::Red);
	square.info();
	Geometry::Rectangle rect(150, 100,550,100,2, Geometry::Color::Green);
	rect.info();
	Geometry::Circle circ(300, 300, 200, 300, 2, Geometry::Color::Orange);
	circ.info();
	cout << "НАЖМИТЕ ЛЮБУЮ КЛАВИШУ, ЧТОБЫ МЯЧИК ЗАПРЫГАЛ!" << endl;
	_getch();
	circ.jump();

}