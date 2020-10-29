/**
 * Тумаков М8О-206Б-19
 * 5-ти угольник, 6-ти угольник, 8-и угольник
 */

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <string>

#define PI 3.14159265358979323846
using namespace std;

using Pair = pair<double, double>;

ostream& operator<<(ostream& stream, Pair p) {
    stream << "( " << p.first << ", "<< p.second << " )";
    return stream;
}

istream& operator>>(istream& stream, Pair p) {
    stream >> p.first;
    stream.ignore(1);
    stream >> p.second;
    return stream;
}

class Figure {
public:
    Figure() {
        center = {0, 0};
        side = 0;
        num = 0;
    }
    Figure(Pair a, double b, int n) {
        center = a;
        side = b;
        num = n;
        area = (num * side*side) / (4 * tan( PI / num ));
    }

    void Print_cords() const {
        for(Pair p : cords) {
            cout<<"Apex cords: ";
            cout << p << endl;
        }
    }

    Pair GetCenter() const {
        return center;
    }

    double GetArea() const {
        return area;
    }

protected:
    Pair center = {0, 0};
    double side = 0;
    vector<Pair> cords;
private:
    uint8_t num = 0;
    double area;
};

class Pentagon : public Figure {
public:
    Pentagon() : Figure() {
        Pair apex1 = {0, 0};
        Pair apex2 = {0, 0};
        Pair apex3 = {0, 0};
        Pair apex4 = {0, 0};
        Pair apex5 = {0, 0}; 
    }
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

class Hexagon : public Figure {
public:
    Hexagon() : Figure() {
        Pair apex1 = {0, 0};
        Pair apex2 = {0, 0};
        Pair apex3 = {0, 0};
        Pair apex4 = {0, 0};
        Pair apex5 = {0, 0}; 
        Pair apex6 = {0, 0}; 
    }
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

class Octagon : public Figure {
public:
    Octagon() : Figure() {
        Pair apex1 = {0, 0};
        Pair apex2 = {0, 0};
        Pair apex3 = {0, 0};
        Pair apex4 = {0, 0};
        Pair apex5 = {0, 0}; 
        Pair apex6 = {0, 0};
        Pair apex7 = {0, 0}; 
        Pair apex8 = {0, 0}; 
    }
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

void Print(const Figure& a) {
    cout << "Geom Center: " << a.GetCenter() << endl;
    a.Print_cords();
    cout <<"Area = " << a.GetArea() << endl;
}

int main() {
    vector<Figure> vec;
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        if(s == "ADD") {
            int num;
            double side;
            Pair cen;
            cin >> num >> side >> cen;;
            if (num == 5) {
                vec.push_back(Pentagon(cen, side));
            }
            else if (num == 6) {
                vec.push_back(Hexagon(cen, side));
            }
            else if (num == 8) {
                vec.push_back(Octagon(cen, side));
            }
            else {
                cout << "Wrong number of sides" << endl;
            }
        }
        else if(s == "DEL") {
            if(vec.size() == 0) {
                cout << "Vector is empty";
            }
            int idx;
            cin >> idx;
            vec.erase(vec.begin() + idx);
        }
        else if(s == "PRINT") {
            int idx;
            cin >> idx;
            if(vec.size() == 0) {
                cout << "Vector is empty";
            }
            if(idx >= vec.size()) {
                cout << "Wrong index" << endl;
                continue;
            }
            Print(vec[idx]);
        }
        else if(s == "AREA") {
            double sum;
            if(vec.size() == 0) {
                cout << "Vector is empty";
            }
            for(auto i : vec) {
                sum += i.GetArea();
            }
            cout << "Common Area = " << sum << endl;
        }
        else {
            cout << "Wrong command";
        }
    }
    return 0;
}