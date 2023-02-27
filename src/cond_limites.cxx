
#include "particule.hxx"
#include "univers.hxx"
#include <assert.h>

void reflexion(Particle p, double paroi_inf, double paroi_sup) {
    assert(paroi_inf < paroi_sup);

    if (p.position.vect[0] >= paroi_sup) {
        p.position = p.position - Vecteur(2 * (p.position.vect[0] - paroi_sup), 0, 0);
        p.vitesse = Vecteur(-p.vitesse.vect[0], p.vitesse.vect[1], p.vitesse.vect[2]);
    } else if (p.position.vect[0] <= paroi_inf) {
        p.position = p.position - Vecteur(2 * (p.position.vect[0] - paroi_inf), 0, 0);
        p.vitesse = Vecteur(-p.vitesse.vect[0], p.vitesse.vect[1], p.vitesse.vect[2]);
    }
    
    if (p.position.vect[1] >= paroi_sup) {
        p.position = p.position - Vecteur(0, 2 * (p.position.vect[1]- paroi_sup), 0);
        p.vitesse = Vecteur(p.vitesse.vect[0], -p.vitesse.vect[1], p.vitesse.vect[2]);
    } else if (p.position.vect[1] <= paroi_inf) {
        p.position = p.position - Vecteur(0, 2 * (p.position.vect[1] - paroi_inf), 0);
        p.vitesse = Vecteur(p.vitesse.vect[0], -p.vitesse.vect[1], p.vitesse.vect[2]);
    }

    if (p.position.vect[2] >= paroi_sup) {
        p.position = p.position - Vecteur(0, 0, 2 * (p.position.vect[2] - paroi_sup));
        p.vitesse = Vecteur(p.vitesse.vect[0], p.vitesse.vect[2], -p.vitesse.vect[2]);
    } else if (p.position.vect[2] <= paroi_inf) {
        p.position = p.position - Vecteur(0, 0, 2 * (p.position.vect[2] - paroi_inf));
        p.vitesse = Vecteur(p.vitesse.vect[0], p.vitesse.vect[2], -p.vitesse.vect[2]);
    }
}


void absorption(Particle p, double paroi_inf, double paroi_sup, Univers univ) {
    assert(paroi_sup >= paroi_inf);

    if ((p.position.vect[0] >= paroi_sup) || (p.position.vect[0] <= paroi_inf) ||
        (p.position.vect[1] >= paroi_sup) || (p.position.vect[1] <= paroi_inf) ||
        (p.position.vect[2] >= paroi_sup) || (p.position.vect[2] <= paroi_inf)) {
        
    }
}


void periodicite(Particle p, double paroi_inf, double paroi_sup) {
    assert(paroi_sup >= paroi_inf);

    if (p.position.vect[0] >= paroi_sup || p.position.vect[0] <= paroi_inf) {
        if (p.position.vect[0] < 0) {
            p.position = Vecteur(fmod(p.position.vect[0], paroi_sup - paroi_inf) + paroi_sup - paroi_inf, p.position.vect[1], p.position.vect[2]);
        } else {
            p.position = Vecteur(fmod(p.position.vect[0], paroi_sup - paroi_inf), p.position.vect[1], p.position.vect[2]);
        }
        
    }

    if (p.position.vect[1] >= paroi_sup || p.position.vect[1] <= paroi_inf) {
        if (p.position.vect[1] < 0) {
            p.position = Vecteur(p.position.vect[0], fmod(p.position.vect[1], paroi_sup - paroi_inf) + paroi_sup - paroi_inf, p.position.vect[2]);
        } else {
            p.position = Vecteur(p.position.vect[0], fmod(p.position.vect[1], paroi_sup - paroi_inf), p.position.vect[2]);
        }
    }

    if (p.position.vect[2] >= paroi_sup || p.position.vect[2] <= paroi_inf) {
        if (p.position.vect[2] < 0) {
            p.position = Vecteur(p.position.vect[0], p.position.vect[1], fmod(p.position.vect[2], paroi_sup - paroi_inf) + paroi_sup - paroi_inf);
        } else {
            p.position = Vecteur(p.position.vect[0], p.position.vect[1], fmod(p.position.vect[2], paroi_sup - paroi_inf));
        }
    }
}


