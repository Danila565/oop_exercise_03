/**
 * Тумаков М8О-206Б-19
 * Лабораторная работа №3
 * 5-ти угольник, 6-ти угольник, 8-и угольник
 */

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <string>

//Число Пи
#define PI 3.14159265358979323846
using namespace std;
//Сокращение для пары чисел типа double
using Pair = pair<double, double>;
//перегрузка оператора вывода для пары
ostream& operator<<(ostream& stream, Pair p) {
    stream << "( " << p.first << ", "<< p.second << " )";
    return stream;
}
//перегрузка оператора ввода для пары
istream& operator>>(istream& stream, Pair p) {
    stream >> p.first;
    stream.ignore(1);
    stream >> p.second;
    return stream;
}
//Класс Figure
class Figure {
public:
//конструктор по умолчанию
    Figure() {
        center = {0, 0};
        side = 0;
        num = 0;
    }
    //конструктор класса
    Figure(Pair a, double b, int n) {
        center = a;
        side = b;
        num = n;
        area = (num * side*side) / (4 * tan( PI / num ));
    }
    //вывод координат вершин фигуры
    void Print_cords() const {
        for(Pair p : cords) {
            cout<<"Apex cords: ";
            cout << p << endl;
        }
    }
    //получить координаты центра фигуры
    Pair GetCenter() const {
        return center;
    }
    //получить площадь фигуры
    double GetArea() const {
        return area;
    }
protected:
    Pair center = {0, 0};
    double side = 0;
    //вектор координат вершин фигуры
    vector<Pair> cords;
private:
    uint8_t num = 0;
    double area;
};
//Класс пятиугольник
class Pentagon : public Figure {
public:
    Pentagon() : Figure() {}

    Pentagon(Pair a, double b) : Figure(a, b, 5) {
        push_cords();
    }
private:
    void push_cords() {
        double ang = 54 * PI / 180;
        double R = side * sin(ang) / sin(72 * PI / 180);
        cords.push_back({center.first, center.second + R});
        cords.push_back({center.first + R*sin(2*ang), center.second - R*cos(2*ang)});
        cords.push_back({center.first + R*cos(ang), center.second - R*sin(ang)});
        cords.push_back({center.first - R*cos(ang), center.second - R*sin(ang)});
        cords.push_back({center.first - R*sin(2*ang), center.second - R*cos(2*ang)});
    }
};
//класс шестиугольник
class Hexagon : public Figure {
public:
    Hexagon() : Figure() {}

    Hexagon(Pair a, double b) : Figure(a, b, 6) {
        push_cords();
    }
private:
    void push_cords() {
        cords.push_back({center.first - side, center.second});
        cords.push_back({center.first - side/2, center.second + side});
        cords.push_back({center.first + side/2, center.second + side});
        cords.push_back({center.first + side, center.second});
        cords.push_back({center.first - side/2, center.second - side});
        cords.push_back({center.first + side/2, center.second - side});
    }
};
//класс восьмиугольник
class Octagon : public Figure {
public:
    Octagon() : Figure() {}

    Octagon(Pair a, double b) : Figure(a, b, 8) {
        push_cords();
    }
private:
    void push_cords() {
        double h = side / (2 * tan(22.5 * PI / 180));
        cords.push_back({center.first - side/2, center.second - h});
        cords.push_back({center.first + side/2, center.second - h});
        cords.push_back({center.first + h, center.second - side/2});
        cords.push_back({center.first + h, center.second + side/2});
        cords.push_back({center.first + side/2, center.second + h});
        cords.push_back({center.first - side/2, center.second + h});
        cords.push_back({center.first - h, center.second + side/2});
        cords.push_back({center.first - h, center.second - side/2});
    }
};
//вывод  координат центра, координат вершин, площади фигуры
void Print(const Figure& a) {
    cout << "Geom Center: " << a.GetCenter() << endl;
    a.Print_cords();
    cout <<"Area = " << a.GetArea() << endl;
}

int main() {
    vector<Figure> vec;
    string s;
    while(cin >> s) {
        if(s == "ADD") {
            int num;
            double side;
            Pair cen;
            cin >> num >> side >> cen;;
            if (num == 5) {
                vec.push_back(Pentagon(cen, side));
                cout << "Pentagon added" << endl;
            }
            else if (num == 6) {
                vec.push_back(Hexagon(cen, side));
                cout << "Hexagon added" << endl;
            }
            else if (num == 8) {
                vec.push_back(Octagon(cen, side));
                cout << "Octagon added" << endl;
            }
            else {
                cout << "Wrong number of sides" << endl;
            }
        }
        else if(s == "DEL") {
            if(vec.size() == 0) {
                cout << "Vector is empty" << endl;
                continue;
            }
            int idx;
            cin >> idx;
            vec.erase(vec.begin() + idx);
        }
        else if(s == "PRINT") {
            if(vec.size() == 0) {
                cout << "Vector is empty" << endl;
                continue;
            }
            int idx;
            cin >> idx;
            if(idx >= vec.size()) {
                cout << "Wrong index" << endl;
                continue;
            }
            Print(vec[idx]);
        }
        else if(s == "AREA") {
            double sum = 0;
            for(auto i : vec) {
                sum += i.GetArea();
            }
            cout << "Common Area = " << sum << endl;
        }
        else {
            cout << "Wrong command" << endl;
        }
    }
    return 0;
}
