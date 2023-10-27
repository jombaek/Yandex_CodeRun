#include <iostream>
#include <cmath>

double* solveQuadraticEquation(double a, double b, double c)
{
    double* result = new double[2];

    if (b == 0 && c == 0)
    {
        result[0] = 0;
        return result;
    }

    if (b == 0 && a != 0 && c != 0)
    {
        double n = -c / a;
        if (n < 0)
            return nullptr;
        result[0] = sqrt(n);
        result[1] = -result[0];
        return result;
    }

    if (a == 0 && b != 0)
    {
        result[0] = -c / b;
        return result;
    }

    double d = b * b - 4 * a * c;

    if (d < 0) {
        return nullptr;
    }

    if (d == 0)
    {
        result[0] = -b / (2 * a);
        return result;
    }

    result[0] = (-b - sqrt(d)) / (2 * a);
    result[1] = (-b + sqrt(d)) / (2 * a);

    return result;
}

int solveSlow(long long k, long long m, int d)
{
    int count = 0;
    long long rest = m;
    long long perDay;

    while (rest >= 0)
    {
        perDay = (d > 5 ? 0 : k);
        count++;
        rest = rest + perDay - count;
        d = d % 7 + 1;
    }

    return count - 1;
}

long long solveFast(long long k, long long m, int d)
{
    if (d > 5 && m < 3)
    {
        if (m == 0) return 0;
        if (d != 7) return solveSlow(k, m, d);
    }

    double a = -24.5;
    double b = 5 * k - 3.5;
    double c = m;
    double* s = solveQuadraticEquation(a, b, c);
    double q = std::max(s[0], s[1]);
    long long numberOfWeek = (long long)q;
    long long result = numberOfWeek * 7 + 1;
    long long perDay;
    double countBeginD = -24.5 * numberOfWeek * numberOfWeek + numberOfWeek * (5 * k - 3.5) + m;
    long long countBegin = (long long)countBeginD;

    for (int i = 1; i <= 7; i++)
    {
        perDay = (d > 5 ? 0 : k);
        countBegin = countBegin + perDay - result;

        if (countBegin < 0)
            break;

        result++;
        d = d % 7 + 1;
    }

    return result - 1;
}

int main()
{
    long long k, m;
    int d;
    std::cin >> k >> m >> d;

    std::cout << solveFast(k, m, d) << "\n";

    return 0;
}
