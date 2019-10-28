#include <iostream>
#include <stdexcept>

using namespace std;
class Point
{
public:
	int x, y;

	Point() {
		cout << "Point()" << endl;
		x = 0;
		y = 0;

	};
	Point(int x, int y) {
		cout << "Point(int x, int y)" << endl;
		this->x = x;
		this->y = y;
	};
	Point(Point &point) {
		cout << "Point(Point &point)" << endl;
		x = point.x;
		y = point.y;
	};

	~Point() {
		printf_s("~Point()\t x=%d, y=%d\n", x, y);
	};

	void Offset(int dx, int dy);
};

void Point::Offset(int dx, int dy) {
	x += dx;
	y += dy;
};


class Rectangle {
protected:
	double width, height;
public:
	Point* Location;

	Rectangle() {
		cout << "Rectangle()" << endl;
		Location = new Point();
		width = 0;
		height = 0;
	}

	Rectangle(int width, int height, Point &location) {
		cout << "Rectangle(int x, int y, Point &location)" << endl;
		Location = new Point(location);
		this->width = width;
		this->height = height;
	}

	Rectangle(Rectangle &rectangle) {
		cout << "Rectangle(Rectangle &rectangle)" << endl;
		Location = new Point(*rectangle.Location);
		width = rectangle.width;
		height = rectangle.height;
	}

	double GetHeight() {
		return height;
	}

	double GetWidth() {
		return width;
	}

	void SetHeight(double height) {
		this->height = height;
	}

	void SetWidth(double width) {
		this->width = width;
	}

	double GetArea() {
		return width * height;
	}

	virtual void Resize(double newWidth, double newHeight) {
		SetWidth(newWidth);
		SetHeight(newHeight);
	}

	~Rectangle() {
		printf_s("~Rectangle()\tWidth=%lf, Height=%lf, Location={ %d, %d }\n", width, height, Location->x, Location->y);
		delete Location;
	};
};

class Square : public Rectangle {
public:
	Square() {
		cout << "Square()" << endl;
	}

	Square(int width, Point &location) : Rectangle(width, width, location) {
		cout << "Square(int width, Point &location) : Rectangle(width, width, location)" << endl;
	}

	Square(Square &square) : Rectangle(square) {
		cout << "Square(Square &square) : Rectangle(square)" << endl;
	}

	~Square();
	//если нет деструктора, то просто вызовется конструктор класса-родителя

	virtual void Resize(double newWidth, double newHeight) override {
		if (newWidth != newHeight)
			throw invalid_argument("Высота должна быть равна ширине у квадрата");

		SetWidth(newWidth);
		SetHeight(newWidth);
	}

	virtual void Resize(double newWidth) {
		Resize(newWidth, newWidth);
	}

};

Square::~Square() {
	printf_s("~Square()\tWidth=%lf, Location={ %d, %d }\n", width, Location->x, Location->y);
}


int main()
{
	setlocale(LC_ALL, "Russian");
	cout << "Создаются 3 объекта и уничтожаются " << endl;
	{
		Point p1;
		Point p2(22, 22);
		Point p3(p2);
	} //произойдут вызовы деструктора для p1-p3
	cout << endl;
	cout << "Создаются 3 объекта и уничтожатся вручную" << endl;
	Point* p4 = new Point();
	Point* p5 = new Point(55, 55);
	Point* p6 = new Point(*p5);

	p6->Offset(5, 5);

	delete p4;
	delete p5;
	delete p6;
	cout << endl;
	
	Point location(4, 8);

	cout << endl;
	cout << "Композиция:" << endl;
	
	Square square(5, location);
	square.Location->Offset(6, 2);

	try
	{
		square.Resize(12, 13);
	}
	catch (const std::invalid_argument &e)
	{
		cerr << e.what() << endl;
	}
	

}