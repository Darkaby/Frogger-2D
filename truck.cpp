/*
 * Widget Truck: Véhicules en mouvement
 * Fichier: truck.cpp
 * Auteurs:
 * * Gabrielle TCHUENBOU KOMGUEP
 * * Ayinde OLUTCHI
 * * Ahmet DUMLU
 */

#include "truck.h"
#include <QTimer>
#include <QPainter>
#include <QPen>

Truck::Truck() : QWidget() {}

// Initialisation du véhicule: position, taille et pas
void Truck::init(int x, int y, int width, int step)
{
    m_x = x; m_y = y;
    m_width = width;
    m_step = step;
    setGeometry(m_x, m_y, m_width, 50);
}

// Getters
int Truck::X()
{
    return m_x;
}

int Truck::Y()
{
    return m_y;
}

int Truck::step()
{
    return m_step;
}

int Truck::Width()
{
    return m_width;
}

// Animation du véhicule
void Truck::animate()
{
    m_x -= m_step;

    if (m_step < 0){ // Déplacement de la droite vers la gauche
        // Faire une boucle une fois arrivé à l'extrémité de la fenêtre
        if (m_x >= parentWidget()->width())
            m_x = -m_width;
    }
    if (m_step > 0){ // Déplacement de la gauche vers la droite
        if (m_x <= -m_width)
            m_x = parentWidget()->width();
    }

}
