
#include <gtest/gtest.h>

#include "cellule.hxx"
#include "particule.hxx"
#include "univers.hxx"
#include "vecteur.hxx"

/**
 * @brief Classe de test de Vecteur
 * 
 */
class VecteurTest : public ::testing::Test {
    protected:
        void SetUp() override {
            v1 = Vecteur();
            v2 = Vecteur(2, 3, 4);
            v3 = Vecteur(v2);
            v4 = v1 + 2;
            v5 = v4 + v2;
            v6 = v2 - v4;
            v7 = v6 * 5;
            v8 = v7 / 5;
            v9 = Vecteur(2, 1, 1);
            v9 *= 3;
            v10 = Vecteur();
            v10 += 5.5;
            v11 = scalaire(v9, v10);
            v12 = floor(v11);
        }
        Vecteur v1;
        Vecteur v2;
        Vecteur v3;
        Vecteur v4;
        Vecteur v5;
        Vecteur v6;
        Vecteur v7;
        Vecteur v8;
        Vecteur v9;
        Vecteur v10;
        Vecteur v11;
        Vecteur v12;
        
};

/**
 * @brief Classe de test de Particle
 * 
 */
class ParticleTest : public ::testing::Test {
    protected:
        void SetUp() override {
            p = new Particle();

            // masse de la masse
            p->setM(9.55e-4);
            
            // force de la particule
            p->setFx(0.04);
            p->setFy(0.05);
            p->setFz(0.022);

            // vitesse de la particule
            p->setVx(0.01);
            p->setVz(0.02);

            // position de la particule
            p->setPosx(0.01);
            p->setPosy(0.03);
        }
        Particle *p;
};

// test de la class particle
/**
 * @brief Test de l'accesseur de la masse d'une particule
 * 
 */
TEST_F(ParticleTest, Masse) {

    EXPECT_EQ(p->getM(), 9.55e-4);

}

/**
 * @brief Test des accesseurs de la force d'une particule
 * 
 */
TEST_F(ParticleTest, Force) {

    EXPECT_EQ(p->getF()(0), 0.04);
    EXPECT_EQ(p->getF()(1), 0.05);
    EXPECT_EQ(p->getF()(2), 0.022);

}

/**
 * @brief Test des accesseurs de la vitesse d'une particule
 * 
 */
TEST_F(ParticleTest, Vitesse) {

    EXPECT_EQ(p->getV()(0), 0.01);
    EXPECT_EQ(p->getV()(1), 0);
    EXPECT_EQ(p->getV()(2), 0.02);

}

/**
 * @brief Test des accesseurs de la position d'une particule
 * 
 */
TEST_F(ParticleTest, Position) {

    EXPECT_EQ(p->getPos()(0), 0.01);
    EXPECT_EQ(p->getPos()(1), 0.03);
    EXPECT_EQ(p->getPos()(2), 0);

}

// test de la class Vecteur
/**
 * @brief Test des constructeurs de la classe Vecteur
 * 
 */
TEST_F(VecteurTest, Constructeur) {

    EXPECT_EQ(v1(0), 0);
    EXPECT_EQ(v1(1), 0);
    EXPECT_EQ(v1(2), 0);

    EXPECT_EQ(v2(0), 2);
    EXPECT_EQ(v2(1), 3);
    EXPECT_EQ(v2(2), 4);

    EXPECT_EQ(v2.equal(v3), true);

}

/**
 * @brief Test des operateurs de la classe Vecteur
 * 
 */
TEST_F(VecteurTest, Operateurs) {

    EXPECT_EQ(v4(0), 2);
    EXPECT_EQ(v4(1), 2);
    EXPECT_EQ(v4(2), 2);

    EXPECT_EQ(v5(0), 4);
    EXPECT_EQ(v5(1), 5);
    EXPECT_EQ(v5(2), 6);

    EXPECT_EQ(v6(0), 0);
    EXPECT_EQ(v6(1), 1);
    EXPECT_EQ(v6(2), 2);

    EXPECT_EQ(v7(0), 0);
    EXPECT_EQ(v7(1), 5);
    EXPECT_EQ(v7(2), 10);

    EXPECT_EQ(v8.equal(v6), true);

    EXPECT_EQ(v9(0), 6);
    EXPECT_EQ(v9(1), 3);
    EXPECT_EQ(v9(2), 3);

    EXPECT_EQ(v10(0), 5.5);
    EXPECT_EQ(v10(1), 5.5);
    EXPECT_EQ(v10(2), 5.5);

    EXPECT_EQ(v11(0), 33);
    EXPECT_EQ(v11(1), 16.5);
    EXPECT_EQ(v11(2), 16.5);

    EXPECT_EQ(v12(0), 33);
    EXPECT_EQ(v12(1), 16);
    EXPECT_EQ(v12(2), 16);

}