#include <iostream>
#include <omp.h>
#include <cstdlib>

using namespace std;

double f(double x)
{
    return log(1 + x) / x;
}

double simpson(double a, double b, int n, double& time_pr)
{
    double integral = f(a) + f(b), h = (b - a) / (2 * n);

    double start = omp_get_wtime();
#pragma omp parallel for reduction(+:integral)
    {
        for (int i = 1; i < 2 * n; i++)
        {
            if (i % 2 == 0)
                integral += 2 * f(a + i * h);
            else
                integral += 4 * f(a + i * h);
        }
    }
    double end = omp_get_wtime();

    time_pr = end - start;

    integral *= h / 3;

    return integral;
}

int main()
{
    int threadNum;
    cout << "Thread num: ";
    cin >> threadNum;

    omp_set_num_threads(threadNum);

    double a = 0.1, b = 1, end_time = 0;
    int n = 10000000;

    double integral = simpson(a, b, n, end_time);

    cout << "\nIntegral: " << integral << endl;
    cout << "Time: " << end_time;
}
