#ifndef CELLULE_HXX
#define CELLULE_HXX

#include "particule.hxx"
#include "vecteur.hxx"

#include <deque>

/**
 * @brief Classe Cellule
 * 
 */
class Cellule {
    public:
    int dim = 3;
    Vecteur id;
    Vecteur center;
    std::deque<Particle> particles;
    std::deque<Cellule*> neighbours;

    Cellule();
    Cellule(int, const Vecteur &);
    Cellule(int, const Vecteur &, const Vecteur &);
    Cellule(int , const Vecteur &, std::deque<Particle> &);

    std::deque<Vecteur> getNeighbours_indexs();
    void setNeighbours(std::deque<Cellule*> &cells);
    void addParticle(const Particle &);

    void computeForces(double );
};

bool checkDistance(const Particle , const Cellule , double);
std::deque<Vecteur> neighb_list();

#endif