
#include <iostream>
#include <chrono>
#include <cmath>
#include <deque>

#include "particule.hxx"

/**
 * @brief Constructeur par defaut de la classe Particle.
 * 
 */
Particle::Particle(){
  id = 1;
  dim = 3;
  masse = 0;
  categorie = 0;
  active = false;
  position = Vecteur();
  vitesse = Vecteur();
  force = Vecteur();
  old_force = Vecteur();
}
/**
 * @brief l'operateur '=' qui retourne une copie d'une particule
 * 
 * @param p     une particule
 */
Particle & Particle::operator=(const Particle &p){
  id = p.id;
  dim = p.dim;
  masse = p.masse;
  categorie = p.categorie;
  active = p.active;
  position = p.position;
  vitesse = p.vitesse;
  force = p.force;
  old_force = p.old_force;
  return *this;
}
/**
 * @brief Affiche la position d'une particule
 * 
 */
void Particle::affiche_position() const{
  std::cout<<position;
}
/**
 * @brief Affiche la vitesse d'une particule
 * 
 */
void Particle::affiche_vitesse() const{
  std::cout<<vitesse;
}
/**
 * @brief Affiche la force d'une particule
 * 
 */
void Particle::affiche_force() const{
  std::cout<<force;
}
/**
 * @brief Affiche la position, la vitesse et la force associe a une particule
 * 
 */
void Particle::affiche() const {
  this->affiche_position();
  std::cout<<" ";
  this->affiche_vitesse();
  std::cout<<" ";
  this->affiche_force();
  std::cout<<std::endl;
}
/**
 * @brief la mise a jour de la force de la particule en ajoutant son interaction avec une autre particule p
 * 
 * @param p     l'autre particule
 */
void Particle::updateForce(Particle &p){
    /// Calcul du vecteur orientation
    Vecteur orientation = p.position - this->position;
    ///
    double f = lennard_potentiel(p);
    force = force + f * orientation;
}
/**
 * @brief la mise a jour de la force des deux particules a la fois, en ajoutant son interaction entre eux.
 * 
 * @param p     l'autre particule
 */
void Particle::updateForceBy2(Particle &p){
    /// Calcul du vecteur orientation
    Vecteur orientation = p.position - this->position;
    ///
    double f = grav_potentiel(p);
    force = force + f * orientation;
    p.force = p.force - f * orientation;
}
/**
 * @brief la mise a jour de position de la particule pendant un instant dt
 * 
 * @param dt     le pas de temps
 */
void Particle::advance_position(double dt){
  position = position + dt * (vitesse + dt * 0.5/masse *force);
}
/**
 * @brief la mise a jour de vitesse de la particule pendant un instant dt
 * 
 * @param dt     le pas de temps
 */
void Particle::advance_vitesse(double dt){
  vitesse = vitesse + dt * 0.5/masse*(force + old_force);
}
/**
 * @brief Retourne la distance euclidienne entre 2 particules.
 * 
 * @param p     l'autre particule
 */
double Particle::distance(const Particle &p){
  double r = 0;
  Vecteur orientation = p.position - this->position;
  for(int k=0;k<dim; k++){
      r += orientation(k) * orientation(k);
  }
  return std::sqrt(r);
}
/**
 * @brief Retourne le potentiel de Lennard Jones entre 2 particules.
 * 
 * @param p     l'autre particule
 */
double Particle::lennard_potentiel(Particle &p){
    double r = distance(p);
    double epsilon =  5;
    double sigma = 1;
    double param = pow(sigma/r, 6);
    double f = 24 * epsilon * (1/pow(r,2))* param * (1 - 2*param);
    return f;
}
/**
 * @brief Retourne le potentiel gravitationnel entre 2 particules.
 * 
 * @param p     l'autre particule
 */
double Particle::grav_potentiel(Particle &p){
    ///  
    double r = distance(p);   
    double f = this->masse * p.masse / pow(r, 3);
    return f;
}
/**
 * @brief Calcul la force global appliquer d'un ensemble de particule sur cette particule
 * 
 * @param p     l'ensemble de particule.
 */
void Particle::computeForce(std::deque<Particle> &p){
  this->force = Vecteur();
  for( auto &it : p){
    if( this->id != it.id ){
      updateForce(it);
    }
  }
}
/**
 * @brief Calcul la force global appliquer d'un ensemble de particule sur cette particule
 * 
 * @param p     l'ensemble de particule.
 * @param j     l'indice de decoupage des particules( toute particule d'indice >= j est peris en compte).  
 */
void Particle::computeForceBy2(std::deque<Particle> &p, int j){
  this->force = Vecteur();
  int n = p.size();
  for(int i = j; i < n; i++){
    if( this->id != p[i].id ){
      updateForceBy2(p[i]);
    }
  }
}

/**
 * @brief condition reflexive a l'aide du potentiel
 * 
 * @param paroi_inf     paroi inferieure
 * @param paroi_sup     paroi superieure
 * @param sigma         valeur de sigma
 * @param epsilon       valeur de epsilon
 * @return Vecteur 
 */
Vecteur Particle::reflexion_potentiel(double paroi_inf, double paroi_sup, double sigma, double epsilon) {
    double rinf, rsup, rapport, rcut, fx, fy, fz;

    rcut = pow(2., 1/6.) * sigma;

    // force selon x
    fx = 0.;
    rinf = this->position.vect[0] - paroi_inf;
    rsup = paroi_sup - this->position.vect[0];
    if (rinf < rcut) {
        rapport = pow(sigma / (2 * rinf), 6);
        fx -= 24. * sigma * rapport * (1 - 2 * rapport) / (2 * rinf);
    } else if (rsup < rcut) {
        rapport = pow(sigma / (2 * rsup), 6);
        fx -= 24. * epsilon * rapport * (1 - 2 * rapport) / (2 * rsup);
    }

    // force selon y
    fy = 0.;
    rinf = this->position.vect[1] - paroi_inf;
    rsup = paroi_sup - this->position.vect[1];
    if (rinf < rcut) {
        rapport = pow(sigma / (2 * rinf), 6);
        fy -= 24. * sigma * rapport * (1 - 2 * rapport) / (2 * rinf);
    } else if (rsup < rcut) {
        rapport = pow(sigma / (2 * rsup), 6);
        fy -= 24. * epsilon * rapport * (1 - 2 * rapport) / (2 * rsup);
    }

    // force selon z
    fz = 0.;
    rinf = this->position.vect[2] - paroi_inf;
    rsup = paroi_sup - this->position.vect[2];
    if (rinf < rcut) {
        rapport = pow(sigma / (2 * rinf), 6);
        fz -= 24. * sigma * rapport * (1 - 2 * rapport) / (2 * rinf);
    } else if (rsup < rcut) {
        rapport = pow(sigma / (2 * rsup), 6);
        fz -= 24. * epsilon * rapport * (1 - 2 * rapport) / (2 * rsup);
    }

    return Vecteur(fx, fy, fz);
}

/**
 * @brief calcul du potentiel gravitationnel
 * 
 * @param G             constante gravitationnelle
 * @param paroi_inf     paroi inferieure
 * @param paroi_sup     paroi superieure
 * @return double 
 */
double Particle::gravitational_potentiel(double G, double paroi_inf, double paroi_sup) {
    return this->masse * G;
}


double Particle::getM() {
    return masse;
}

int Particle::getId() {
    return id;
}

int Particle::getCat() {
    return categorie;
}

Vecteur Particle::getV() {
    return vitesse;
}

Vecteur Particle::getPos() {
    return position;
}

Vecteur Particle::getF() {
    return force;
}

// modification de l'id
void Particle::setId(double ident) {
    id = ident;
}

// modification de la categorie
void Particle::setCat(double cat) {
    categorie = cat;
}

// modification de la masse
void Particle::setM(double m) {
    masse = m;
}

// modification des vitesses
void Particle::setV(Vecteur &v) {
    vitesse = v;
}

void Particle::setVx(double vx) {
    vitesse.vect[0] = vx;
}

void Particle::setVy(double vy) {
    vitesse.vect[1] = vy;
}

void Particle::setVz(double vz) {
    vitesse.vect[2] = vz;
}

// modification des positions
void Particle::setPos(Vecteur &p) {
    position = p;
}

void Particle::setPosx(double x) {
    position.vect[0] = x;
}

void Particle::setPosy(double y) {
    position.vect[1] = y;
}

void Particle::setPosz(double z) {
    position.vect[2] = z;
}

// modification des forces
void Particle::setF(Vecteur &f) {
    force = f;
}

void Particle::setFx(double fx) {
    force.vect[0] = fx;
}

void Particle::setFy(double fy) {
    force.vect[1] = fy;
}

void Particle::setFz(double fz) {
    force.vect[2] = fz;
}