
#include "vecteur.hxx"
#include <deque>
#include <cmath>

/**
 * @brief Contructeur par defaut donne le vecteur nulle.
 * 
 */
Vecteur::Vecteur(){
    vect = {0, 0, 0};
}
/**
 * @brief Contructeur d'un vecteur initialise par les valeurs en arguments.
 * 
 * @param x     composant x
 * @param y     composant y
 * @param z     composant z
 */
Vecteur::Vecteur(double x, double y, double z) {
    vect = {x, y, z};
}
/**
 * @brief Constructeur d'un vecteur a partir d'un vecteur.
 * 
 * @param vecteur     un vecteur.
 */
Vecteur::Vecteur(const Vecteur & vecteur) {
    vect = {vecteur.vect[0], vecteur.vect[1], vecteur.vect[2]};
}

Vecteur Vecteur::operator+ (double d) {
    return Vecteur(d+vect[0], d+vect[1], d+vect[2]);
}

Vecteur Vecteur::operator+ (const Vecteur & v) {
    return Vecteur(vect[0]+v.vect[0], vect[1]+v.vect[1], vect[2]+v.vect[2]);
}

Vecteur Vecteur::operator- (const Vecteur & v) {
    return Vecteur(vect[0]-v.vect[0], vect[1]-v.vect[1], vect[2]-v.vect[2]);
}

Vecteur Vecteur::operator* (double d) {
    return Vecteur(d*vect[0], d*vect[1], d*vect[2]);
}

Vecteur Vecteur::operator/ (double d) {
    return Vecteur(vect[0]/d, vect[1]/d, vect[2]/d);
}

Vecteur &Vecteur::operator*=  (double val) {
    for (int i=0; i<3; i++)
        vect[i] *= val;
    return *this;
}

Vecteur &Vecteur::operator+=  (double val) {
    for (int i=0; i<3; i++)
        vect[i] += val;
    return *this;
}

Vecteur &Vecteur::operator=(const Vecteur & v) {
    for (int i=0; i<3; i++)
        vect[i] = v.vect[i];
    return *this;
}

Vecteur &Vecteur::operator+=  (const Vecteur &v) {
    for (int i=0; i<3; i++)
        vect[i] += v.vect[i];
    return *this;
}

double &Vecteur::operator()(int k){
    return vect[k];
}

double Vecteur::operator()(int k) const {
    return vect[k];
}

std::ostream &operator<< (std::ostream &out, const Vecteur &vecteur) {
    for(auto d:vecteur.vect){
        out<<d<<" ";
    }
    return out;
}

Vecteur operator+(const Vecteur &v1, const Vecteur &v2){
  return Vecteur(v1.vect[0] + v2.vect[0], v1.vect[1] + v2.vect[1], v1.vect[2] + v2.vect[2]);
}

Vecteur operator*(double d, const Vecteur &v){
  return Vecteur(d * v.vect[0], d * v.vect[1], d * v.vect[2]);
}

Vecteur operator-(const Vecteur &v1, const Vecteur &v2){
  return Vecteur(v1.vect[0] - v2.vect[0], v1.vect[1] - v2.vect[1], v1.vect[2] - v2.vect[2]);
}

/**
 * @brief Teste si le vecteur est egal au vecteur en argument
 * 
 * @param v     un vecteur
 */
bool Vecteur::equal(const Vecteur &v){
    if ((vect[0]==v.vect[0]) &&
        (vect[1]==v.vect[1]) &&
        (vect[2]==v.vect[2]))
        return true;
    return false;
}
/**
 * @brief Calcule le scalaire entre deux vecteurs
 * 
 * @param v1     premier vecteur
 * @param v2     deuxieme vecteur
 */
Vecteur scalaire(const Vecteur & v1, const Vecteur & v2){
    return Vecteur(v1.vect[0]*v2.vect[0], v1.vect[1]*v2.vect[1], v1.vect[2]*v2.vect[2]);
}

/**
 * @brief Retourne un vecteur de la partie entier de chaque composant du vecteur en argument
 * 
 * @param v     vecteur
 */
Vecteur floor(const Vecteur &v){
    return Vecteur(int(v.vect[0]), int(v.vect[1]), int(v.vect[2]));
}

/**
 * @brief Calcule la distance euclidienne entre deux vecteurs.
 * 
 * @param v1     vecteur
 * @param v2     vecteur
 */
double  distance( const Vecteur &v1, const Vecteur &v2){
    double r = 0;
    Vecteur vect = v1 - v2;
    for(int k=0;k<3; k++){
      r += vect(k) * vect(k);
    }
    return std::sqrt(r);
}
