#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

int main() {
    int n;
    double eps;
    ifstream f("matrix.txt");
    f >> n;
    f >> eps;
  //  double om;
  //  cin >>om;
    double **a = new double *[n+1]; //Выделяем память под строки
    for (int i = 1; i <= n; i++)
        a[i] = new double[n+1];     //Под столбцы
    double b[n + 1];
    double x[n + 1];
    cout << "Matrix A: " << endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            f >> a[i][j];
            cout << a[i][j] << ' ';
        }
        f >> b[i];
        cout << b[i] <<endl;
        x[i] = b[i]/ a[i][i];
    }
    f.close();

    double NextX[n + 1];
    int k = 0;
    double norm = 0;
    do {
        for (int i = 1; i <= n; ++i) {
            double sum = 0;
            for (int j = 1; j <= n; ++j) {
                if (i != j) {
                    sum = sum + a[i][j] * x[j];
                }
            }
            NextX[i] = (b[i] - sum) / a[i][i];
        }

        norm = fabs(NextX[1] - x[1]);
        for (int i = 1; i <= n; ++i) {
            if (fabs(NextX[i] - x[i]) > norm) {
                norm = fabs(NextX[i] - x[i]);
            }
            x[i] = NextX[i];
        }
        k++;
    } while (norm > eps);

    cout << "Iteration count: " << k << endl << "eps: " << eps << endl;

    for (int i = 1; i <= n; ++i){
        for (int j = 1; j <= n; ++j) {
            b[i] = b[i] - a[i][j] * x[j];
        }

        if (norm < fabs(b[i])) {
            norm = fabs(b[i]);
        }
    }
    cout << "Residual= " << norm << endl;

    //Выводим решения
    ofstream out ("answer.txt");
    cout <<endl <<"Answer" <<endl;
    for (int i = 1; i <= n; i++) {
        cout << setprecision(10) << fixed << x[i] << " ";
        out << x[i] << ' ';
    }
    out.close();
    return 0;
}