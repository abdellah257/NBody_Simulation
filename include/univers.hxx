#ifndef UNIVERS_HXX
#define UNIVERS_HXX

#include "particule.hxx"
#include "vecteur.hxx"
#include "cellule.hxx"
#include <deque>

/**
 * @brief Classe Univers
 * 
 */
class Univers {
    public:
        // constantes physiques
        double sigma = 1;
        double epsilon = 5;
        //
        int dim = 3;
        int nb_particles = 0;
        double rc = 1;
        
        Vecteur Lc = Vecteur(1, 1, 1);
        std::deque<Cellule*> cellules;

        Univers();
        Univers(int);
        Univers(int, double, const Vecteur &);

        void initCellules();
        void setNeighbours();
        void addParticle(Particle &);
        void update_forces();
        Vecteur getDimension();
        Vecteur index_position(const Particle &);
        int size();

        void update_cells();
        void compute_forces();
        void compute_forcesBy2();
        void evolution(double, double);
        void evolution_perm(double, double);
        void evolution_vis(double, double);
        void print_univers_positions();

        void reflexion(Particle p, double paroi_inf, double paroi_sup);
        void absorption(Particle p, int index, double paroi_inf, double paroi_sup, Cellule cell);
        void periodicite(Particle p, double paroi_inf, double paroi_sup);

        void energieCinetique(double energieD);
};

void visualisation(std::deque<Cellule*>, std::string);

#endif