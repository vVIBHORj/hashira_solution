#include <bits/stdc++.h>
using namespace std;

// Multiply two polynomials
vector<double> polyMultiply(const vector<double>& A, const vector<double>& B) {
    vector<double> res(A.size() + B.size() - 1, 0.0);
    for (size_t i = 0; i < A.size(); i++) {
        for (size_t j = 0; j < B.size(); j++) {
            res[i + j] += A[i] * B[j];
        }
    }
    return res;
}

// Add two polynomials
vector<double> polyAdd(const vector<double>& A, const vector<double>& B) {
    size_t n = max(A.size(), B.size());
    vector<double> res(n, 0.0);
    for (size_t i = 0; i < A.size(); i++) res[i] += A[i];
    for (size_t i = 0; i < B.size(); i++) res[i] += B[i];
    return res;
}

int main() {
    // Example points (from Test Case 1)
    vector<pair<double,double>> points = {
        {1,4}, {2,7}, {3,12}, {6,39}
    };

    int k = 3; // we only need k points (degree = k-1)
    vector<pair<double,double>> used(points.begin(), points.begin()+k);

    vector<double> poly; // final polynomial coefficients

    // Lagrange interpolation
    for (int i = 0; i < k; i++) {
        double xi = used[i].first, yi = used[i].second;

        // Start with polynomial = {1} (represents constant 1)
        vector<double> Li = {1.0};
        double denom = 1.0;

        for (int j = 0; j < k; j++) {
            if (i == j) continue;
            double xj = used[j].first;

            // Multiply Li by (x - xj)
            vector<double> term = {-xj, 1.0}; // ( -xj + 1*x )
            Li = polyMultiply(Li, term);

            denom *= (xi - xj);
        }

        // Scale Li by yi/denom
        for (auto &coef : Li) coef *= yi / denom;

        // Add to final polynomial
        poly = polyAdd(poly, Li);
    }

    // Print polynomial
    cout << "Polynomial: f(x) = ";
    for (int i = poly.size()-1; i >= 0; i--) {
        if (fabs(poly[i]) < 1e-9) continue; // skip tiny coeffs
        if (i != (int)poly.size()-1 && poly[i] >= 0) cout << "+";
        cout << poly[i];
        if (i > 0) cout << "x";
        if (i > 1) cout << "^" << i;
        cout << " ";
    }
    cout << "\n";

    // Print constant term (secret)
    cout << "Secret (constant term) = " << poly[0] << "\n";

    return 0;
}










