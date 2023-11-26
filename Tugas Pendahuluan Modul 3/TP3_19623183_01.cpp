// Program Tugas Pendahuluan Modul 3 Online Learning
// Varel Tiara - 19623183

#include <iostream>
#include <iomanip>

using namespace std;

class LinearLine {
private:
    float x1, y1, x2, y2;

public:
    LinearLine(float _x1, float _y1, float _x2, float _y2)
        : x1(_x1), y1(_y1), x2(_x2), y2(_y2) {}

    float gradient() {
        return (y2 - y1) / (x2 - x1);
    }

    float y_intercept() {
        float m = gradient();
        return y1 - m * x1;
    }

    void operator+(float a) {
        y1 += a;
        y2 += a;
    }

    void printEquation() {
        float m = gradient();
        float c = y_intercept();

        cout << "y = " << m << "x + " << c << endl;
    }

    void printPoints() {
        cout << fixed << setprecision(0);
        cout << "(x1, y1) = (" << x1 << ", " << y1 << ")" << endl;
        cout << "(x2, y2) = (" << x2 << ", " << y2 << ")" << endl;
    }
};

int main() {
    LinearLine line(1.0f, 8.0f, 2.0f, 3.0f);
    int a = 3;

    cout << "Sehingga didapatkan" << endl;
    line.printPoints();

    cout << "gradient = " << line.gradient() << endl;
    cout << "y_intercept = " << line.y_intercept() << endl;
    cout << "y = ";
    line.printEquation();

    cout << "Setelah digeser sejauh " << a << ", didapatkan persamaan baru:" << endl;
    line + a;
    cout << "y = ";
    line.printEquation();

    return 0;
}

