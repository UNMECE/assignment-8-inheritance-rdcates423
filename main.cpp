#include <iostream>
#include <cmath>

const double EPSILON_0 = 8.854e-12;
const double MU_0 = 4 * M_PI * 1e-7;

class Field {
protected:
    double* value;
public:
    Field() {
        value = new double[3];
        value[0] = 0.0;
        value[1] = 0.0;
        value[2] = 0.0;
    }

    Field(double x, double y, double z) {
        value = new double[3];
        value[0] = x;
        value[1] = y;
        value[2] = z;
    }

    Field(const Field& other) {
        value = new double[3];
        value[0] = other.value[0];
        value[1] = other.value[1];
        value[2] = other.value[2];
    }

    virtual ~Field() {
        delete[] value;
    }

    virtual void printMagnitude() {
        std::cout << "Components: (" << value[0] << ", " << value[1] << ", " << value[2] << ")" << std::endl;
    }
};

class Electric_Field : public Field {
private:
    double e_calc;
public:
    Electric_Field() : Field(), e_calc(0.0) {}

    Electric_Field(double x, double y, double z) : Field(x, y, z), e_calc(0.0) {}

    Electric_Field(const Electric_Field& other) : Field(other), e_calc(other.e_calc) {}

    void calculateField(double Q, double r) {
        if (r != 0)
            e_calc = Q / (4 * M_PI * EPSILON_0 * r * r);
        else
            e_calc = 0;
    }

    Electric_Field operator+(const Electric_Field& rhs) {
        return Electric_Field(value[0] + rhs.value[0],
                              value[1] + rhs.value[1],
                              value[2] + rhs.value[2]);
    }

    friend std::ostream& operator<<(std::ostream& os, const Electric_Field& e) {
        os << "(" << e.value[0] << ", " << e.value[1] << ", " << e.value[2] << ")";
        return os;
    }

    void printMagnitude(){
        Field::printMagnitude();
        std::cout << "Calculated Electric Field Magnitude: " << e_calc << std::endl;
    }
};

class Magnetic_Field : public Field {
private:
    double b_calc;
public:
    Magnetic_Field() : Field(), b_calc(0.0) {}

    Magnetic_Field(double x, double y, double z) : Field(x, y, z), b_calc(0.0) {}

    Magnetic_Field(const Magnetic_Field& other) : Field(other), b_calc(other.b_calc) {}

    void calculateField(double I, double r) {
        if (r != 0)
            b_calc = I / (2 * M_PI * r * MU_0);
        else
            b_calc = 0;
    }

    Magnetic_Field operator+(const Magnetic_Field& rhs) {
        return Magnetic_Field(value[0] + rhs.value[0],
                              value[1] + rhs.value[1],
                              value[2] + rhs.value[2]);
    }

    friend std::ostream& operator<<(std::ostream& os, const Magnetic_Field& m) {
        os << "(" << m.value[0] << ", " << m.value[1] << ", " << m.value[2] << ")";
        return os;
    }

    void printMagnitude(){
        Field::printMagnitude();
        std::cout << "Calculated Magnetic Field Magnitude: " << b_calc << std::endl;
    }
};

int main() {
    Electric_Field e1(0, 1e5, 1e3);
    Magnetic_Field m1(0.1, 0.2, 0.3);

    std::cout << "Initial Electric Field:" << std::endl;
    e1.printMagnitude();

    std::cout << "Initial Magnetic Field:" << std::endl;
    m1.printMagnitude();

    e1.calculateField(1e-6, 0.05); // Q = 1 uC, r = 5cm
    m1.calculateField(10, 0.05);  // I = 10 A, r = 5cm

    std::cout << "\nAfter Calculation:" << std::endl;
    e1.printMagnitude();
    m1.printMagnitude();

    Electric_Field e2(1, 2, 3);
    Electric_Field e3 = e1 + e2;
    Magnetic_Field m2(0.5, 0.5, 0.5);
    Magnetic_Field m3 = m1 + m2;

    std::cout << "\nCombined Electric Field: " << e3 << std::endl;
    std::cout << "Combined Magnetic Field: " << m3 << std::endl;

    return 0;
}

