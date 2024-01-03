// Program Tugas Post Day Modul 3 Online Learning 
// Varel Tiara - 19623183

#include <iostream>
#include <string>
#include <vector>
#include <cmath>

class Matrix {
private:
    int rows;
    int cols;
    std::vector<std::vector<float>> matrix;
public:
    // Constructor yang dapat menerima input dalam bentuk array 2d.
    Matrix(const std::vector<std::vector<float>>& data) : matrix(data) {
        rows = data.size();
        cols = data[0].size();
    }

    // Constructor yang dapat menerima input banyaknya baris dan kolom
    Matrix(int rows, int cols) : rows(rows), cols(cols) {
        matrix = std::vector<std::vector<float>>(rows, std::vector<float>(cols, 0.0));
    }

    // Constructor yang dapat men-copy objek dengan class yang sama
    Matrix(const Matrix& other) : rows(other.rows), cols(other.cols), matrix(other.matrix) {}

    // Operator overloading untuk penjumlahan matrix
    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            std::cout << "The matrix dimension is not valid!\n";
            std::cout << "Return 1 by 1 of zeros matrix\n";
            return Matrix(1,1);
        }

        Matrix hasil(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                hasil.matrix[i][j] = matrix[i][j] + other.matrix[i][j];
            }
        }
        return hasil;
    }

    // Operator overloading untuk pengurangan matrix
    Matrix operator-(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            std::cout << "The matrix dimension is not valid!\n";
            std::cout << "Return 1 by 1 of zeros matrix\n";
            return Matrix(1,1);
        }

        Matrix hasil(rows, cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                hasil.matrix[i][j] = matrix[i][j] - other.matrix[i][j];
            }
        }
        return hasil;
    }

    // Operator overloading untuk perkalian matrix
    Matrix operator*(const Matrix& other) const {
        if (cols != other.rows) {
            std::cout << "Multiplication cannot be done. The number of columns in the first matrix should be equal to the number of rows in the second\n";
            std::cout << '\n';
            std::cout << "Return 1 by 1 of zeros matrix\n";
            std::cout << '\n';
            return Matrix(1,1);
        }

        Matrix hasil(rows, other.cols);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < other.cols; ++j) {
                for (int k = 0; k < cols; ++k) {
                    hasil.matrix[i][j] += matrix[i][k] * other.matrix[k][j];
                }
            }
        }
        return hasil;
    }

    // Menampilkan matrix
    void display() const {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << "\n";
        }
    }
};

class Swerve {
private:
    float r = 0.26363;
    float x, y, theta;
    std::vector<float> wheelVx, wheelVy;
public:
    Swerve(float x_init, float y_init, float theta_init) : x(x_init), y(y_init), theta(theta_init), wheelVx(4), wheelVy(4) {}
    void velocityCommand(float vx, float vy, float omega) {
        // Matriks transformasi
        std::vector<std::vector<double>> transformMatrix = {
            {1, 0, -r * std::sin(M_PI / 4)},
            {0, 1, r * std::cos(M_PI / 4)},
            {1, 0, -r * std::sin(M_PI / 4)},
            {0, 1, r * std::cos(M_PI / 4)},
            {1, 0, -r * std::sin(M_PI / 4)},
            {0, 1, r * std::cos(M_PI / 4)},
            {1, 0, -r * std::sin(M_PI / 4)},
            {0, 1, r * std::cos(M_PI / 4)}
        };
        std::vector<float> velocities = {vx, vy, omega};
        for (int i = 0; i < 4; i++) {
            float resultVx = 0, resultVy = 0;
            for (int j = 0; j < 3; ++j) {
                resultVx += transformMatrix[i * 2][j] * velocities[j];
                resultVy += transformMatrix[i * 2 + 1][j] * velocities[j];
            }
            wheelVx[i] = resultVx;
            wheelVy[i] = resultVy;
        }
    };

    void updatePose(float deltaTime) {
        x += deltaTime * (wheelVx[0] + wheelVx[1] + wheelVx[2] + wheelVx[3]) / 4;
        y += deltaTime * (wheelVy[0] + wheelVy[1] + wheelVy[2] + wheelVy[3]) / 4;
        theta += deltaTime * 0; 
    };

    void displayPosition() {
        std::cout << "Posisi X: " << x << "\n";
        std::cout << "Posisi Y: " << y << "\n";
    }

    float calculateResultantSpeed(int wheelNumber) {
        if (wheelNumber < 1 || wheelNumber > 4) {
            std::cout << "Invalid wheel number!" << "\n";
            return -1;
        }
        int index = wheelNumber - 1;
        float resultSpeed = std::sqrt(std::pow(wheelVx[index], 2) + std::pow(wheelVy[index], 2));
        return resultSpeed;
    }
};

int main() {
    // No 1
    Matrix A({{1, 2, 3}, {2, 3, 1}});
    Matrix B({{0, 2, 4}, {1, 2, 5}, {8, 2, 1.2}});
    Matrix C(2, 3);

    std::cout << "Matrix A\n";
    A.display();
    std::cout << '\n';
    std::cout << "Matrix B\n";
    B.display();
    std::cout << '\n';
    std::cout << "Matrix C\n";
    C.display();
    std::cout << '\n';

    Matrix C1 = A + C;
    std::cout << "Matrix C1\n";
    C1.display();
    std::cout << '\n';

    Matrix C2 = A - C;
    std::cout << "Matrix C2\n";
    C2.display();
    std::cout << '\n';

    Matrix C3 = A * B;
    std::cout << "Matrix C3\n";
    C3.display();
    std::cout << '\n';

    Matrix C4 = B * A;
    std::cout << "Matrix C4\n";
    C4.display();
    std::cout << '\n';

    // No 2 dan 3
    float x_init = 0, y_init = 5, theta_init = 0;
    Swerve robot(x_init, y_init, theta_init);

    for (float t = 0; t <= 6.3; t += 0.01) {
        float vx = 48 * std::cos(t) * std::pow(std::sin(t), 2);
        float vy = 4 * std::sin(4 * t) + 6 * std::sin(3 * t) + 10 * std::sin(2 * t) - 13 * std::sin(t);
        float omega = 0;

        robot.velocityCommand(vx, vy, omega);
        robot.updatePose(0.01);
    }

    robot.displayPosition();

    for (int i = 1; i <= 4; ++i) {
        std::cout << "Resultant speed of wheel " << i << ": " << robot.calculateResultantSpeed(i) << std::endl;
    }
    return 0;
}