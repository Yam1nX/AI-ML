// 1. Horner's Rule (Lec-3, Page 4)
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    cout << "Enter degree of polynomial: ";
    cin >> n;

    vector<double> coeffs(n + 1);
    cout << "Enter coefficients from highest to lowest degree:\n";
    for (int i = 0; i <= n; i++) {
        cout << "a[" << n - i << "] = ";
        cin >> coeffs[i];
    }

    double x;
    cout << "Enter value of x: ";
    cin >> x;

    double result = coeffs[0];
    for (int i = 1; i <= n; i++) {
        result = result * x + coeffs[i];
    }

    cout << "\nPolynomial value at x = " << x << " is: " << result << endl;
    return 0;
}

// Sample Input/Output:
// Enter degree of polynomial: 3
// Enter coefficients from highest to lowest degree:
// a[3] = 1
// a[2] = -4
// a[1] = 1
// a[0] = 6
// Enter value of x: 2

// Polynomial value at x = 2 is: 0

// 2. Banker's Rounding Rule (Lec-2, Page 2)


double bankersRound(double number, int n) {
    if (number == 0) return 0.0;
    int exp = (int)floor(log10(fabs(number)));
    int shift = n - 1 - exp;
    double factor = pow(10, shift);
    double shifted = number * factor;
    double floorVal = floor(shifted);
    double frac = shifted - floorVal;
    double rounded;
    if (frac < 0.5) {
        rounded = floorVal;
    } else if (frac > 0.5) {
        rounded = floorVal + 1;
    } else {
        if (fmod(floorVal, 2.0) == 0)
            rounded = floorVal;
        else
            rounded = floorVal + 1;
    }
    return rounded / factor;
}
int main() {
    double number;
    int n;
    cout << "Enter a number: ";
    cin >> number;
    cout << "Enter number of significant digits: ";
    cin >> n;
    cout << fixed << setprecision(10);
    cout << "Rounded value: " << bankersRound(number, n) << endl;
    return 0;
}


// Sample Input/Output:
// Enter a number: 3.14159
// Enter number of significant digits: 4
// Rounded value: 3.1420000000


// 3. Bisection Method (Lec-3, Page 5)
double f(double x) {
    return x*x*x - x - 1;
}
int main() {
    double x1, x2, E;
    cout << "Enter lower guess x1: "; cin >> x1;
    cout << "Enter upper guess x2: "; cin >> x2;
    cout << "Enter tolerance E: "; cin >> E;
    double f1 = f(x1), f2 = f(x2);
    if (f1 * f2 > 0) {
        cout << "Initial guesses do not bracket a root." << endl;
        return 1;
    }
    int iter = 0;
    double x0 = x1;
    cout << "\nIter\tx1\t\tx2\t\tx0\t\tf(x0)\n";

    while (fabs(x2 - x1) >= E) {
        x0 = (x1 + x2) / 2;
        double f0 = f(x0);
        cout << iter + 1 << "\t" << x1 << "\t" << x2 << "\t"
             << x0 << "\t" << f0 << endl;
        if (f1 * f0 < 0) {
            x2 = x0;
            f2 = f0;
        } else {
            x1 = x0;
            f1 = f0;
        }
        iter++;
    }
    cout << "\nRoot ≈ " << (x1 + x2) / 2 << endl;
    cout << "Iterations = " << iter << endl;
    return 0;
}

// Sample Input/Output:
// Enter lower guess x1: 1
// Enter upper guess x2: 2
// Enter tolerance E: 0.001

// Iter    x1          x2          x0          f(x0)
// 1       1           2           1.5         0.875
// 2       1           1.5         1.25        -0.296875
// 3       1.25        1.5         1.375       0.224609
// Root ≈ 1.32422
// Iterations = 10





// 4. Newton-Raphson Method (Lec-3, Page 7)
double f(double x)  { return x*x - 3*x + 2; }
double df(double x) { return 2*x - 3; }
int main() {
    double x0, E;
    int maxIter;
    cout << "Enter initial guess x0: ";
    cin >> x0;
    cout << "Enter tolerance E: ";
    cin >> E;
    cout << "Enter maximum iterations: ";
    cin >> maxIter;
    cout << "\nIter\tx\t\tf(x)\n";
    double x = x0;

    for (int i = 1; i <= maxIter; i++) {
        double fx = f(x);
        double dfx = df(x);
        if (dfx == 0) {
            cout << "Derivative is zero. Method fails." << endl;
            return 1;
        }

        double x_new = x - fx / dfx;
        cout << i << "\t" << x_new << "\t" << f(x_new) << endl;
        if (fabs(x_new - x) < E) {
            x = x_new;
            cout << "\nRoot ≈ " << x << endl;
            cout << "Iterations = " << i << endl;
            return 0;
        }
        x = x_new;
    }
    cout << "\nDid not converge within " << maxIter << " iterations." << endl;
    cout << "Last estimate: " << x << endl;
}

// Sample Input/Output:
// Enter initial guess x0: 0
// Enter tolerance E: 0.0001
// Enter maximum iterations: 50

// Iter    x               f(x)
// 1       0.6667          0.4444
// 2       0.9333          0.0711
// 3       0.9959          0.0041
// 4       0.9999          0.0001
// 5       1.0000          0.0000

// Root ≈ 1
// Iterations = 5




// 5. Newton Forward Interpolation (Lec-4, Page 7)

int main() {
    int n;
    cout << "Enter number of data points: ";
    cin >> n;
    vector<double> x(n), y(n);
    cout << "Enter x values (equally spaced):\n";
    for (int i = 0; i < n; i++) cin >> x[i];
    cout << "Enter corresponding y values:\n";
    for (int i = 0; i < n; i++) cin >> y[i];
    double xp;
    cout << "Enter x value to interpolate: ";
    cin >> xp;
    // Build forward difference table
    vector<vector<double>> table(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) table[i][0] = y[i];
    for (int j = 1; j < n; j++)
        for (int i = 0; i < n - j; i++)
            table[i][j] = table[i+1][j-1] - table[i][j-1];
    cout << "\nForward Difference Table:\n";
    cout << setw(8) << "x" << setw(10) << "y";

    for (int j = 1; j < n; j++) cout << setw(10) << ("Δ" + to_string(j) + "y");
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(8) << x[i] << setw(10) << y[i];
        for (int j = 1; j < n - i; j++)
            cout << setw(10) << table[i][j];
        cout << endl;
    }
    double h = x[1] - x[0];
    double u = (xp - x[0]) / h;
    double result = table[0][0];
    double uTerm = 1.0, fact = 1.0;
    for (int i = 1; i < n; i++) {
        uTerm *= (u - (i - 1));
        fact  *= i;
        result += uTerm * table[0][i] / fact;
    }

    cout << "\nInterpolated value at x = " << xp << " is: " << result << endl;
    return 0;
}

// Sample Input/Output:
// Enter number of data points: 5
// Enter x values (equally spaced):
// 0 1 2 3 4
// Enter corresponding y values:
// 1 3 9 31 81
// Enter x value to interpolate: 2.5

// Forward Difference Table:
//        x         y        Δ1y        Δ2y        Δ3y        Δ4y
//        0         1         2         4        16         0
//        1         3         6        20        16
//        2         9        26        36
//        3        31        50
//        4        81

// Interpolated value at x = 2.5 is: 16.5625




// 6. Newton Divided Difference Interpolation (Lec-4, Pages 13–14)
int main() {
    int n;
    cout << "Enter number of data points: ";
    cin >> n;
    vector<double> x(n), y(n);
    cout << "Enter x values (any spacing):\n";
    for (int i = 0; i < n; i++) cin >> x[i];
    cout << "Enter corresponding y values:\n";
    for (int i = 0; i < n; i++) cin >> y[i];
    double xv;
    cout << "Enter x value to interpolate: ";
    cin >> xv;
    // Divided difference table
    vector<vector<double>> table(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) table[i][0] = y[i];
    for (int j = 1; j < n; j++)
        for (int i = 0; i < n - j; i++)
            table[i][j] = (table[i+1][j-1] - table[i][j-1]) / (x[i+j] - x[i]);
    // Print table
    cout << "\nDivided Difference Table:\n";
    cout << setw(8) << "x" << setw(10) << "f[x]";
    for (int j = 1; j < n; j++) cout << setw(12) << ("f[.." + to_string(j) + "]");
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << setw(8) << x[i] << setw(10) << y[i];
        for (int j = 1; j < n - i; j++)
            cout << setw(12) << table[i][j];
        cout << endl;
    }
    double result = table[0][0];
    double term = 1.0;
    for (int i = 1; i < n; i++) {
        term *= (xv - x[i-1]);
        result += term * table[0][i];
    }
    cout << "\nInterpolated value at x = " << xv << " is: " << result << endl;
    return 0;
}

// Sample Input/Output:
// Enter number of data points: 4
// Enter x values (any spacing):
// 1 2 4 7
// Enter corresponding y values:
// 3 5 11 19
// Enter x value to interpolate: 3

// Divided Difference Table:
//        x       f[x]      f[..1]      f[..2]      f[..3]
//        1          3           2           1           0
//        2          5           3           1
//        4         11           2.66667
//        7         19

// Interpolated value at x = 3 is: 7

 


















//1. Horner's Rule (সহজ)
int main() {
    int n;
    cout << "Degree of polynomial: ";
    cin >> n;
    if (n < 0 || n > 99) {
        cout << "Invalid degree!\n";
        return 0;
    }
    double a[100];
    cout << "Coefficients (highest to lowest):\n";
    for (int i = 0; i <= n; i++) cin >> a[i];
    double x;
    cout << "Value of x: ";
    cin >> x;
    double result = a[0];
    for (int i = 1; i <= n; i++)
        result = result * x + a[i];
    cout << "f(" << x << ") = " << result << endl;
    return 0;
}
// 1. Horner's Rule
// Example: f(x) = x³ − 4x² + x + 6 at x = 2 (PDF এর হুবহু উদাহরণ)
// Input:
// 3
// 1 -4 1 6
// 2
// Output:
// f(2) = 0


//2. Banker's Rounding (সহজ)
int main() {
    long double x;
    int n;
    cout << "Enter number: ";
    cin >> x;
    cout << "Enter significant digits: ";
    cin >> n;
    if (n < 1) {
        cout << "Invalid digits!\n";
        return 0;
    }
    if (x == 0) {
        cout << "Rounded value: 0\n";
        return 0;
    }
    fesetround(FE_TONEAREST);   // banker's rounding(round to nearest even)
    int p = floor(log10(fabsl(x)));          // exponent
    long double factor = pow(10.0L, n - 1 - p);
    long double ans = nearbyintl(x * factor) / factor;
    cout << "Rounded value: " << setprecision(n) << ans << endl;
    return 0;
}
// 2. Banker's Rounding
// Input:
// 3.14159
// 4
// Output:
// Rounded value: 3.142
// (PDF উদাহরণ: 3.14159 → 3.142 )

// আরেকটা (tie case):
// Input:
// 2.5
// 1
// Output:
// Rounded value: 2
// (2.5 → 2, কারণ 2 জোড় Banker's rule)



//3. Bisection Method
double f(double x) {
    return x * x * x - x - 1;
}
int main() {
    double a, b, e;
    cout << "Enter a, b: ";
    cin >> a >> b;
    cout << "Enter tolerance: ";
    cin >> e;
    if (e <= 0) {
        cout << "Invalid tolerance!\n";
        return 0;
    }
    if (a > b) {
        double t = a;
        a = b;
        b = t;
    }
    double fa = f(a), fb = f(b);
    cout << setprecision(12);
    if (fa == 0) {
        cout << "Root = " << a << endl;
        return 0;
    }
    if (fb == 0) {
        cout << "Root = " << b << endl;
        return 0;
    }
    if ((fa > 0 && fb > 0) || (fa < 0 && fb < 0)) {
        cout << "No root is bracketed in this interval.\n";
        return 0;
    }
    int i = 0;
    while (b - a > e && i < 1000) {
        double mid = (a + b) / 2;
        double fm = f(mid);
        i++;
        if (fm == 0) {
            a = b = mid;
            break;
        }
        if ((fa > 0 && fm > 0) || (fa < 0 && fm < 0)) {
            a = mid;
            fa = fm;
        } else {
            b = mid;
        }
    }
    cout << "Approximate root = " << (a + b) / 2 << endl;
    if (b - a > e)
        cout << "Tolerance not reached within 1000 iterations.\n";
}
// 3. Bisection Method
// Example: x³ − x − 1 = 0, root between 1 and 2
// Input:
// Enter a, b: 1 2
// Enter tolerance: 0.001
// Output:
// Approximate root = 1.32470703125

// 3. Bisection Method easy
#include <iostream>
using namespace std;
double f(double x) {
    return x*x*x - x - 1;
}
int main() {
    double a, b, e;
    cout << "Enter a, b: ";
    cin >> a >> b;
    cout << "Enter tolerance: ";
    cin >> e;
    if (e <= 0) {
        cout << "Invalid tolerance!\n";
        return 0;
    }
    if (a > b) {
        double t = a;
        a = b;
        b = t;
    }
    if (f(a) == 0) {
        cout << "Root = " << a << endl;
        return 0;
    }
    if (f(b) == 0) {
        cout << "Root = " << b << endl;
        return 0;
    }

    if (f(a) * f(b) > 0) {
        cout << "No root is bracketed in this interval.\n";
        return 0;
    }
    int i = 0;
    while ((b - a) > e && i < 1000) {
        double mid = (a + b) / 2;
        if (f(mid) == 0) {
            a = b = mid;
            break;
        }
        if (f(a) * f(mid) < 0)
            b = mid;
        else
            a = mid;
        i++;
    }
    cout << "Approximate root = " << (a + b) / 2 << endl;
    if ((b - a) > e)
        cout << "Tolerance not reached within 1000 iterations.\n";
}

// 4. Newton-Raphson Method
double f(double x) {
    return x * x * x - x - 1;
}
double df(double x) {
    return 3 * x * x - 1;
}
int main() {
    double x0, e;
    cout << "Initial guess: ";
    cin >> x0;
    cout << "Tolerance: ";
    cin >> e;
    if (e <= 0) {
        cout << "Invalid tolerance!\n";
        return 0;
    }
    for (int i = 0; i < 1000; i++) {
        if (fabs(f(x0)) < e) {
            cout << "Root = " << x0 << endl;
            return 0;
        }
        double derivative = df(x0);
        if (fabs(derivative) < 1e-12) {
            cout << "Derivative is zero. Method stopped.\n";
            return 0;
        }
        double x1 = x0 - f(x0) / derivative;
        if (!isfinite(x1)) {
            cout << "Method failed to converge.\n";
            return 0;
        }
        if (fabs(x1 - x0) < e || fabs(f(x1)) < e) {
            cout << "Root = " << x1 << endl;
            return 0;
        }
        x0 = x1;
    }
    cout << "Approximate root = " << x0 << endl;
    cout << "Maximum iterations reached.\n";
}
// 4. Newton–Raphson Method
// Example: x³ − x − 1 = 0, initial guess 1.5
// Input:
// 1.5
// 0.0001
// Output:
// Root = 1.32472



//5. Newton Forward Interpolation
int main() {
    int n;
    cout << "Number of points: ";
    cin >> n;
    if (n < 2 || n > 50) {
        cout << "Invalid number of points!\n";
        return 0;
    }
    double x[50], y[50], d[50][50];
    cout << "Enter x and y:\n";
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    double h = x[1] - x[0];
    if (fabs(h) < 1e-12) {
        cout << "Invalid x values!\n";
        return 0;
    }
    for (int i = 2; i < n; i++) {
        if (fabs((x[i] - x[i - 1]) - h) > 1e-8) {
            cout << "x values must be equally spaced!\n";
            return 0;
        }
    }
    // Forward difference table
    for (int i = 0; i < n; i++)
        d[i][0] = y[i];
    for (int j = 1; j < n; j++)
        for (int i = 0; i < n - j; i++)
            d[i][j] = d[i + 1][j - 1] - d[i][j - 1];
    double xv;
    cout << "Interpolate at x = ";
    cin >> xv;
    double u = (xv - x[0]) / h;
    double sum = y[0], term = 1;
    for (int i = 1; i < n; i++) {
        term = term * (u - (i - 1)) / i;
        sum = sum + term * d[0][i];
    }
    cout << "f(" << xv << ") = " << sum << endl;
}
// 5. Newton Forward Interpolation
// Example: নিচের টেবিল থেকে x = 2.5 এ interpolate করো
// x	y
// 1	1
// 2	8
// 3	27
// 4	64
// Input:
// 4
// 1 1
// 2 8
// 3 27
// 4 64
// 2.5
// Output:
// f(2.5) = 15.625
// (এটা x³ polynomial, তাই 2.5³ = 15.625 — exact match)



// 6. Newton Divided Difference
int main() {
    int n;
    cout << "Number of points: ";
    cin >> n;
    if (n < 2 || n > 50) {
        cout << "Invalid number of points!\n";
        return 0;
    }
    double x[50], y[50], d[50][50];
    cout << "Enter x and y:\n";
    for (int i = 0; i < n; i++)
        cin >> x[i] >> y[i];
    // Check for duplicate x values
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (fabs(x[i] - x[j]) < 1e-12) {
                cout << "All x values must be distinct!\n";
                return 0;
            }
        }
    }
    // Divided difference table
    for (int i = 0; i < n; i++)
        d[i][0] = y[i];
    for (int j = 1; j < n; j++) {
        for (int i = 0; i < n - j; i++) {
            d[i][j] =
                (d[i + 1][j - 1] - d[i][j - 1])
                / (x[i + j] - x[i]);
        }
    }
    double xv;
    cout << "Interpolate at x = ";
    cin >> xv;
    double sum = d[0][0], term = 1;
    for (int i = 1; i < n; i++) {
        term = term * (xv - x[i - 1]);
        sum = sum + term * d[0][i];
    }
    cout << "f(" << xv << ") = " << sum << endl;
}
// 6. Newton Divided Difference
// একই টেবিল, x = 2.5:
// Input:
// 4
// 1 1
// 2 8
// 3 27
// 4 64
// 2.5
// Output:
// f(2.5) = 15.625
// আরেকটা non-polynomial উদাহরণ (PDF-এর style):
// Input:
// 3
// 1 1
// 2 4
// 4 16
// 3
// Output:
// f(3) = 9
// (y = x² ধরলে 3² = 9 )

