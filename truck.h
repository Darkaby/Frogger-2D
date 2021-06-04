/*
 * Widget Truck: Véhicules en mouvement
 * Fichier: truck.h
 * Auteurs:
 * * Gabrielle TCHUENBOU KOMGUEP
 * * Ayinde OLUTCHI
 * * Ahmet DUMLU
 */

#ifndef TRUCK_H
#define TRUCK_H

#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPainter>
#include <QPixmap>

class Truck : public QWidget
{
    Q_OBJECT

public:
    Truck();

    // Coordonnées des véhicules
    void init(int x, int y, int width, int step);
    int step();
    int X();
    int Y();
    int Width();

    // Animer
    void animate();

private:
    int m_x, m_y;
    int m_width;
    int m_height;
    int m_step;
};

#endif // TRUCK_H
