#include <iostream>
#include <string>

class Figure {
protected:
    int sides_count;
    std::string name;

public:
    Figure(int sides_count, const std::string& name) : sides_count(sides_count), name(name) {}

    virtual void print_info() const {
        std::cout << name << ":\n";
        std::cout << "Количество сторон: " << sides_count << "\n";
    }

    virtual bool check() const {
        return sides_count == 0;
    }

    virtual ~Figure() = default;
};

class Triangle : public Figure {
protected:
    double a, b, c;
    double A, B, C;

public:
    Triangle(double a, double b, double c, double A, double B, double C)
        : Figure(3, "Треугольник"), a(a), b(b), c(c), A(A), B(B), C(C) {}

    void print_info() const override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << "\n";
    }

    bool check() const override {
        return (A + B + C == 180);
    }
};

class RightTriangle : public Triangle {
public:
    RightTriangle(double a, double b, double c, double A, double B)
        : Triangle(a, b, c, A, B, 90) {
        name = "Прямоугольный треугольник";
    }

    bool check() const override {
        return Triangle::check() && (C == 90);
    }
};

class IsoscelesTriangle : public Triangle {
public:
    IsoscelesTriangle(double a, double b, double c, double A, double B, double C)
        : Triangle(a, b, c, A, B, C) {
        name = "Равнобедренный треугольник";
    }

    bool check() const override {
        return Triangle::check() && (a == c) && (A == C);
    }
};

class EquilateralTriangle : public Triangle {
public:
    EquilateralTriangle(double side)
        : Triangle(side, side, side, 60, 60, 60) {
        name = "Равносторонний треугольник";
    }

    bool check() const override {
        return Triangle::check() && (a == b) && (b == c) && (A == 60) && (B == 60) && (C == 60);
    }
};

class Quadrangle : public Figure {
protected:
    double a, b, c, d;
    double A, B, C, D;

public:
    Quadrangle(double a, double b, double c, double d, double A, double B, double C, double D)
        : Figure(4, "Четырёхугольник"), a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) {}

    void print_info() const override {
        Figure::print_info();
        std::cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
        std::cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n";
    }

    bool check() const override {
        return (A + B + C + D == 360);
    }
};

class Rectangle : public Quadrangle {
public:
    Rectangle(double a, double b)
        : Quadrangle(a, b, a, b, 90, 90, 90, 90) {
        name = "Прямоугольник";
    }

    bool check() const override {
        return Quadrangle::check() && (a == c) && (b == d) && (A == 90) && (B == 90) && (C == 90) && (D == 90);
    }
};

class Square : public Quadrangle {
public:
    Square(double side)
        : Quadrangle(side, side, side, side, 90, 90, 90, 90) {
        name = "Квадрат";
    }

    bool check() const override {
        return Quadrangle::check() && (a == b) && (b == c) && (c == d) && (A == 90) && (B == 90) && (C == 90) && (D == 90);
    }
};

class Parallelogram : public Quadrangle {
public:
    Parallelogram(double a, double b, double A, double B)
        : Quadrangle(a, b, a, b, A, B, A, B) {
        name = "Параллелограмм";
    }

    bool check() const override {
        return Quadrangle::check() && (a == c) && (b == d) && (A == C) && (B == D);
    }
};

class Rhombus : public Quadrangle {
public:
    Rhombus(double side, double A, double B)
        : Quadrangle(side, side, side, side, A, B, A, B) {
        name = "Ромб";
    }

    bool check() const override {
        return Quadrangle::check() && (a == b) && (b == c) && (c == d) && (A == C) && (B == D);
    }
};

void print_info(const Figure* fig) {
    fig->print_info();
    if (fig->check()) {
        std::cout << "Правильная\n";
    }
    else {
        std::cout << "Неправильная\n";
    }
}

int main() {
    Figure* figures[] = {
        new Figure(0, "Фигура"),
        new Triangle(10, 20, 30, 50, 60, 70),
        new RightTriangle(10, 20, 30, 50, 40),
        new RightTriangle(10, 20, 30, 50, 40),
        new IsoscelesTriangle(10, 20, 10, 50, 60, 50),
        new EquilateralTriangle(30),
        new Quadrangle(10, 20, 30, 40, 50, 60, 70, 80),
        new Rectangle(10, 20),
        new Square(20),
        new Parallelogram(20, 30, 30, 40),
        new Rhombus(30, 30, 40)
    };

    for (const Figure* fig : figures) {
        print_info(fig);
        std::cout << "\n";
    }

    // Освобождение памяти
    for (Figure* fig : figures) {
        delete fig;
    }

    return 0;
}