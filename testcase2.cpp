#include <iostream>
#include <vector>
#include <cmath>
#include <string>

// Function to convert a string number from base `b` to decimal (long double for big numbers)
long double baseToDecimal(const std::string& value, int base) {
    long double result = 0;
    long double power = 1;
    for (int i = value.size() - 1; i >= 0; i--) {
        char ch = value[i];
        int digit;
        if (ch >= '0' && ch <= '9') digit = ch - '0';
        else if (ch >= 'a' && ch <= 'f') digit = 10 + (ch - 'a');
        else if (ch >= 'A' && ch <= 'F') digit = 10 + (ch - 'A');
        else digit = 0; // fallback, can also handle error

        result += digit * power;
        power *= base;
    }
    return result;
}

// Lagrange interpolation to find polynomial coefficients
// Returns coefficients from degree 0 (constant) to degree n (highest)
std::vector<long double> lagrangeInterpolation(const std::vector<long double>& x, const std::vector<long double>& y) {
    int n = x.size();
    std::vector<long double> coeffs(n, 0.0);

    for(int i = 0; i < n; ++i) {
        std::vector<long double> li(n, 0.0);
        li[0] = 1.0;

        long double denom = 1.0;
        for(int j = 0; j < n; ++j) {
            if(j == i) continue;
            denom *= (x[i] - x[j]);
        }

        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            // Multiply polynomial li(x) by (x - x[j])
            for(int d = n-1; d > 0; --d){
                li[d] = li[d] - li[d-1] * x[j];
            }
            li[0] = li * (-x[j]);
        }
        for(int d = 0; d < n; ++d) {
            coeffs[d] += y[i] * li[d] / denom;
        }
    }
    return coeffs;
}

int main() {
    // X values for the second test case
    std::vector<long double> x = {1,2,3,4,5,6,7,8,9,10};
    // Base and encoded y values (from the problem)
    std::vector<std::pair<int,std::string>> encodedY = {
        {6, "13444211440455345511"},
        {15,"aed7015a346d63"},
        {15,"6aeeb69631c227c"},
        {16,"e1b5e05623d881f"},
        {8,"316034514573652620673"},
        {3,"2122212201122002221120200210011020220200"},
        {3,"20120221122211000100210021102001201112121"},
        {6,"20220554335330240002224253"},
        {12,"45153788322a1255483"},
        {7,"1101613130313526312514143"}
    };

    std::vector<long double> y;
    for (auto& p : encodedY) {
        int base = p.first;
        y.push_back(baseToDecimal(p.second, base));
    }

    // Polynomial degree is 6; need 7 points. Use first 7 points for interpolation
    int degree = 6;
    std::vector<long double> x_sub(x.begin(), x.begin() + degree + 1);
    std::vector<long double> y_sub(y.begin(), y.begin() + degree + 1);

    std::vector<long double> coeffs = lagrangeInterpolation(x_sub, y_sub);

    std::cout << "Polynomial coefficients (from degree 0 to degree " << degree << "):\n";
    for(size_t i = 0; i < coeffs.size(); ++i) {
        std::cout << "c" << i << " = " << coeffs[i] << "\n";
    }

    return 0;
}
