
#ifndef VECTEUR_HXX
#define VECTEUR_HXX

#include <string.h>
#include <iostream>
#include <array>
#include <deque>

/**
 * @brief Classe Vecteur
 * 
 */
class Vecteur {
    public:
        std::array<double, 3> vect;
        Vecteur();
        Vecteur(double, double, double);
        Vecteur(const Vecteur &);
        Vecteur operator+ (double);
        Vecteur operator* (double);
        Vecteur operator/ (double);
        Vecteur &operator*= (double);
        Vecteur &operator+= (double);
        Vecteur &operator+= (const Vecteur &);
        Vecteur operator+ (const Vecteur &);
        Vecteur operator- (const Vecteur &);
        Vecteur &operator= (const Vecteur &);
        double &operator()(int );
        double operator()(int ) const ;

        bool equal(const Vecteur &);
        //~Vecteur();
        
};

std::ostream &operator<< (std::ostream &, const Vecteur &);
Vecteur operator*(double, const Vecteur &);
Vecteur operator+(const Vecteur &, const Vecteur &);
Vecteur operator-(const Vecteur &, const Vecteur &);
Vecteur scalaire(const Vecteur &, const Vecteur &);
Vecteur floor(const Vecteur &);
double  distance( const Vecteur &, const Vecteur &);


#endif