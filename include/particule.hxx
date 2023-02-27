
#ifndef PARTICULE_HXX
#define PARTICULE_HXX

#include <array>
#include <deque>
#include <random>
#include <list>
#include "vecteur.hxx"

/**
 * @brief Classe Particle
 * 
 */
class Particle {
    public :

        int id;
        int dim;
        int categorie;
        double masse;
        bool active;

        Vecteur position;
        Vecteur vitesse;
        Vecteur force;
        Vecteur old_force;

        double getM();
        int getId();
        int getCat();
        Vecteur getV();
        Vecteur getPos();
        Vecteur getF();

        // modification de l'id
        void setId(double ident);

        // modification de la categorie
        void setCat(double cat);

        // modification de la masse
        void setM(double m);

        // modification des vitesses
        void setV(Vecteur &v);
        void setVx(double vx);
        void setVy(double vy);
        void setVz(double vz);

        // modification des positions
        void setPos(Vecteur &p);
        void setPosx(double x);
        void setPosy(double y);
        void setPosz(double z);

        // modification des forces
        void setF(Vecteur &f);
        void setFx(double fx);
        void setFy(double fy);
        void setFz(double fz);

        // constructeur
        Particle();

        Particle &operator= (const Particle &);

        // Permet d'afficher les champs relatifs à une particule
        void affiche() const;
        void affiche_position() const;
        void affiche_vitesse() const;
        void affiche_force() const;

        void computeForce(std::deque<Particle> &);
        void computeForceBy2(std::deque<Particle> &, int);

        void advance_position(double );
        void advance_vitesse(double );
        void updateForce(Particle &);

        void updateForceBy2(Particle &);

        double lennard_potentiel(Particle &);
        double grav_potentiel(Particle &);
        Vecteur reflexion_potentiel(double paroi_inf, double paroi_sup, double sigma, double epsilon);
        double gravitational_potentiel(double G, double paroi_inf, double paroi_sup);

        double distance(const Particle &);
};

#endif