#include "particule.hxx"
#include "vecteur.hxx"
#include "cellule.hxx"

#include <deque>


/**
 * @brief Constructeur par defaut de la classe Cellule.
 * 
 */
Cellule::Cellule(){
    id = Vecteur(-1, -1, -1);
}
/**
 * @brief Constructeur de Cellule 
 * 
 * @param d     l'ensemble de particule.
 * @param v     le Vecteur de l'id ( represente son emplacement)
 */
Cellule::Cellule(int d, const Vecteur &v){
    dim = d;
    id = v;
}
/**
 * @brief Constructeur de Cellule 
 * 
 * @param d     l'ensemble de particule.
 * @param v     le Vecteur de l'id ( represente son emplacement)
 * @param c     le Vecteur de centre de la cellule.
 */
Cellule::Cellule(int d, const Vecteur &v, const Vecteur &c){
    dim = d;
    id = v;
    center = c;
}

/**
 * @brief Constructeur de Cellule 
 * 
 * @param d     l'ensemble de particule.
 * @param v     le Vecteur de l'id ( represente son emplacement)
 * @param p     un ensemble de particule
 */
Cellule::Cellule(int d, const Vecteur &v, std::deque<Particle> &p){
    dim = d;
    id = v;
    particles = p;
}

/**
 * @brief Retourne la liste des  coordonnees de voisins d'un point dans en 3D, avec les 3 premier element des voisins en 1D, les 8 premiers en 2D. 
 * 
 */
std::deque<Vecteur> neighb_list(){
    std::deque<Vecteur> tab;
    tab.push_back(Vecteur( 0, 0, 0));
    tab.push_back(Vecteur(-1, 0, 0));
    tab.push_back(Vecteur( 1, 0, 0));
    tab.push_back(Vecteur( 0,-1, 0));
    tab.push_back(Vecteur( 0, 1, 0));
    tab.push_back(Vecteur(-1,-1, 0));
    tab.push_back(Vecteur(-1, 1, 0));
    tab.push_back(Vecteur( 1,-1, 0));
    tab.push_back(Vecteur( 1, 1, 0));
    tab.push_back(Vecteur( 0, 0,-1));
    tab.push_back(Vecteur( 0, 0, 1));
    tab.push_back(Vecteur(-1, 0,-1));
    tab.push_back(Vecteur(-1,-1,-1));
    tab.push_back(Vecteur(-1, 1,-1));
    tab.push_back(Vecteur( 0,-1,-1));
    tab.push_back(Vecteur( 0, 1,-1));
    tab.push_back(Vecteur( 1, 0,-1));
    tab.push_back(Vecteur( 1,-1,-1));
    tab.push_back(Vecteur( 1, 1,-1));
    tab.push_back(Vecteur(-1, 0, 1));
    tab.push_back(Vecteur(-1,-1, 1));
    tab.push_back(Vecteur(-1, 1, 1));
    tab.push_back(Vecteur( 0,-1, 1));
    tab.push_back(Vecteur( 0, 1, 1));
    tab.push_back(Vecteur( 1, 0, 1));
    tab.push_back(Vecteur( 1,-1, 1));
    tab.push_back(Vecteur( 1, 1, 1));
    return tab;
}
/**
 * @brief Retourne la liste des voisins possible selon le dimension, d'une cellule
 * 
 */
std::deque<Vecteur> Cellule::getNeighbours_indexs(){
    std::deque<Vecteur> tab = neighb_list();
    std::deque<Vecteur> neighb;
    int TAILLE = pow(3, dim);
    for (int i = 0; i < TAILLE; i++){
        Vecteur v = Vecteur(id);
        neighb.push_back(v + tab[i]);
    }
    return neighb;
}

void Cellule::addParticle(const Particle  &p){
    particles.push_back(p);
}
/**
 * @brief Initialise les voisins d'une cellule en faisant une intersection entre l'ensemble de cellules existantes et celle des voisins possible.
 * 
 * @param cells     l'ensemble de cellules de l'univers
 */
void Cellule::setNeighbours(std::deque<Cellule*> &cells){
    std::deque<Vecteur> indexs = getNeighbours_indexs();
    for(auto &c : cells){
        for(auto &ind: indexs){
            if(ind.equal(c->id))
                neighbours.push_back(c);
        }
    }
}
/**
 * @brief Teste si la distance entre une particule et le centre d'une cellule est inferieure au rayon
 * 
 * @param p     une particule
 * @param p     la cellule
 * @param rayon     le rayon de courbure
 */
bool checkDistance(Particle p, Cellule c, double rayon){
    double d = distance(p.position, c.center);
    return (d < rayon);
}

/**
 * @brief Calcule les forces de toutes les particules dans la cellule
 * 
 * @param rayon     le rayon de courbure
 */
void Cellule::computeForces(double rayon){
    for(auto &it: particles){
        for(auto &c : neighbours){
            if (checkDistance(it, *c, rayon))
                it.computeForce(c->particles);
        }
    }
}