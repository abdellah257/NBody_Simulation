/// Code élémentaire pour le calcul de la trace d'une matrice.
/// Printemps 2022
/// Objectif : manipuler les éléments de base du C++
///            utiliser des outils de profiling et de débogage
/// ref: l'exercice est inspiré très largement de ressources WWW             

#include <cstdlib>
#include <cmath>
#include <iostream>

double phi(double x, double u);
double phi2(double x, double u);
double* eulerexp(double a, double b, int n, double u0, double (*func) (double, double));
void print_matrix(double* matrix , int n);
double* eulerimp(double a, double b, int n, double u0, double (*func) (double, double));

int main()
{
    double u0 = 1.0;
    int n = 1000;

    double* matexp = eulerexp(0., 1., n, u0, *phi);
    print_matrix(matexp, n);
    std::cout << std::endl;
    double* matimp = eulerimp(0., 1., n, u0, *phi);
    print_matrix(matimp, n);

    std::cout << std::endl;

    u0 = 0.0;
    double* matexp1 = eulerexp(0., 2.,n, u0, *phi2);
    print_matrix(matexp1, n);
    std::cout << std::endl;
    double* matimp1 = eulerimp(0., 2., n, u0, *phi2);
    print_matrix(matimp1, n);

    return 0;
}

double phi(double x, double u) {
    return 2*x*u;
}

double phi2(double x, double u) {
    return 50 * u * cos(x);
}

double f(double x, double u0, double h, double xn1, double (*func) (double, double)) {
    return -x + u0 + h * func(xn1, x);
}

static double newton(double a, double b, double u, double epsilon, double (*func) (double, double), double h, double xn1) {
    double x;
    double fa, fb;
    fa = f(a, u, h, xn1, func);
    fb = f(b, u, h, xn1, func);
    x = (fb*a-fa*b)/(fb-fa);
    while((x-b)/x > epsilon || (b-x)/x > epsilon) {
        a = b;
        fa = fb;
        b = x;
        fb = f(b, u, h, xn1, func);
        x = (fb*a-fa*b)/(fb-fa);
    }
    return x;
}

double* eulerexp(double a, double b, int n, double u0, double (*func) (double, double)) {
    double* matrice = (double*) calloc(n+1, sizeof(double*));
    matrice[0] = u0;
    double x = 0.0;
    double pas = (double) (b-a)/n;
    for (int i= 1 ; i< n+1 ; i++) {
        matrice[i] = func(x, matrice[i-1])* pas + matrice[i-1];
        x += pas;
    }
    return matrice;
}

double* eulerimp(double a, double b, int n, double u0, double (*func) (double, double)) {
    double* matrice = (double*) calloc(n+1, sizeof(double*));
    matrice[0] = u0;
    double x = 0.0;
    double pas = (double) (b-a)/n;
    for (int i = 1 ; i< n+1 ; i++) {
        x += pas;
        matrice[i] = newton(0., 3., matrice[i-1], 0.0001, *func, pas, x);
    }
    return matrice;
}

void print_matrix(double* matrix , int n)
{
    int i;
    for (i= 0 ; i< n ; i++)
      std::cout << matrix[i] << ", ";
    std::cout << std::endl;
}